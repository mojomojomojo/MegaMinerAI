//Copyright (C) 2009 - Missouri S&T ACM AI Team
//Please do not modify this file while building your AI
//See AI.h & AI.cpp for that

#include "BaseAI.h"
#include "game.h"
#include <math.h>

int BaseAI::turnNumber()
{
  return getTurnNumber(c);
}
int BaseAI::playerID()
{
  return getPlayerID(c);
}
int BaseAI::gameNumber()
{
  return getGameNumber(c);
}
int BaseAI::baseCost()
{
  return getBaseCost(c);
}
float BaseAI::scaleCost()
{
  return getScaleCost(c);
}
//// TWH
int BaseAI::virusCost( int level ) {
  return (int)(baseCost() * powf(scaleCost(),level));
}
int BaseAI::spawnsLeft() {
  int remain = 0;
  for (std::vector<Base>::iterator base = bases.begin();
       base != bases.end();
       base++) {
    if ((*base).owner() == playerID()) {
      remain += (*base).spawnsLeft();
    }
  }
  return remain;
}

bool BaseAI::canAffordVirus( int level ) {
  return players[playerID()].cycles() >= virusCost(level);
}

Virus* BaseAI::locateVirus( int virusID ) {
  for (vector<Virus>::iterator v = viruses.begin();
       v != viruses.end();
       v++) {
    if ((*v).id() == virusID) {
      return &(*v);
    }
  }
  return NULL;
}
Virus* BaseAI::locateVirusAtBase( int baseID ) {
  // Find the base.
  for (vector<Base>::iterator b = bases.begin();
       b != bases.end();
       b++) {
    if ((*b).id() == baseID) {
      for (vector<Virus>::iterator v = viruses.begin();
           v != viruses.end();
           v++) {
        if ((*v).x() == (*b).x() && (*v).y() == (*b).y()) {
          return &(*v);
        }
      }
    }
  }
  return NULL;
}

//// TWH


int BaseAI::width()
{
  return getWidth(c);
}
int BaseAI::height()
{
  return getHeight(c);
}
Tile& BaseAI::getTileAtLocation(int x, int y)
{
  return tiles[x+y*width()];
}

bool BaseAI::startTurn()
{
  static bool initialized = false;
  int count = 0;
  count = getBaseCount(c);
  bases.clear();
  bases.resize(count);
  for(int i = 0; i < count; i++)
  {
    bases[i] = Base(getBase(c, i));
  }

  count = getPlayerCount(c);
  players.clear();
  players.resize(count);
  for(int i = 0; i < count; i++)
  {
    players[i] = Player(getPlayer(c, i));
  }

  count = getTileCount(c);
  tiles.clear();
  tiles.resize(count);
  for(int i = 0; i < count; i++)
  {
    tiles[i] = Tile(getTile(c, i));
  }

  count = getVirusCount(c);
  viruses.clear();
  viruses.resize(count);
  for(int i = 0; i < count; i++)
  {
    viruses[i] = Virus(getVirus(c, i));
  }

  if(!initialized)
  {
    initialized = true;
    init();
  }
  return run();
}

BaseAI::BaseAI(Connection* conn) : c(conn) {}
BaseAI::~BaseAI() {}
