#ifndef CHAINH_H
#define CHAINH_H

#include<stdint.h>
#include<list>
#include<math.h>
#include "AI.h"
#include "TheGeneral.h"

#include <vector>
using namespace std;

class TheGeneral;

class Chain
{
public:
  int16_t m_neededDrones;
  int8_t m_minLv;
  int8_t m_maxLv;
  AI* m_ai;
  TheGeneral* _commander;
  uint16_t _id;

  std::vector<int> m_virusIDs; // ID value of Viruses in assignment
  Chain() : _id(next_issue_id++) {}; // have the subclass constructor call this

	
  int16_t numDrones(){return m_virusIDs.size();}
  int16_t neededDrones(){return m_neededDrones;}
	
  inline int16_t costOfLvXVirus(const int lvX){
    return(m_ai->baseCost() * pow(m_ai->scaleCost(), lvX) );
  }
	
  virtual bool update();
  virtual bool spawnMore();
  virtual bool advance();
  virtual bool kidnap( vector<Chain>::iterator start,
                       vector<Chain>::iterator end);

  vector<Virus>::iterator findVirus( int id, vector<Virus>& vlist );

  inline uint16_t id() { return _id; }

 protected:
  static uint16_t next_issue_id;

#ifdef _DEBUG_THE_GENERAL
  int LogLevel( int lvl = -1 );

  string _ofcName

  // These are nicknames for the various log levels.
#define LOG_NICKNAME(NICK)                                 \
  inline void NICK ( string msg, bool eol = true ) {       \
    OfficersLog(LOG_ ## NICK ,msg,eol);                    \
  }

  LOG_NICKNAME(PressRelease);
  LOG_NICKNAME(NotifySuperiors);
  LOG_NICKNAME(NotifySubordinates);
  LOG_NICKNAME(PersonalMemoirs);
  LOG_NICKNAME(ProtectAgainstWarTrials);
  
#else

#endif // _DEBUG_THE_GENERAL

};






#endif
