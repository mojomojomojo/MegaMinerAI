#include "Chain.h"

uint16_t Chain::next_issue_id = 0;

bool Chain::update()
{
  for (vector<int>::iterator my_v = m_virusIDs.begin();
       my_v != m_virusIDs.end();
       my_v++) {
    // If the vector doesn't exist in the existing virus list, remove it
    //   from my list.
    vector<Virus>::iterator found = findVirus(*my_v,m_ai->viruses);
    if (found != m_ai->viruses.end()) {
      m_virusIDs.erase(my_v);
    }
  }

  return true;
}

vector<Virus>::iterator findVirus( int id, vector<Virus>& vlist )
{
  for (vector<Virus>::iterator i = vlist.begin();
       i != vlist.end();
       i++) {
    if (id == (*i).id()) {
      return i;
    }
  }
  return vlist.end();
}

bool Chain::spawnMore()
{
  if(numDrones() < neededDrones())
    {
      if(true);
    }
}

bool Chain::advance()
{
}

bool Chain::kidnap( vector<Chain>::iterator start,
                    vector<Chain>::iterator end)
{
  return true;
}





