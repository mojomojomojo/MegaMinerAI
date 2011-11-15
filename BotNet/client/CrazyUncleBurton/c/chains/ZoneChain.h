#ifndef __ZONE_CHAIN__
#define __ZONE_CHAIN__

#include "AI.h"
#include "Chain.h"

class ZoneChain : public Chain {
 public:
  ZoneChain( AI *ai );

  virtual bool spawnMore();
  virtual bool advance();
  virtual bool kidnap( vector<Chain>::iterator start,
                       vector<Chain>::iterator end );
};


#endif // __ZONE_CHAIN__
