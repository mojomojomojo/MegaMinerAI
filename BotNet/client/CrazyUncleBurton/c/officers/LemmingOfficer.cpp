#include "LemmingOfficer.h"

#include "officerutil.h"

#include <map>
using namespace std;

// bool LemmingOfficer::spawnMore() {
//   PersonalMemoirs("LemmingOfficer::spawnMore()...");

//   vector<Base> randomBase = RandomMyBaseOrdering(_ai);
//   // While:
//   //   we don't have enough
//   //   we can still spawn more
//   //   we can afford the minimum level virus

//   CLEAR_DEBUG_STREAM;
//   _DS("Employed: "<<numEmployed()<<", Wanted: "<<unitsWanted()<<", SpawnsLeft: "<<_ai->spawnsLeft()<<", Afford("<<(int)_minLvl<<")?: "<<_ai->canAffordVirus(_minLvl)<<", Cost:"<<_ai->virusCost(_minLvl)<<", Cycles:"<<_ai->players[_ai->playerID()].cycles());
//   TakeNotes(DEBUG_STRING);

//   int passes = 0,
//       max_passes = _ai->bases.size()*_ai->bases.size(); // just in case
//   while ((numEmployed() < unitsWanted()) &&
//          _ai->spawnsLeft() > 0 &&
//          _ai->canAffordVirus(_minLvl)
//          ) {
//     if (passes++ > max_passes) break; // just in case

//     bool spawnsRemain = false;
//     for (vector<Base>::iterator base = randomBase.begin();
//          base != randomBase.end();
//          base++) {
//       if (baseCanSpawn(*base,_ai->map)) {
//         spawnsRemain = true;
//         requisitionUnit(_minLvl,(*base),this);
//       } else {
//         CLEAR_DEBUG_STREAM;
//         _DS("Base cannot spawn: "<<*base);
//         TakeNotes(DEBUG_STRING);
//       }
//     }
//     // An occupied base that can spawn is the consideration here.
//     if (!spawnsRemain) break;
//   }

//   if ((numEmployed() < unitsWanted()) && !_ai->canAffordVirus(_minLvl)) {
//     // Don't let subordinates spawn. We're saving up our cycles.
//     return false;
//   }

//   // recurse
//   return Officer::spawnMore();
// }

bool LemmingOfficer::advance() {
  PersonalMemoirs("LemmingOfficer::advance()...");

  for (vector<int>::iterator u = _employedUnits.begin();
       u != _employedUnits.end();
       u++) {
    _TakeNotes("Determining orders for virus ID "<<(*u));
    Virus* v = _ai->locateVirus(*u);
    if (v) {
      Point move = go(Point(v->x(),v->y()),_marchDir);
      if (_ai->map.legal(move.x,move.y)) {
        CLEAR_DEBUG_STREAM;
        _DS("Order "<<Point(v->x(),v->y())<<" -> "<<move<<" for "<<*v);
        NotifySuperiors(DEBUG_STRING);

        v->move(move.x,move.y);
      } else {
        CLEAR_DEBUG_STREAM;
        _DS("Lemming virus stuck: "<<*v);
        NotifySuperiors(DEBUG_STRING);
      }
    } else {
      NotifySuperiors(string("Bad employee id: ")+int_str(*u));
    }
  }

  return Officer::advance();
}
