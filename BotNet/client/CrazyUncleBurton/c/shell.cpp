#include "shell.h"
#include "Virus.h"
#include "path.hpp"
#include "Point.h"

#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include <map>
using namespace std;

map<int,int> baseAttackers;
const int attackerMin = 2;
const int maxAttackers = 1;

class MovePreferenceBehavior {
  const static int DirectionOrder;
};

// ostream& operator<<(ostream& o, const Virus& v) {
//   o << "[Virus (" << v.x() << "," << v.y() << ") O(" << v.owner() 
//     << ") L(" << v.level() << ")]";
// }
// ostream& operator<<(ostream& o, const Base& b) {
//   o << "[Base (" << b.x() << "," << b.y() << ") O(" << b.owner() 
//     << "]";
// }
Virus* getVirusAt( Point p, AI *ai );
void build_shell_virus( Virus& v, AI *ai, Map& map );
bool victimNearby( Virus& v, AI *ai, Map& m,
                   Point &target ); // output param
void getLegalMoves( Point& p, AI *ai, Map &m,
                    vector<Point>& moves );
bool CommandAttacker( Virus &v, AI *ai, Map& m );



void build_shells( AI* ai, Map& map ){ 
  srand(time(NULL));

  cout << map << endl << endl;

  for (vector<Virus>::iterator i = ai->viruses.begin();
       i != ai->viruses.end();
       i++) {
    // if you own that virus
    if((*i).owner() == ai->playerID())
      build_shell_virus(*i,ai,map);
  }
}


void build_shell_virus( Virus& v, AI *ai, Map& map ) {
    ai->players[ai->playerID()].talk("Better...");
    // If this returns true, this virus has been given "special" orders.
  //if (CommandAttacker(v,ai,map)) return;

    // get all legal moves.
    Point here(v.x(),v.y());
    cout << "Virus at " << here << endl;
    vector<Point> moves;
    int off = (v.id() % 2)*2;
    for (int d=0; d<4; d++) {
      int doff = (d+off)%4; // odd virus id: Left/Right; even: up/down
      if (doff==0) {
        // up
        if (map.legal(here.x,here.y-1))
          moves.push_back(Point(here.x,here.y-1));
      } else if (doff==1) {
        // down
        if (map.legal(here.x,here.y+1))
          moves.push_back(Point(here.x,here.y+1));
      } else if (doff==2) {
        // right
        if (map.legal(here.x+1,here.y))
          moves.push_back(Point(here.x+1,here.y));
      } else if (doff==3) {
        // left
        if (map.legal(here.x-1,here.y))
          moves.push_back(Point(here.x-1,here.y));
      }
    }
    //    cout << "Legal Moves:";
    //    for (int i=0; i<moves.size(); i++) { cout << " (" << i << ")" << moves[i]; } cout << endl;
    if (moves.size() == 0) return; // Why?
    
    // check for an adjacent killable opponent
    for (vector<Point>::iterator pMove = moves.begin();
         pMove != moves.end();
         pMove++) {
      MAPCODE content = map.at((*pMove).x,(*pMove).y);
      if (content == OPVIRUS) {
        Virus *t = getVirusAt(*pMove,ai);
        if (t->level() < v.level()) {
          cout << "Attack: " << *pMove << endl;
          v.move((*pMove).x,(*pMove).y);
          return;
        }
      }
    }
    //    cout << "after attack" << endl;

    // if we can combine, do so
    for (vector<Point>::iterator pMove = moves.begin();
         pMove != moves.end();
         pMove++) {
      MAPCODE content = map.at((*pMove).x,(*pMove).y);
      if (content == MYVIRUS) {
        Virus *t = getVirusAt(*pMove,ai);
        if (t->level() == v.level()) {
          cout << "Combine: " << *pMove << endl;
          v.move((*pMove).x,(*pMove).y);
          return;
        }
      }
    }
    //    cout << "after combine" << endl;

    // If we can surround a base, do so.

    // Break a chain

    for (vector<Point>::iterator pMove = moves.begin();
         pMove != moves.end();
         pMove++) {
      MAPCODE content = map.at((*pMove).x,(*pMove).y);
      // Take an opponent's tile.
      if (content == OP) { // take it.
        cout << "Take: " << *pMove << endl;
        v.move((*pMove).x,(*pMove).y);
        return;
      } else if (content == EMPTY) { // take it.
        cout << "Occupy: " << *pMove << endl;
        v.move((*pMove).x,(*pMove).y);
        return;
      } else if (content == MY) { // skip it.
      }
    }
    //cout << "after take ownership" << endl;

    // Look for the closest empty spot.
    cout << "Looking for nearest open tile." << endl;
    vector<MAPCODE> targets;
    targets.push_back(EMPTY);
    targets.push_back(OP);
    Path *target = pathToNearestTarget(map,here,targets);
    if (target) {
      cout << "Nearest: [" << target->end << "] <-- " << target->nodes[1] << endl;
      v.move(target->nodes[1].x,target->nodes[1].y);
      return;
    }

    // Nothing remains but death or my own squares. Random move.
    int m = rand();
    //cout << "R: " << m << endl;
    m %= moves.size();
    cout << "Random: [" << m << "] " << moves[m] << endl;
    v.move(moves[m].x,moves[m].y);
    //cout << "after random move" << endl;

    return;
}

bool CommandAttacker( Virus &v, AI *ai, Map& m ) {
    // Check for "attacker" status.
    if (v.level() >= attackerMin) {
      if (baseAttackers.size() <= maxAttackers) {
        baseAttackers[v.id()] = -1;
        cout << "Unassigned Attacker: " << v << endl;
      }
      Point vloc = Point(v.x(),v.y());

      if (baseAttackers.count(v.id())) {
        cout << "  Searching for target..." << endl;
        Path *closestPath = NULL;
        Base closest_base;
        EdgeCost closest = EdgeFar;

        // known attacker
        if (baseAttackers[v.id()] == -1) {
          for (vector<Base>::iterator base = ai->bases.begin();
               base != ai->bases.end();
               base++) {
            if ((*base).owner() == ai->playerID()) continue;
            cout << "  Enemy Base: " << (*base) << endl;

            Path p;
            p.start = vloc;
            p.end = Point((*base).x(),(*base).y());
            cout << asText(m,p);

            Path *toBase =
              path_astar(m,vloc,Point((*base).x(),(*base).y()),
                         (AStarBehavior_t)(AS_IgnoreViruses | AS_AllowImpassableEnd));

            if (!toBase) {
              cout << " * No path from " << vloc << " to base " 
                   << (*base) << endl;
              continue; // no path
            }
            cout << asText(m,*toBase);

            EdgeCost d = toBase->nodes.size()-1;
            if (d < closest) {
              closest = d;
              closest_base = *base;
              closestPath = toBase;
            }
          }
          if (closest != EdgeFar) {
            cout << "  Base acquired: " << closest_base << endl;
            baseAttackers[v.id()] = closest_base.id();
          }
        }
        if (closestPath == NULL) {
          baseAttackers.erase(v.id());
          return false; // this guy can't do it.
        }

        // Now, what to do.
        if (closestPath->nodes.size() <= 3) {
          // Look for a kill, or go to a corner.
          Point target;
          if (victimNearby(v,ai,m,target)) {
            cout << " Attacker [" << v.id() << "]" << vloc << " -> Victim " << target << "]" << endl;
            stringstream s(stringstream::out);
            s << " Attacker [" << v.id() << "]" << vloc << " -> Victim " << target << "]";
            string st = s.str();
            ai->players[ai->playerID()].talk((char*)(s.str().c_str()));
            v.move(target.x,target.y);
            return true;
          }
        } else {
          // Direct him toward the base.
          Point vMove = closestPath->nodes[1];
          cout << " Attacker [" << v.id() << "]" << vloc << " -> Base[" << closest_base << "]" << endl;
            stringstream s(stringstream::out);
            s << " Attacker [" << v.id() << "]" << vloc << " -> Base " << closest_base << "]";
            ai->players[ai->playerID()].talk((char*)(s.str().c_str()));
            v.move(vMove.x,vMove.y);
          return true;
        }
      }
    }

    return false;
}

Virus* getVirusAt( Point p, AI *ai ) {
  for (vector<Virus>::iterator i = ai->viruses.begin();
       i != ai->viruses.end();
       i++) {
    if ((*i).x() == p.x && (*i).y() == p.y) {
      return &(*i);
    }
  }
  return NULL;
}

bool victimNearby( Virus& v, AI *ai, Map& map,
                   Point &target ) { // output param
  vector<Point> legalMoves;
  Point vloc(v.x(),v.y());
  getLegalMoves(vloc,ai,map,legalMoves);
  for (vector<Point>::iterator move = legalMoves.begin();
       move != legalMoves.end();
       move++) {
    if (map.at((*move).x,(*move).y) == OPVIRUS) {
      // ensure we can kill it.
      Virus *victim = getVirusAt(*move,ai);
      if (victim->level() < v.level()) {
        target = *move;
        return true;
      }
    }
  }

  return false;
}

void getLegalMoves( Point& p, AI *ai, Map &map,
                    vector<Point>& moves ) {
    // get all legal moves.
    for (int d=0; d<4; d++) {
      if (d==0) {
        // up
        if (map.legal(p.x,p.y-1))
          moves.push_back(Point(p.x,p.y-1));
      } else if (d==1) {
        // down
        if (map.legal(p.x,p.y+1))
          moves.push_back(Point(p.x,p.y+1));
      } else if (d==2) {
        // right
        if (map.legal(p.x+1,p.y))
          moves.push_back(Point(p.x+1,p.y));
      } else if (d==3) {
        // left
        if (map.legal(p.x-1,p.y))
          moves.push_back(Point(p.x-1,p.y));
      }
    }
}
