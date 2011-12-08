#include "Officer.h"
#include "officerutil.h"

#include <assert.h>

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

uint16_t Officer::next_issue_id = 0;

void Officer::init( AI *ai ) {
  _ai = ai;
}

void Officer::Command() {
  LogBlank();
  PersonalMemoirs("Officer::Command()...");

  // Remove any dead viruses from the payroll.
  // Update the map object.
  NotifySuperiors("Reclassifying ex-units.");
  update(); // Handle my own units.
  // (Call Officer::update() to update() all subordinates.)


  // Reevaluate based on how many units are still around.
  NotifySuperiors("Re-evaluating strategy.");
  reevaluateStrategy(ReevaluateAfterCasualties); 
  // (Call Officer::reevaluateStrategy() to process all subordinates.)


  // Walk through each underling, getting a list of viruses to spawn.
  // Order my units first (naturally, I'm more important).
  // Recursively give all subordinates (and theirs) a chance to spawn.
  NotifySuperiors("Spawning troops.");
  spawnMore();


  NotifySuperiors("Re-evaluating strategy (after spawning).");
  reevaluateStrategy(ReevaluateAfterSpawning); 
  // Allow underlings to reevaluate their strategies.


  // Give orders to employed units.
  NotifySuperiors("Commanding troops.");
  advance();
  // consider having a two-step approach, if you need other units to go first.

  return;
}

void Officer::reevaluateStrategy( int phase ) {
  PersonalMemoirs("Officer::reevaluateStrategy()...");

  // Allow underlings to reevaluate their strategies.
  // Call Officer::reevaluateStrategy() in any subclass's implementation.
  for (vector<Officer*>::iterator underling = _subordinates.begin();
       underling != _subordinates.end();
       underling++) {
    (*underling)->reevaluateStrategy(phase);
  }
}

bool Officer::isEmployed( int unitID ) {
  vector<int>::iterator unused;
  return isEmployed(unitID,unused);
}

bool Officer::isEmployed( int unitID, vector<int>::iterator& dogtag ) {
  for (vector<int>::iterator v = _employedUnits.begin();
       v != _employedUnits.end();
       v++) {
    if ( *v == unitID ) {
      dogtag = v;
      return true;
    }
  }
  return false;
}

bool Officer::numEmployed() {
  return _employedUnits.size();
}


// Spawn a unit at the specified base.
// Reserve it for the officer (arg).
// Assign it to that officer in update()
bool Officer::requisitionUnit( int level, Base base, Officer *requisitioner ) {
  PersonalMemoirs("Officer::requisitionUnit()...");
  if (_commander) {
    return _commander->requisitionUnit(level,base,requisitioner);
  }

  // Ensure the spawn will succeed.
  if (baseCanSpawn(base,_ai->_map) && _ai->canAffordVirus(_minLvl)) {
    _NotifySuperiors("Requisitioning a level "<<level<<" virus for "
                     <<requisitioner->_ofcname<<"."<<requisitioner->_id
                     <<" at "<<base);

    _requisitions[base.id()] = requisitioner;
    base.spawn(level);
    return true;
  } else {
    return false;
  }
}


// It should be called at the end of any subclass's spawnMore().
bool Officer::spawnMore() {
  PersonalMemoirs("Officer::spawnMore()...");

  bool saveMoneyInstead = false;


  vector<Base> randomBase = RandomMyBaseOrdering(_ai);
  // While:
  //   we don't have enough
  //   we can still spawn more
  //   we can afford the minimum level virus

  _TakeNotes("Employed: "<<_employedUnits.size()<<", Wanted: "<<_unitsWanted
             <<", SpawnsLeft: "<<_ai->spawnsLeft()<<", Afford("<<(int)_minLvl
             <<")?: "<<_ai->canAffordVirus(_minLvl)
             <<", Cost:"<<_ai->virusCost(_minLvl)
             <<", Cycles:"<<_ai->players[_ai->playerID()].cycles());

  int passes = 0,
      max_passes = _ai->bases.size()*_ai->bases.size(); // just in case
  while ((_employedUnits.size() < _unitsWanted) &&
         _ai->spawnsLeft() > 0 &&
         _ai->canAffordVirus(_minLvl)
         ) {
    if (passes++ > max_passes) break; // just in case

    bool spawnsRemain = false;
    for (vector<Base>::iterator base = randomBase.begin();
         base != randomBase.end();
         base++) {
      if (baseCanSpawn(*base,_ai->_map)) {
        spawnsRemain = true;
        requisitionUnit(_minLvl,(*base),this);
      } else {
        _TakeNotes("Base cannot spawn: "<<*base);
      }
    }
    // An occupied base that can spawn is the consideration here.
    if (!spawnsRemain) {
      saveMoneyInstead = true;
      break;
    }
  }

  if (saveMoneyInstead ||
      ((numEmployed() < unitsWanted()) && !_ai->canAffordVirus(_minLvl))) {
    // Don't let subordinates spawn. We're saving up our cycles.
    return false;
  }

  // spawn my own viruses (subclasses should implement this, then call the
  //   superclass's method to recurse)
  // The subclass really needs to implement this so that it can choose
  //   which base to spawn from.

  for (vector<Officer*>::iterator underling = _subordinates.begin();
       underling != _subordinates.end();
       underling++) {
    // Don't bother trying if there aren't any spawns available.
    if (_ai->spawnsLeft() == 0 || saveMoneyInstead) break;

    // If more are needed and we're not saving money, buy more.
    if (((*underling)->numEmployed() < (*underling)->unitsWanted()) &
        !saveMoneyInstead) {
        // If this returns true, it was able to spawn (or decide it didn't
        //   want to).
        if (!(*underling)->spawnMore()) {
          saveMoneyInstead = true;
          continue;
        }
    }
  }

  if (saveMoneyInstead) return false; // stop all spending

  for (vector<Officer*>::iterator underling = _subordinates.begin();
       underling != _subordinates.end();
       underling++) {
    if (!(*underling)->spawnMore()) {
      saveMoneyInstead = true;
    }
  }
  // If one of our underlings wants to save up, make it so.
  return !saveMoneyInstead; // a false return value means don't spend anything
}

// This function only calls update() of this officer's underlings.
// This should be called at the end of any subclass's update(),
//   though it probably doesn't need to be implemented.
bool Officer::update() {
  PersonalMemoirs("Officer::update()...");

  // Add new units.
  if (!_commander) {
    for (map<int,Officer*>::iterator req = _requisitions.begin();
         req != _requisitions.end();
         req++) {
      Virus *recruit = _ai->locateVirusAtBase((*req).first);
      if (!recruit) {
        _NotifySuperiors("Requisitioned unit is not found at base ID "
                         <<(*req).first<<" for "<<*((*req).second));
        continue;
      }
      assert(recruit!=NULL); // Don't crash on accident. Do it on purpose.

      _NotifySuperiors("Assigning new recruit "<<*recruit<<" to "
                       <<(*req).second->_ofcname<<"."<<(*req).second->_id);

      (*req).second->_employedUnits.push_back(recruit->id());
      _TakeNotes((*req).second->_ofcname<<"."<<(*req).second->_id
                 <<" now has "<<(*req).second->_employedUnits.size()<<" units: "
                 <<vectorToList((*req).second->_employedUnits));
    }
  }
  _requisitions.erase(_requisitions.begin(),_requisitions.end());


  // Update my rosters.
  for (vector<int>::iterator emp = _employedUnits.begin();
       emp != _employedUnits.end();
       emp++) {
    bool employeeAlive = false;
    for (vector<Virus>::iterator v = _ai->viruses.begin();
         v != _ai->viruses.end();
         v++) {
      if ((*v).id() == *emp) {
        employeeAlive = true;
        break;
      }
    }

    // Remove him from the roster.
    if (!employeeAlive) {
      _employedUnits.erase(emp,emp);
    }
  }

  // Do my underlings.
  for (vector<Officer*>::iterator underling = _subordinates.begin();
       underling != _subordinates.end();
       underling++) {
    (*underling)->update();
  }
}

// This function only calls advance() of this officer's underlings.
// This should be called at the end of any subclass's advance().
bool Officer::advance() {
  PersonalMemoirs("Officer::advance()...");

  // Issue orders to my units.

  // List all units in my employ.
  CLEAR_DEBUG_STREAM;
  _DS("Employed Units: ");
  for (vector<int>::iterator u = _employedUnits.begin();
       u != _employedUnits.end();
       u++) {
    if (u != _employedUnits.begin()) _DS(", ");
    _DS(*u);
  }
  TakeNotes(DEBUG_STRING);

  // Do my underlings.
  for (vector<Officer*>::iterator underling = _subordinates.begin();
       underling != _subordinates.end();
       underling++) {
    (*underling)->advance();
  }
}


bool Officer::conscript( vector<Officer*>::iterator start,
                         vector<Officer*>::iterator end ) {
  PersonalMemoirs("Officer::conscript()...");

  // Conscript for myself.

  // Do my underlings.
  for (vector<Officer*>::iterator underling = _subordinates.begin();
       underling != _subordinates.end();
       underling++) {
    (*underling)->conscript(start,end);
  }
}


void Officer::addSubordinate( Officer* o ) {
  _subordinates.push_back(o);
  o->_commander = this;
  o->_ai = _ai;
}


bool Officer::baseCanSpawn( Base& b, const Map& map ) {
  if (b.spawnsLeft() == 0) {
    _ProtectAgainstWarTrials("  *Base "<<b<<" has no spawns remaining.");
    return false;
  }
  
  for (vector<Virus>::iterator virus = map.m_parent->viruses.begin();
       virus != map.m_parent->viruses.end();
       virus++) {
    if ((*virus).x() == b.x() && (*virus).y() == b.y()) {
      _ProtectAgainstWarTrials("  *Base "<<b<<" has a virus in it: "<<*virus);
      return false;
    }
  }
  return true;
}


ostream& operator<<(ostream& stream, const Officer& o) {
  stream << "[Officer '"<<o._ofcname<<"."<<o._id<<"]";
}

  // Get a list of all units that can be conscripted by a higher-precedence
  //   duty's CO.
  // tail-recursive ('list' is an output parameter)
  // Each recipient should find all lower priority groups and list all the
  //   units employed by each. (No duplicates should be allowed.)
  // If requester_co is null, assume it's the same as the requester.
void Officer::getConscriptList( Officer* requester,
                                vector<int> &list,
                                Officer *requester_co
                                ) {
  if (!requester_co) requester_co = requester;

  // Have my commander check all his subordinate officers whose tasks
  //   are a lower priority than mine.
  if (requester_co != this) {
    // find all lower-precedence jobs (than the requester_co) and
    //   have them list all available conscripts.

    bool found_requester_co = false;
    for (vector<Officer*>::iterator sub = _subordinates.begin();
         sub != _subordinates.end();
         sub++) {
      if (!found_requester_co && *sub == requester_co) {
        found_requester_co = true;
        continue;
      } else if (found_requester_co) {
        (*sub)->listAvailableConscripts(list);
      }
    }
  } else {
    // If I'm calling this on myself.
    for (vector<Officer*>::iterator sub = _subordinates.begin();
         sub != _subordinates.end();
         sub++) {
      (*sub)->listAvailableConscripts(list);
    }
  }

  // No commander (i.e. I am the Chief Commander): recursion ends.
  if (_commander == NULL) return;

  // Pass it up the chain of command.
  _commander->getConscriptList(requester,list,this);
 
}

void Officer::listAvailableConscripts( vector<int>& roster ) {
}



#ifdef _DEBUG_OFFICER

void Officer::CaptainsLog( int lvl, string msg, bool eol ) {
  if (lvl >= _LogLevel) return;

  if (_ai) cout << "[T " << setw(3) << (_ai->turnNumber()+1)
                << "; P " << _ai->playerID() << "] ";
  cout << "[" << _ofcname << "." << _id;
  if (_commander) 
    cout << " (CO:" << _commander->_ofcname << "." << _commander->_id << ")";
  cout << " " << setw(2) << lvl << "/" << _LogLevel << "] " << msg;
  if (eol) cout << endl;
}

#endif // _DEBUG_OFFICER

