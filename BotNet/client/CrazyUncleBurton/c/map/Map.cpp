#include "Map.h"

Map::Map(const signed short x, const signed short y, AI* parent) : m_width(x), m_height(y), m_parent(parent)
{
	m_grid = new MAPCODE*[x];
	for(int i = 0; i < x; i++)
	{
		m_grid[i] = new MAPCODE[y];
		for(int j = 0; j < y; j++)
		{
			m_grid[i][j] = EMPTY;
		}
	}
	
	update();
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
		else
		{
			m_grid[m_parent->tiles[i].x()][m_parent->tiles[i].y()] = OP;
		}
		m_grid[m_parent->tiles[i].x()][m_parent->tiles[i].y()] = (m_parent->tiles[i].owner() == m_parent->playerID())?(MYBASE):(OPBASE);
	}
	
	// grab virus info
	for(int i = 0; i < m_parent->viruses.size(); i++)
	{
		m_grid[m_parent->viruses[i].x()][m_parent->viruses[i].y()] = (m_parent->viruses[i].owner() == m_parent->playerID())?(MYVIRUS):(OPVIRUS);
	}
	
	// set the bases
	for(int i = 0; i < m_parent->bases.size(); i++)
	{
		m_grid[m_parent->bases[i].x()][m_parent->bases[i].y()] = (m_parent->bases[i].owner() == m_parent->playerID())?(MYBASE):(OPBASE);
	}
}
	
bool Map::legal(const int8_t x, const int8_t y)
{
	return(m_grid[x][y] == EMPTY || m_grid[x][y] == MY || m_grid[x][y] == OP);
}
	
	
std::ostream& Map::operator<<(std::ostream& out)
{
	for(int i = 0; i < width(); i++)
	{
		for(int j = 0; j < height(); j++)
			out << int(m_grid[i][j]);
		out << std::endl;
	}
	return out;
}
	
	
	
	
