#include "TheGeneral.h"

#include "ZoneChain.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void TheGeneral::initChains() {
  // default chain
  _chains.push_back(ZoneChain(_ai));
  _chains.back().m_neededDrones = 0xFFFF;
  _chains.back().m_minLv = 0;
  _chains.back().m_maxLv = 99;
}

void TheGeneral::Command() {
  _ai->players[_ai->playerID()].talk((char*)"The General: 0.5 (Zone)");

  // Remove any dead viruses from the payroll.
  // Update the map object.
  NotifySuperiors("Reclassifying ex-units.");
  for (vector<Chain>::iterator chain = _chains.begin();
       chain != _chains.end();
       chain++) {
    (*chain).update();
  }

  // Walk through each assignment, getting a list of viruses to spawn.
  bool saveMoneyInstead = false;
  int spawned = 0;
  int max_spawns = 3; // constant
  for (vector<Chain>::iterator chain = _chains.begin();
       chain != _chains.end();
       chain++) {
    // If we need more and we're not saving money, buy more.
    if (((*chain).numDrones() < (*chain).m_neededDrones) &
        !saveMoneyInstead) {
      int needed = (*chain).m_neededDrones - (*chain).numDrones();

      for (int i=0; i<max_spawns; i++) {
        if (spawned >= max_spawns) break; // don't spawn any more

        // If this returns true, it was able to spawn (or decide it didn't
        //   want to).
        if ((*chain).spawnMore()) {
          spawned++;  // not the best way (look at bases[n].spawnsLeft())
        } else {
          saveMoneyInstead = true;
          continue;
        }
      }
    }
  }

  for (vector<Chain>::iterator chain = _chains.begin();
       chain != _chains.end();
       chain++) {
    (*chain).advance();
  }

  return;
}

#ifdef _DEBUG_THE_GENERAL

int TheGeneral::LogLevel( int lvl ) {
  if (lvl >= 0) _LogLevel = lvl;
  return _LogLevel;
}

void TheGeneral::CaptainsLog( int lvl, string msg, bool eol ) {
  cout << "[The General:" << setw(2) << lvl << "/" << _LogLevel << "] " << msg;
  if (eol) cout << endl;
}
void TheGeneral::OfficersLog( int lvl, string ofc_monik, string msg, bool eol ) {
  cout << "[Officer:" << ofc_monik << "] " << msg;
  if (eol) cout << endl;
}
#endif // _DEBUG_THE_GENERAL
