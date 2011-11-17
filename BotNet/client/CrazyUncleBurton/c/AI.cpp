#include "AI.h"
#include "util.h"

#include "Officer.h"
#include "RandomOfficer.h"
#include "LemmingOfficer.h"
#include "shell.h"
#include "rrbase.h"

AI::AI(Connection* conn) : BaseAI(conn) {}

const char* AI::username()
{
  return "mst00120";
}

const char* AI::password()
{
  return "aegoaf5Y";
}

Officer Commander_Washington;
RandomOfficer LtRand;
LemmingOfficer ColRight,ColUp;

//This function is run once, before your first turn.
void AI::init(){
  cout << "AI Started" << endl;
  cout << "Base Cost: " << baseCost() << ", Scale: " << scaleCost() << endl;

  // run-time configuration is required here.
  Commander_Washington.LogLevel(10);
  Commander_Washington.init(this);
  Commander_Washington.setOfficerName("Gen.Wash");
  Commander_Washington.PressRelease("Good afternoon, gentlemen.");

  ColRight.LogLevel(10);
  ColRight.marchDir(East);
  ColRight.unitsWanted(2);
  ColRight.minLevel(1);
  ColRight.setOfficerName(string("Col.Right"));
  Commander_Washington.addSubordinate(&ColRight);
  ColRight.PressRelease("Col. Right, reporting for duty.");

  ColUp.LogLevel(10);
  ColUp.marchDir(North);
  ColUp.unitsWanted(2);
  ColUp.minLevel(0);
  ColUp.setOfficerName(string("Col.Up"));
  Commander_Washington.addSubordinate(&ColUp);
  ColUp.PressRelease("Col. Up, reporting for duty.");

  LtRand.LogLevel(10);
  LtRand.unitsWanted(0x7FFF); // the rest of the troops
  LtRand.minLevel(0);
  LtRand.setOfficerName("Lt.Rand");
  Commander_Washington.addSubordinate(&LtRand);
  LtRand.PressRelease("Lt. Random, reporting for duty.");
}

//This function is called each time it is your turn.
//Return true to end your turn, return false to ask the server for updated information.
bool AI::run()
{
  players[playerID()].talk((char*)"The General: 0.51 (2xLem,1Rand)");

  // Future: tell the map to update itself (saving history)
  map = Map(this);

  // Update convenience data structures.
  myBases.erase(myBases.begin(),myBases.end());
  for (vector<Base>::iterator base = bases.begin();
       base != bases.end();
       base++) {
    if ((*base).owner() == playerID()) myBases.push_back(*base);
  }
  myViruses.erase(myViruses.begin(),myViruses.end());
  for (vector<Virus>::iterator virus = viruses.begin();
       virus != viruses.end();
       virus++) {
    if ((*virus).owner() == playerID()) myViruses.push_back(*virus);
  }

  // Let the General command the army.
  Commander_Washington.Command();

  // The Old Way
  // // virus coverage strategy
  // build_shells(this,map);

  // // fewest spawns
  // distribute_base_spawning(this,map);


  // // loop through all of the bases
  // for(int i=0;i<bases.size();i++)
  // {
  //   // check if you own that base
  //   if(bases[i].owner() == playerID())
  //   {
  //     // check to see if you have enough cycles to spawn a level 0 virus
  //     if(baseCost() <= players[playerID()].cycles())
  //     {
  //       // spawn a level 0 virus at that base
  //       bases[i].spawn(0);
  //     }
  //   }
  // }

  // // loop through all of the viruses
  // for(int i=0;i<viruses.size();i++)
  // {
  //   // if you own that virus
  //   if(viruses[i].owner() == playerID())
  //   {
  //     // if the tile you want to move to is NOT a wall
  //     if(getTileAtLocation(viruses[i].x()+1, viruses[i].y()).owner() != 3)
  //     {
  //       // move the virus
  //       viruses[i].move(viruses[i].x()+1, viruses[i].y());
  //     }
  //   }
  // }
 // End your turn
  return true;
}

//This function is run once, after your last turn.
void AI::end(){}
