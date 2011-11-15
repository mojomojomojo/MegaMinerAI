#include <stdint.h>

#include <vector>
using namespace std;


typedef uint16_t EdgeCost;
#define EdgeFar 0xFFFE
#define EdgeInf 0xFFFF

typedef enum {
  FoundPath,
  NoPath,
  NoPathRightNow,
} PathType;

// point
class Point {
public:
  uint8_t x;
  uint8_t y;

  Point() : x(255), y(255) {}
  Point( uint8_t _x, uint8_t y ) : x(_x), y(_y) {}
};

Path* path_astar( MapCode** map, Point start, Point end );

class Path {
public:
  Point *start;
  Point *end;
  vector<Point> nodes;

  inline bool isGood() { return _info == FoundPath; }
  inline bool isBlockedByMovable() { return _info == NoPathRightNow; }
  inline bool isNoPath() { return _info == NoPath; }

protected:
  PathType _info;
}
