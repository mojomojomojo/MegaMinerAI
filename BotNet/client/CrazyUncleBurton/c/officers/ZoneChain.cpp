#include "ZoneChain.h"

#include "path.hpp"


class Zone {
public:
  static int last_issued_id;
  int id;
  coord_t min_x,max_x,min_y,max_y;

  inline Zone() : id(++last_issued_id) {}
  inline Zone(Point c1, Point c2) {
    Zone();
    if (c1.x < c2.x) {
      min_x = c1.x; max_x = c2.x;
    } else {
      min_x = c2.x; max_x = c1.x;
    }
    if (c1.y < c2.y) {
      min_y = c1.y; max_y = c2.y;
    } else {
      min_y = c2.y; max_y = c1.y;
    }
  }
  inline friend ostream& operator<<( ostream& o, const Zone& z) {
    o << "[Zone ID(" << id << ") LL" < ll << " UR" << ur << "]";
  }
};
Zone::last_issued_id = 0;

map<int,Zone> virusZoneAssignments;

bool inZone( Point& p, Zone& z) {
  return (p.x <= z.max_x && p.x >= z.min_x &&
          p.y <= z.max_y && p.x >= z.min_y);
}


virtual bool ZoneChain::spawnMore() {

}

virtual bool ZoneChain::advance() {
  for (vector<int>::iterator vid = m_virusIDs.begin();
       vid != m_virusIDs.end();
       vid++) {
    // Get the virus object.
    vector<Virus> v = findVirus(*vid,ai->viruses);

    
}

virtual bool ZoneChain::kidnap( vector<Chain_base>::iterator start,
                                vector<Chain_base>::iterator end) {
  return true;
}
