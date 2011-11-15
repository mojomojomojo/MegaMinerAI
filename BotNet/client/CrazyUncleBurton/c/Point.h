#ifndef __POINT_H__
#define __POINT_H__

#include <iostream>
using namespace std;

typedef uint8_t coord_t;

// point
class Point {
public:
  coord_t x;
  coord_t y;

  Point() : x(255), y(255) {}
  Point( uint8_t _x, uint8_t _y ) : x(_x), y(_y) {}
  inline bool bad() { return x==255 && y==255; }
  inline friend ostream& operator<<(ostream& o, const Point& p) { o << "(" << (int)p.x << "," << (int)p.y << ")"; }
  inline bool operator==( const Point& p ) { return x==p.x && y == p.y; }
  inline bool operator!=( const Point& p ) { return !(*this == p); }
};

#endif // __POINT_H__
