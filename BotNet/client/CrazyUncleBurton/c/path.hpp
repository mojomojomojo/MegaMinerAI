#ifndef __PATH_HPP__
#define __PATH_HPP__

#include <stdint.h>
#include "Map.h"
#include "Point.h"

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

typedef uint8_t coord_t;

typedef uint16_t EdgeCost;
#define EdgeFar 0xFFFE
#define EdgeInf 0xFFFF



// Calculate the coordinate in the corresponding direction.
// Return BAD_POINT (*.bad() == true) if we've exceeded the map.
Point go( Direction_t dir, coord_t x, coord_t y,
          coord_t width, coord_t height );


class PathTrack {
public:
  Point at;
  Point prev;
  EdgeCost dist;
  bool visited;
  bool queued;
  inline friend ostream& operator<<(ostream& out, PathTrack& p) {
    out << "[PathTrack At(" << p.at << ") D(" << p.dist << ") Prev("
        << p.prev << ")" << " V(" << p.visited << ") Q(" << p.queued << ")";
  }
};


typedef enum {
  AS_IgnoreViruses = 0,
  AS_DontCrossViruses = 1,
  AS_AllowImpassableEnd = 4,
} AStarBehavior_t;

class Path;
class Map;

Path* path_astar( Map map, Point start, Point end,
                  AStarBehavior_t behavior = AS_IgnoreViruses );

Path* pathToNearestTarget( Map map, Point start, vector<MAPCODE>& accept );

string asText( Map &m, Path& p, PathTrack **tracking = NULL );


// map.m_grid is a 2D array of MAPCODE ints.  

class Path {
public:
  Point start;
  Point end;
  vector<Point> nodes;

  inline bool isGood() { return _info == FoundPath; }
  inline bool isBlockedByMovable() { return _info == NoPathRightNow; }
  inline bool isNoPath() { return _info == NoPath; }

  inline friend ostream& operator<<( ostream& o, Path& p ) {
    o << "[Path Start(" << p.start << ") End(" << p.end << ") {";
    for (vector<Point>::iterator i = p.nodes.begin();
         i != p.nodes.end();
         i++) {
      if (i != p.nodes.begin()) o << " --> ";
      o << *i;
    }
    o << "}]";
  }

protected:
  PathType _info;
};

#endif // __PATH_HPP__
