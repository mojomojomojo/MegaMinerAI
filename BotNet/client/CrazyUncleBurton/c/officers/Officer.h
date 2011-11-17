#ifndef __OFFICER__
#define __OFFICER__

#include "AI.h"
#include "Map.h"
#include "strutil.h"

#include <vector>
#include <sstream>
#include <map>
using namespace std;

class Officer {
 public:
  // Call this from AI::init(), subclasses should implement this.
  virtual void init( AI* ai ); 

  // Command all subordinate officers and units under my control.
  // Subclasses shouldn't need to implement this.
  void Command();

  // Called from Command(), subclasses should implement this.
  virtual void reevaluateStrategy( int phase ); 
  static const int ReevaluateAfterCasualties = 1;
  static const int ReevaluateAfterSpawning = 2;

  // Give this officer a subordinate officer.
  virtual void addSubordinate( Officer *o );

  // These actions all happen at the commander (no superior officer) level.
  // An officer should call this when he spawns a unit at a base.
  bool requisitionUnit( int level, Base base, Officer *requisitioner );

  // Update the list of employed viruses. Remove dead. Add new.
  virtual bool update();
  virtual bool spawnMore();
  virtual bool advance();
  virtual bool conscript( vector<Officer*>::iterator start,
                          vector<Officer*>::iterator end );



  inline Officer() : _id(next_issue_id++), _commander(NULL) {
#ifdef _DEBUG_OFFICER
    _ofcname = string("Officer ID#") + int16_t_str(_id);
#endif // _DEBUG_OFFICER
  }
  inline Officer( AI *ai ) : _id(next_issue_id++), _ai(ai), _commander(NULL) {
#ifdef _DEBUG_OFFICER
    _ofcname = string("Officer ID#") + int16_t_str(_id);
#endif // _DEBUG_OFFICER
  }
  inline Officer( const Officer& o ) : _id(o._id), _ai(o._ai),
    _subordinates(o._subordinates), _employedUnits(o._employedUnits),
    _unitsWanted(o._unitsWanted), _minLvl(o._minLvl), _maxLvl(o._maxLvl),
    _commander(o._commander)
#ifdef _DEBUG_OFFICER
    , _LogLevel(o._LogLevel), _ofcname(o._ofcname)
#endif // _DEBUG_OFFICER
  {}
  inline Officer& operator=( const Officer& o ) {
    _id = o._id;
    _ai = o._ai;
    _subordinates = o._subordinates;
    _employedUnits = o._employedUnits;
    _unitsWanted = o._unitsWanted;
    _minLvl = o._minLvl;
    _maxLvl = o._maxLvl;
    _commander = o._commander;
#ifdef _DEBUG_OFFICER
    _LogLevel = o._LogLevel;
    _ofcname = o._ofcname;
#endif // _DEBUG_OFFICER
  }

  // data member access methods
  inline AI* ai() { return _ai; }
  inline vector<Officer*>& subordinates() { return _subordinates; }
  inline int16_t unitsWanted( int16_t wanted = -1 ) {
    if (wanted != -1) _unitsWanted = wanted;
    return _unitsWanted;
  }
  inline int8_t minLevel( int8_t minLvl = -1 ) {
    if (minLvl != -1) _minLvl = minLvl;
    return _minLvl;
  }

  // Search for an employed virus.
  bool isEmployed( int unitID );
  bool isEmployed( int unitID, vector<int>::iterator& dogtag );
  bool numEmployed();

  bool baseCanSpawn( Base& b, const Map& map );

  friend ostream& operator<<(ostream& stream, const Officer& o);

 protected:
  vector<Officer*> _subordinates;
  map<int,Officer*> _requisitions;

  AI *_ai;

  vector<int> _employedUnits;

  int16_t _unitsWanted;
  int8_t _minLvl, _maxLvl;

  Officer* _commander;
  uint16_t _id;

  static uint16_t next_issue_id;

 public:
#ifdef _DEBUG_OFFICER
  inline int LogLevel( int lvl = -1 ) {
    if (lvl >= 0) _LogLevel = lvl;
    return _LogLevel;
  }

  // Log Levels
  static const int LOG_PressRelease = 1;
  static const int LOG_NotifySuperiors = 3;
  static const int LOG_NotifySubordinates = 4;
  static const int LOG_PersonalMemoirs = 7;
  static const int LOG_TakeNotes = 8;
  static const int LOG_ProtectAgainstWarTrials = 9;

  virtual void CaptainsLog( int lvl, string msg, bool eol = true );

#define CLEAR_DEBUG_STREAM _dbgstream.str("")
#define _DS(x) _dbgstream << x
#define DEBUG_STRING _dbgstream.str()

  // These are nicknames for the various log levels.
#define LOG_NICKNAME(NICK)                                 \
  inline void NICK ( string msg, bool eol = true ) {       \
    CaptainsLog(LOG_ ## NICK ,msg,eol);                    \
  }

  LOG_NICKNAME(PressRelease);
  LOG_NICKNAME(NotifySuperiors);
  LOG_NICKNAME(NotifySubordinates);
  LOG_NICKNAME(PersonalMemoirs);
  LOG_NICKNAME(TakeNotes);
  LOG_NICKNAME(ProtectAgainstWarTrials);

#define _PressRelease(...) CLEAR_DEBUG_STREAM;_DS(__VA_ARGS__);PressRelease(DEBUG_STRING);
#define _NotifySuperiors(...) CLEAR_DEBUG_STREAM;_DS(__VA_ARGS__);NotifySuperiors(DEBUG_STRING);
#define _NotifySubordinates(...) CLEAR_DEBUG_STREAM;_DS(__VA_ARGS__);NotifySubordinates(DEBUG_STRING);
#define _PersonalMemoirs(...) CLEAR_DEBUG_STREAM;_DS(__VA_ARGS__);PersonalMemoirs(DEBUG_STRING);
#define _TakeNotes(...) CLEAR_DEBUG_STREAM;_DS(__VA_ARGS__);TakeNotes(DEBUG_STRING);
#define _ProtectAgainstWarTrials(...) CLEAR_DEBUG_STREAM;_DS(__VA_ARGS__);ProtectAgainstWarTrials(DEBUG_STRING);

  inline void LogBlank() { cout << endl; }

  inline void setOfficerName( string name ) {
    _ofcname = name;
  }

 protected:
  int _LogLevel;
  string _ofcname;
  stringstream _dbgstream; // no copy/assignment semantics

#else

  inline int LogLevel( int lvl = -1 ) {}
  inline void CaptainsLog( int lvl, string msg, bool eol = true ) {};
  inline void LogBlank() {}

#define LOG_NICKNAME(NICK)                                 \
  inline void NICK ( string msg, bool eol = true ) {}

  LOG_NICKNAME(PressRelease);
  LOG_NICKNAME(NotifySuperiors);
  LOG_NICKNAME(NotifySubordinates);
  LOG_NICKNAME(PersonalMemoirs);
  LOG_NICKNAME(TakeNotes);
  LOG_NICKNAME(ProtectAgainstWarTrials);

  inline void setOfficerName( string name ) {}

#define CLEAR_DEBUG_STREAM
#define _DS(x)
#define DEBUG_STRING ""
#define __DEBUG(...)

#define _PressRelease(...) 
#define _NotifySuperiors(...)
#define _NotifySubordinates(...)
#define _PersonalMemoirs(...) 
#define _TakeNotes(...) 
#define _ProtectAgainstWarTrials(...) 


#endif // _DEBUG_OFFICER

};

#endif // __OFFICER__
