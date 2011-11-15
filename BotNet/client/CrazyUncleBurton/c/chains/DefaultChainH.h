#ifndef DEFAULTCHAINH_H
#define DEFAULTCHAINH_H

#include "ChainH.h"

class DefaultChain : public Chain_base
{
public:
	DefaultChain(AI* ai);
	bool spawnMore();
	bool advance();
	bool kidnap(int virusID);
};

#endif
