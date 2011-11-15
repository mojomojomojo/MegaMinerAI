#include "rrbase.h"
#include <stdint.h>

#include <map>
using namespace std;

map<int,uint32_t> spawnCounts; // global
map<int,uint32_t>::iterator counti;
// if we've already attempted to spawn this turn.
map<int,bool> spawnedThisTurn;

void distribute_base_spawning( AI* ai, Map& m ) {
  int max_iters = 6;
  // While we can afford a level 0.
  int iters = 0;
  cout << "Spawn Counts: ";
  for (counti=spawnCounts.begin();
       counti != spawnCounts.end();
       counti++) {
    cout << "  [" << (*counti).first << "]" << (*counti).second;
  }
  cout << endl;

  while (ai->baseCost() <= ai->players[ai->playerID()].cycles()
         && iters++ < max_iters) {
    //cout << " [SPAWN_LOOP]" << endl;
    uint32_t min_spawns = 0xFFFFFFFF;
    vector<Base>::iterator min_base;
    uint8_t canSpawn = ai->bases.size();

    for (vector<Base>::iterator base = ai->bases.begin();
         base != ai->bases.end();
         base++) {
      spawnedThisTurn[(*base).id()] = false;
    }

    // Find the base with the least amount of spawned viruses.
    for (vector<Base>::iterator base = ai->bases.begin();
         base != ai->bases.end();
         base++) {

      // cout << " [BASE_LOOP]" << endl;
      if ((*base).owner() != ai->playerID()) {
        canSpawn--;
        continue;
      }
      if (spawnedThisTurn[(*base).id()]) {
        canSpawn--;
        continue;
      }
      if ((*base).spawnsLeft() < 1) {
        canSpawn--;
        continue;
      }

      if (spawnCounts.count((*base).id()) > 0) {
        uint32_t spawns = spawnCounts[(*base).id()];
        if (spawns < min_spawns) {
          // new low base
          min_spawns = spawns;
          min_base = base;
        }
      } else {
        cout << "  Base " << (*base).id() << " never spawned" << endl;
        min_base = base;
        min_spawns = 0;
      }
    }

    cout << "Spawning from base " << (*min_base).id() << " (min:" << min_spawns << ")" << endl;
    (*min_base).spawn(0);
    spawnCounts[(*min_base).id()] = min_spawns+1;
    spawnedThisTurn[(*min_base).id()] = true;

    cout << "Bases that can spawn: " << (uint32_t)canSpawn << endl;
    if (canSpawn == 0) break;
  }

  return;
}
