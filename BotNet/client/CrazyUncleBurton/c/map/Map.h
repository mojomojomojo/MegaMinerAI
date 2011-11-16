#ifndef __MAP_H__
#define __MAP_H__

#include<stdint.h>
#include<iostream>
#include<fstream>
#include "AI.h"
#include "config.h"

class AI;

typedef enum
{
	EMPTY,  // No one owns
	WALL,   // Can not traverse onto
	OPBASE, // My base
	MYBASE, // Opponents base
	OP,     // Opponent owned computer
	MY,      // a computer I own resides here
	MYVIRUS,
	OPVIRUS
}MAPCODE;

class Map
{
	public:
	MAPCODE ** m_grid;
	int8_t m_width;
	int8_t m_height;
	AI* m_parent;
	
	Map(const signed short x, const signed short y, AI* parent); //Creates an empty map
	Map(AI* parent); //Creates an empty map
	
	int8_t width();
	int8_t height();
	
	MAPCODE at(const int8_t x, const int8_t y);
	
	void update();
	
	bool legal(const int8_t x, const int8_t y);
	
	std::ostream& operator<<(std::ostream& out);
	
//	void init();
};

#endif // __MAP_H__
