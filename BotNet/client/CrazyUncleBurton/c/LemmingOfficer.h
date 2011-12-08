#ifndef __LEMMING_OFFICER__
#define __LEMMING_OFFICER__

#include "Officer.h"

class LemmingOfficer : public Officer
{
public:
  //  bool spawnMore();
  bool advance();

  inline Direction_t marchDir( Direction_t dir = NumDirections ) {
    if (dir != NumDirections) _marchDir = dir;
    return _marchDir;
  }

 protected:
  Direction_t _marchDir;
};

#endif // __LEMMING_OFFICER__
