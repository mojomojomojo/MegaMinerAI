#ifndef __COVERAGE_OFFICER__
#define __COVERAGE_OFFICER__

#include "Officer.h"
#include "Point.h"
#include "path.hpp"

#include <map>

class CoverageOfficer : public Officer
{
public:
  //  bool spawnMore();
  bool advance();

  // These constants determine the start and direction of the search.
  static const int CW = 1;
  static const int CCW = -1;

  static const int North = 0;
  static const int NorthEast = 1;
  static const int East = 2;
  static const int SouthEast = 3;
  static const int South = 4;
  static const int SouthWest = 5;
  static const int West = 6;
  static const int NorthWest = 7;

  static const int NumDirs = 8; // for programmatically looping.

  // cDir: cardinal direction - one of the 8 adjacent points
  // aDir: angular direction - clockwise or counterclockwise
  static int NextDir( int cDir, int aDir );
  Point go( Direction_t dir, coord_t x, coord_t y,
            coord_t width, coord_t height );
  bool impassable( MAPCODE c );

  Path* pathToNearestTarget( Map map, Point start, vector<MAPCODE>& acceptPri,
                             int cDir, int aDir );

 protected:
  std::map<int,int> _searchInfo; // virusid_t => search_orient/search_dir
  int[8] _searchDist; // internal - used to keep track of the number of
                      //   units assigned to that search dir/orient.

  
};

#endif // __COVERAGE_OFFICER__
