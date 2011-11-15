#ifndef __THE_GENERAL__
#define __THE_GENERAL__

#include "AI.h"
#include "MapH.h"
#include "Chain.h"

#include <vector>
using namespace std;

class TheGeneral {
 public:
  const static int PhaseOne = 0;
  const static int PhaseTwo = 0;
  const static int PhaseThree = 0;

  inline AI* ai() { return _ai; }

  virtual void initChains(); // call from init(), subclasses should implement

  virtual void Command(); // call from run(), probably no need for subclasses to implement

  // called from Command(), subclasses should implement this
  virtual void reevaluatStrategy( int phase ); 

  inline TheGeneral() {}
  inline TheGeneral( AI *ai ) : _ai(ai) {}

#ifdef _DEBUG_THE_GENERAL
  int LogLevel( int lvl = -1 );

  // Log Levels
  static const int LOG_PressRelease = 1;
  static const int LOG_NotifySuperiors = 3;
  static const int LOG_NotifySubordinates = 4;
  static const int LOG_PersonalMemoirs = 7;
  static const int LOG_ProtectAgainstWarTrials = 9;

  void CaptainsLog( int lvl, string msg, bool eol = true );
  void OfficersLog( int lvl, string ofc_monik, string msg, bool eol = true );


  // These are nicknames for the various log levels.
#define LOG_NICKNAME(NICK)                                 \
  inline void NICK ( string msg, bool eol = true ) {       \
    CaptainsLog(LOG_ ## NICK ,msg,eol);                    \
  }

  LOG_NICKNAME(PressRelease);
  LOG_NICKNAME(NotifySuperiors);
  LOG_NICKNAME(NotifySubordinates);
  LOG_NICKNAME(PersonalMemoirs);
  LOG_NICKNAME(ProtectAgainstWarTrials);

#else

#define LogLevel(...)
#define CaptainsLog(...)
#define OfficersLog(...)

#define PressRelease(...)
#define NotifySuperiors(...)
#define NotifySubordinates(...)
#define PersonalMemoirs(...)
#define ProtectAgainstWarTrials(...)


#endif // _DEBUG_THE_GENERAL

 protected:
  vector<Chain> _chains;
  AI *_ai;

#ifdef _DEBUG_THE_GENERAL
  int _LogLevel;
#endif // _DEBUG_THE_GENERAL

};

#endif // __THE_GENERAL__
