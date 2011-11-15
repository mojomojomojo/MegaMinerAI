#include "MapH.h"

Cluster::Cluster(MAPCODE mapcode) : m_type(mapcode), m_size(0), m_virusCount(0)
{
	m_active = new MAPCODE*[40]; // x
	for(int i = 0; i < 40; i++)
	{
		m_active[i] = new MAPCODE[20]; // y
		for(int j = 0; j < 20; j++)
		{
			m_active[i][j] = VOID;
		}
	}
}

std::vector<Cluster> Cluster::extract(Map& map)
{
	char dummy;
	std::vector<Cluster> ToReturn;
	for(int i = 0; i < map.width(); i++)
		for(int j= 0; j < map.height(); j++)
		{
			if(!map.m_clustered[i][j] && map.m_grid[i][j] != WALL && map.m_grid[i][j] != OPBASE && map.m_grid[i][j] != MYBASE)
			{
				// set the type
			//	m_type = map.m_grid[i][j];
std::cout << "Calling cluster on " << int(map.m_grid[i][j]) << std::endl;
//std::cin >> dummy;
				Cluster newCluster(map.m_grid[i][j]);
				if(newCluster.m_type == MYVIRUS) newCluster.m_type = MY;
				if(newCluster.m_type == OPVIRUS) newCluster.m_type = OP;
				newCluster.grow(i,j, map);
				ToReturn.push_back(newCluster);
			}
		}
	return ToReturn;
}

void Cluster::grow(const int i, const int j, Map& map)
{
	map.m_clustered[i][j] = true;
	m_active[i][j] = m_type;
	m_size++;
	
	char dummy;
	
	if(map.m_grid[i][j] == MYVIRUS || map.m_grid[i][j] == OPVIRUS)
		m_virusCount++;
	
	// I-1 J
	if(	map.legal(i-1,j) && 
		!map.m_clustered[i-1][j] && 
		(
			map.m_grid[i-1][j] == m_type || 
			(m_type == MY && map.m_grid[i-1][j] == MYVIRUS) || 
			(m_type == OP && map.m_grid[i-1][j] == OPVIRUS)
		) 
	)
	{
//std::cout << "growing left" << std::endl;
		grow(i-1,j,map);
	}
	// I+1 J
	if(	map.legal(i+1,j) && 
		!map.m_clustered[i+1][j] && 
		(
			map.m_grid[i+1][j] == m_type || 
			(m_type == MY && map.m_grid[i+1][j] == MYVIRUS) || 
			(m_type == OP && map.m_grid[i+1][j] == OPVIRUS)
		) 
	)
	{
//std::cout << "growing right" << std::endl;
		grow(i+1,j,map);
	}
	// I J-1
	if(	map.legal(i,j-1) && 
		!map.m_clustered[i][j-1] && 
		(
			map.m_grid[i][j-1] == m_type || 
			(m_type == MY && map.m_grid[i][j-1] == MYVIRUS) || 
			(m_type == OP && map.m_grid[i][j-1] == OPVIRUS)
		) 
	)
	{
//std::cout << "growing down" << std::endl;
		grow(i,j-1,map);
	}
	// I J+1
	if(	map.legal(i,j+1) && 
		!map.m_clustered[i][j+1] && 
		(
			map.m_grid[i][j+1] == m_type || 
			(m_type == MY && map.m_grid[i][j+1] == MYVIRUS) || 
			(m_type == OP && map.m_grid[i][j+1] == OPVIRUS)
		) 
	)
	{
//std::cout << "growing up" << std::endl;
		grow(i,j+1,map);
	}
}

float Cluster::virusDensity()
{
	return(float(m_virusCount) / m_size);
}

Map::Map() : m_parent(NULL), m_grid(NULL), m_clustered(NULL), m_width(0), m_height(0)
{

}

Map::Map(AI* parent) : m_width(parent->width()), m_height(parent->height()), m_parent(parent)
{
	m_grid = new MAPCODE*[width()];
	for(int i = 0; i < width(); i++)
	{
		m_grid[i] = new MAPCODE[height()];
		for(int j = 0; j < height(); j++)
		{
			m_grid[i][j] = EMPTY;
		}
	}
	
	m_clustered = new bool*[width()];
	for(int i = 0; i < width(); i++)
	{
		m_clustered[i] = new bool[height()];
		for(int j = 0; j < height(); j++)
		{
			m_clustered[i][j] = false;
		}
	}
	
	update();
}

int8_t Map::width()
{
	return m_width;
}

int8_t Map::height()
{
	return m_height;
}

MAPCODE Map::at(const int8_t x, const int8_t y)
{
	return m_grid[x][y];
}

void Map::update()
{
	for(int i = 0; i < width(); i++)
		for(int j = 0; j < height(); j++)
			m_grid[i][j] = EMPTY;

	// Grab the tile info
	for(int i = 0; i < m_parent->tiles.size(); i++)
	{
		if(m_parent->tiles[i].owner() == m_parent->playerID() )
		{
			m_grid[m_parent->tiles[i].x()][m_parent->tiles[i].y()] = MY;
		}
		else if (m_parent->tiles[i].owner() == 3) // FIREWALL
		{
			m_grid[m_parent->tiles[i].x()][m_parent->tiles[i].y()] = WALL;
		}
		else if (m_parent->tiles[i].owner() == 2) // No One
		{
			m_grid[m_parent->tiles[i].x()][m_parent->tiles[i].y()] = EMPTY;
		}
		else
		{
			m_grid[m_parent->tiles[i].x()][m_parent->tiles[i].y()] = OP;
		}
	}
	
	// grab virus info
	for(int i = 0; i < m_parent->viruses.size(); i++)
	{
		if(m_parent->viruses[i].owner() == m_parent->playerID() )
		{
			m_grid[m_parent->viruses[i].x()][m_parent->viruses[i].y()] = MYVIRUS;
		}
		else
		{
			m_grid[m_parent->viruses[i].x()][m_parent->viruses[i].y()] = OPVIRUS;
		}
	}
	
	// set the bases
	for(int i = 0; i < m_parent->bases.size(); i++)
	{
		if(m_parent->bases[i].owner() == m_parent->playerID() )
		{
			m_grid[m_parent->bases[i].x()][m_parent->bases[i].y()] = MYVIRUS;
		}
		else
		{
			m_grid[m_parent->bases[i].x()][m_parent->bases[i].y()] = OPVIRUS;
		}
	}
	
//	m_clusters = Cluster::extract(*this);
}
	
bool Map::legal(const int8_t x, const int8_t y)
{
	if(x < 0 || y < 0)
		return false;
	if(x > 39 || y > 19)
		return false;
	return(m_grid[x][y] == EMPTY || m_grid[x][y] == MY || m_grid[x][y] == OP);
}


std::vector<Point> Map::seekBottleneck()
{
	std::vector<Point> ToReturn;
	
	for(int i = 1; i < 39; i++)
	{
		for(int j = 1; j < 19; j++)
		{
			if(!legal(i-1,j) && !legal(i+1,j))
			{
				 Point tmp(i,j);
				 ToReturn.push_back(tmp);
			}
			else if(!legal(i,j-1) && !legal(i,j+1))
			{
				 Point tmp(i,j);
				 ToReturn.push_back(tmp);
			}
		}
	}
	return ToReturn;
}



Direction_t Map::nearestEmpty(const int x, const int y, const int r)
{
	int SolX = -1, SolY = -1;
		
	for(int i = 0; i < r; i++)
	{
		// NORTH
		for(int j = x - r + 1; j < x + r; j++) // walk through j => x
		{
			if(legal(j, y+r) && m_grid[j][j+r] == EMPTY)
			{
				SolX = j;
				SolY = y+r;
				break;
			}
		}
		// WEST
		for(int j = y - r + 1; j < y + r; j++) // walk through j => y
		{
			if(legal(x-r, j) && m_grid[x-r][j] == EMPTY)
			{
				SolX = y-r;
				SolY = j;
				break;
			}
		}
		// EAST
		for(int j = y - r + 1; j < y + r; j++) // walk through j => y
		{
			if(legal(x+r, j) && m_grid[x+r][j] == EMPTY)
			{
				SolX = x+r;
				SolY = j;
				break;
			}
		}
		// SOUTH
		for(int j = x - r + 1; j < x + r; j++) // walk through j => x
		{
			if(legal(j, y-r) && m_grid[j][j-r] == EMPTY)
			{
				SolX = j;
				SolY = y-r;
				break;
			}
		}
	}
	
	if(SolX != -1) // if found solution
	{
		Point start(x,y);
		Point end(SolX,SolY);
		Path* tmp = path_astar(*this, start, end);
		if(tmp == NULL)
			return NumDirections;
		if(tmp->nodes.size() < 2)
			return North;
		if(tmp->nodes[1].x > tmp->nodes[0].x)
			return East;
		if(tmp->nodes[1].x < tmp->nodes[0].x)
			return West;
		if(tmp->nodes[1].y > tmp->nodes[0].y)
			return North;
		else
			return South;
	}
	else
	{
		return Direction_t(rand() % 4);
	}
}

	
	
std::ostream& operator<<(std::ostream& out,Map& map)
{
	for(int j = 0; j < map.height(); j++)
	{
		for(int i = 0; i < map.width(); i++)
		{
			out << int(map.m_grid[i][j]);
		}
		out << std::endl;
	}
	return out;
}

std::ostream& operator<<(std::ostream& out, Cluster& cluster)
{
	out << cluster.m_type << " CLUSTER" << std::endl;
	
	for(int j = 0; j < 20; j++)
	{
		for(int i = 0; i < 40; i++)
		{
			out << int(cluster.m_active[i][j]);
		}
		out << std::endl;
	}
	
	return out;
}

	
	