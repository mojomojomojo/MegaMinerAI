#ifndef __OFFICER_UTIL__
#define __OFFICER_UTIL__

#include "Point.h"
#include "Officer.h"

#include <vector>
#include <algorithm>
#include <sstream>
using namespace std;

inline vector<Base> RandomBaseOrdering( vector<Base>& source ) {
    // Pick a random base that has spawns remaining.
    vector<int> randomOrder;
    for (int i=0; i<source.size(); i++) {
      randomOrder.push_back(rand()%10000 * 100 + i);
    }
    sort(randomOrder.begin(),randomOrder.end());

    vector<Base> randomBase;
    for (int i=0; i<source.size(); i++) {
      randomBase.push_back(source[randomOrder[i] % 100]);
    }
    return randomBase;
}

inline vector<Base> RandomMyBaseOrdering( AI* ai ) {
  return RandomBaseOrdering( ai->myBases );
}

//template <typename T>
inline string vectorToList( const vector<int>& v ) {
  stringstream s(stringstream::out);
  for (vector<int>::const_iterator i = v.begin();
       i != v.end();
       i++) {
    if (i != v.begin()) s << ", ";
    s << *i;
  }
  return s.str();
};

inline Point north( const Point& p ) { return Point(p.x,   p.y-1); }
inline Point south( const Point& p ) { return Point(p.x,   p.y+1); }
inline Point east( const Point& p )  { return Point(p.x+1, p.y); }
inline Point west( const Point& p )  { return Point(p.x-1, p.y); }
inline Point go( const Point& p, Direction_t d ) {
  if (d == North) return north(p);
  if (d == South) return south(p);
  if (d == East)  return east(p);
  if (d == West)  return west(p);
  return Point(255,255);
}

#endif // __OFFICER_UTIL__
