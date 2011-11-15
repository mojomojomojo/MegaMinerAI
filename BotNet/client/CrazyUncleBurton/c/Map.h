#ifndef MAPH_H
#define MAPH_H

#include<stdint.h>
#include<iostream>
#include<fstream>
#include<vector>
#include<list>
#include<ctime>
#include "AI.h"
#include "config.h"
#include "Point.h"
#include "EnumsH.h"
#include "path.hpp"
#include <stdlib.h>

class AI;
class Point;

class Cluster;

class Map
{
public:
	MAPCODE** m_grid;
	bool** m_clustered;
	int8_t m_width;
	int8_t m_height;
	AI* m_parent;
	std::vector<Cluster> m_clusters;
	
	Map();
	Map(AI* parent); //Creates an empty map
	
	int8_t width();
	int8_t height();
	
	MAPCODE at(const int8_t x, const int8_t y);
	
	void update();
	
	bool legal(const int8_t x, const int8_t y);
	Direction_t nearestEmpty(const int x, const int y, const int radius = 0);
	std::vector<Point> seekBottleneck();
};

class Cluster
{
public:
	MAPCODE m_type;
	int8_t m_size;
	int8_t m_virusCount;
	MAPCODE** m_active;
	
	Cluster(MAPCODE mapcode);
	
	static std::vector<Cluster> extract(Map& map);
	void grow(const int i, const int j, Map& map);
	
	float virusDensity();
};



std::ostream& operator<<(std::ostream& out, Map& map);
std::ostream& operator<<(std::ostream& out, Cluster& cluster);

#endif
