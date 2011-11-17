#ifndef EXPLORECHAINH_H
#define EXPLORECHAINH_H

#include "ChainH.h"

class ExploreChain : public Chain_base
{
public:
	ExploreChain(AI* ai);
	bool spawnMore();
	bool advance();
	bool kidnap(int virusID);
};

#endif

