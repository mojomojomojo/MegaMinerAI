#include "RandomOfficer.h"
#include "Point.h"
#include "strutil.h"
#include "EnumsH.h"

#include <stdlib.h> // rand()
#include <time.h>

#include <algorithm>
using namespace std;



// bool RandomOfficer::spawnMore()
// {
//   NotifySuperiors("Preparing to deploy more troops.");

//   vector<int> randomOrder;
//   for (int i=0; i<_ai->bases.size(); i++) {
//     randomOrder.push_back(rand()%10000 * 100 + i);
//   }
//   sort(randomOrder.begin(),randomOrder.end());

//   for(int i=0;i<_ai->bases.size();i++)
//   {
//     int b = randomOrder[i]%100;

//     // check if you own that base
//     if(_ai->bases[b].owner() == _ai->playerID())
//     {
//       // check to see if you have enough cycles to spawn a level 0 virus
//       if(_ai->baseCost() <= _ai->players[_ai->playerID()].cycles())
//       {
//         // spawn a level 0 virus at that base
//         _ai->bases[b].spawn(0);
//         CLEAR_DEBUG_STREAM;
//         _DS("Spawning level 0 virus from ");
//         _DS(Point(_ai->bases[b].x(),_ai->bases[b].y()));_DS(":");_DS(b);
//         NotifySuperiors(DEBUG_STRING);

//       }
//     }
//   }

//   Officer::spawnMore();
// }

bool RandomOfficer::advance()
{
  NotifySuperiors("Issuing orders for troops.");

  for (vector<int>::iterator u = _employedUnits.begin();
       u != _employedUnits.end();
       u++) {
    _TakeNotes("Determining orders for virus ID "<<(*u));

    Virus *v = _ai->locateVirus(*u);
    if (!v) {
      NotifySuperiors(string("Bad employee id: ")+int_str(*u));
      continue;
    }

    int x = v->x();
    int y = v->y();
    int dir = rand()%2;
    int dist = (rand()%3)-1;
    if (dir == 0) {
      x += dist;
    } else {
      y += dist;
    }
      
    // Keep choosing until you get one that's not off the map.
    // getTileAtLocation() doesn't do any bounds checking.
    // if the tile you want to move to is NOT a wall or a base.
    int rand_limit = 100;
    int tries = 0;
    while (!(
             (x >= 0 && x<_ai->width()) &&
             (y >= 0 && y<_ai->height()) &&
             (_ai->getTileAtLocation(x,y).owner() != 3) &&
             (_ai->map.at(x,y) != OPBASE) &&
             (_ai->map.at(x,y) != MYBASE)
             )
           ) {
      if (tries++ > rand_limit) break;

      int dir = rand()%2;
      int dist = (rand()%3)-1;
      if (dir == 0) {
        x = v->x() + dist;
      } else {
        y = v->y() + dist;
      }
    }
    if (tries > rand_limit) continue; // Don't try anything if this happens.

    _NotifySuperiors("Sending virus to "<<Point(x,y)<<":"<<v);

    // Move the virus (if it's going somewhere--the game complains if you
    //   attempt to move() it to the same location).
    if ( x != v->x() || y != v->y() )
      v->move(x,y);
  }

  return Officer::advance();
}

