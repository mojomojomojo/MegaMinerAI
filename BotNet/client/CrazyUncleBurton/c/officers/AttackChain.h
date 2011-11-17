#ifndef ATTACKCHAINH_H
#define ATTACKCHAINH_H

#include "ChainH.h"

class AttackChain : public Chain_base
{
public:
	AttackChain(AI* ai);
	bool spawnMore();
	bool advance();
	bool kidnap(int virusID);
};

#endif
