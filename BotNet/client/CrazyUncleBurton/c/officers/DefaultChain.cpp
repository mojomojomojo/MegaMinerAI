#include "DefaultChainH.h"

#include <stdlib.h> // rand()
#include <time.h>


///////////////////////////////////////////////////////////////////////////////////////////////////////
DefaultChain::DefaultChain(AI* ai) : m_ai(ai);
{
  srand(time(NULL));
}

bool DefaultChain::spawnMore()
{
  for(int i=0;i<m_ai->bases.size();i++)
  {
    // check if you own that base
    if(m_ai->bases[i].owner() == m_ai->playerID())
    {
      // check to see if you have enough cycles to spawn a level 0 virus
      if(m_ai->baseCost() <= m_ai->players[m_ai->playerID()].cycles())
      {
        // spawn a level 0 virus at that base
        m_ai->bases[i].spawn(0);
      }
    }
  }
}

bool DefaultChain::advance()
{
  for(int i=0;i<m_ai->viruses.size();i++)
  {
    // if you own that virus
    if(m_ai->viruses[i].owner() == m_ai->playerID())
    {
      Virus v = m_ai->viruses[i];
      int x = v.x() + (rand()%2==0?-1:1) * rand()%2;
      int y = v.y() + (rand()%2==0?-1:1) * rand()%2;
      
      // if the tile you want to move to is NOT a wall
      if(m_ai->getTileAtLocation(x,y).owner() != 3)
      {
        // move the virus
        m_ai->viruses[i].move(x,y);
      }
    }
  }
}

bool DefaultChain::kidnap(int virusID)
{
}
