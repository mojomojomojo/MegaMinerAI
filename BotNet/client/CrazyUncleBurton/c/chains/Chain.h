#ifndef CHAINH_H
#define CHAINH_H

#include<stdint.h>
#include<list>
#include<math.h>
#include "AI.h"

#include <vector>
using namespace std;


class Chain
{
public:
//	int16_t m_numDrones;
	int16_t m_neededDrones;
	int8_t m_minLv;
	int8_t m_maxLv;
	AI* m_ai;
	
	std::vector<int> m_virusIDs; // ID value of Viruses in assignment
	
	int16_t numDrones(){return m_virusIDs.size();}
	int16_t neededDrones(){return m_neededDrones;}
	
	inline int16_t costOfLvXVirus(const int lvX){
          return(m_ai->baseCost() * pow(m_ai->scaleCost(), lvX) );
        }
	
	virtual bool update();
	virtual bool spawnMore();
	virtual bool advance();
	virtual bool kidnap( vector<Chain>::iterator start,
                             vector<Chain>::iterator end);

        vector<Virus>::iterator findVirus( int id, vector<Virus>& vlist );
};






#endif
