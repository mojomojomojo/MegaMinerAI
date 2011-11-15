#include "path.hpp"

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

/*
class Map
{
	public:
	int8_t ** m_grid;
	int8_t m_width;
	int8_t m_height;
	AI* m_parent;
	
	Map(const signed short x, const signed short y, AI* parent); //Creates an empty map
	Map(AI* parent); //Creates an empty map
	
	int8_t width();
	int8_t height();
	
	MAPCODE at(const int8_t x, const int8_t y);
	
	void update();
	
//	void init();
};

*/

void initMap(Map &m);


int main() {
  Map m;

  // int w=10,h=10;
  // m.m_width = w;
  // m.m_height = h;
  // m.m_grid = new MAPCODE*[w];
  // for (int x=0; x<w; x++) {
  //   m.m_grid[x] = new MAPCODE[h];
  //   for (int y=0; y<h; y++) {
  //     m.m_grid[x][y] = EMPTY;
  //   }
  // }
  // for (int x = 0; x+1<w; x++) {
  //   m.m_grid[x][4] = WALL;
  // }
  // for (int x = 1; x<w; x++) {
  //   m.m_grid[x][6] = WALL;
  // }

  // for (int  y=0; y<m.height(); y++) {
  //   for (int x=0; x<m.width(); x++) {
  //     cout << " " << m.at(x,y);
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  initMap(m);
  Path _p;
  cout << "curr map: " << endl;
  cout << asText(m,_p) << endl;


  m.m_grid[17][8] = OPBASE;
  // No path from (31,19) to (20,11)
  Path *path = path_astar(m,Point(31,19),Point(20,11),AS_AllowImpassableEnd);

  if (path != NULL) {
    cout << *path << endl << endl;
    cout << endl << asText(m,*path) << endl;
  }

  delete path;
}

/*
string asText( Map &m, Path& p ) {
  stringstream sout(stringstream::out);

  for (int y=0; y<m.height(); y++) {
    for (int x=0; x<m.width(); x++) {
      MAPCODE c = m.m_grid[x][y];
      if (c == WALL) {
        sout << "#";
        continue;
      }

      Point here(x,y);
      if (here == p.start) {
        sout << "@";
        continue;
      } else if (here == p.end) {
        sout << "X";
        continue;
      }

      bool inPath = false;
      for (vector<Point>::iterator pt = p.nodes.begin()+1;
           pt != p.nodes.end();
           pt++) {
        if (pt+1 == p.nodes.end()) continue;
        if (*pt == here) {
          sout << "+";
          inPath = true;
          break;
        }
      }
      if (inPath) continue;

      sout << ".";
    }
    sout << endl;
  }

  return sout.str();
}
*/

void initMap(Map &m) {
  m.m_width = 40;
  m.m_height = 20;
  m.m_grid = new MAPCODE*[m.m_width];
  for (int x=0; x<m.m_width; x++) {
    m.m_grid[x] = new MAPCODE[m.m_height];
    for (int y=0; y<m.m_height; y++) {
      m.m_grid[x][y] = EMPTY;
    }
  }

Map *map_var = &m;
  map_var->m_grid[0][0] = EMPTY;
  map_var->m_grid[1][0] = EMPTY;
  map_var->m_grid[2][0] = EMPTY;
  map_var->m_grid[3][0] = EMPTY;
  map_var->m_grid[4][0] = EMPTY;
  map_var->m_grid[5][0] = EMPTY;
  map_var->m_grid[6][0] = WALL;
  map_var->m_grid[7][0] = EMPTY;
  map_var->m_grid[8][0] = EMPTY;
  map_var->m_grid[9][0] = EMPTY;
  map_var->m_grid[10][0] = EMPTY;
  map_var->m_grid[11][0] = EMPTY;
  map_var->m_grid[12][0] = EMPTY;
  map_var->m_grid[13][0] = EMPTY;
  map_var->m_grid[14][0] = EMPTY;
  map_var->m_grid[15][0] = EMPTY;
  map_var->m_grid[16][0] = EMPTY;
  map_var->m_grid[17][0] = EMPTY;
  map_var->m_grid[18][0] = EMPTY;
  map_var->m_grid[19][0] = EMPTY;
  map_var->m_grid[20][0] = EMPTY;
  map_var->m_grid[21][0] = WALL;
  map_var->m_grid[22][0] = EMPTY;
  map_var->m_grid[23][0] = EMPTY;
  map_var->m_grid[24][0] = EMPTY;
  map_var->m_grid[25][0] = EMPTY;
  map_var->m_grid[26][0] = EMPTY;
  map_var->m_grid[27][0] = EMPTY;
  map_var->m_grid[28][0] = EMPTY;
  map_var->m_grid[29][0] = EMPTY;
  map_var->m_grid[30][0] = EMPTY;
  map_var->m_grid[31][0] = EMPTY;
  map_var->m_grid[32][0] = EMPTY;
  map_var->m_grid[33][0] = EMPTY;
  map_var->m_grid[34][0] = EMPTY;
  map_var->m_grid[35][0] = EMPTY;
  map_var->m_grid[36][0] = EMPTY;
  map_var->m_grid[37][0] = EMPTY;
  map_var->m_grid[38][0] = EMPTY;
  map_var->m_grid[39][0] = EMPTY;

  map_var->m_grid[0][1] = EMPTY;
  map_var->m_grid[1][1] = EMPTY;
  map_var->m_grid[2][1] = WALL;
  map_var->m_grid[3][1] = EMPTY;
  map_var->m_grid[4][1] = EMPTY;
  map_var->m_grid[5][1] = EMPTY;
  map_var->m_grid[6][1] = EMPTY;
  map_var->m_grid[7][1] = WALL;
  map_var->m_grid[8][1] = EMPTY;
  map_var->m_grid[9][1] = EMPTY;
  map_var->m_grid[10][1] = EMPTY;
  map_var->m_grid[11][1] = WALL;
  map_var->m_grid[12][1] = EMPTY;
  map_var->m_grid[13][1] = EMPTY;
  map_var->m_grid[14][1] = EMPTY;
  map_var->m_grid[15][1] = WALL;
  map_var->m_grid[16][1] = EMPTY;
  map_var->m_grid[17][1] = EMPTY;
  map_var->m_grid[18][1] = EMPTY;
  map_var->m_grid[19][1] = EMPTY;
  map_var->m_grid[20][1] = EMPTY;
  map_var->m_grid[21][1] = EMPTY;
  map_var->m_grid[22][1] = EMPTY;
  map_var->m_grid[23][1] = EMPTY;
  map_var->m_grid[24][1] = EMPTY;
  map_var->m_grid[25][1] = EMPTY;
  map_var->m_grid[26][1] = EMPTY;
  map_var->m_grid[27][1] = EMPTY;
  map_var->m_grid[28][1] = EMPTY;
  map_var->m_grid[29][1] = EMPTY;
  map_var->m_grid[30][1] = EMPTY;
  map_var->m_grid[31][1] = EMPTY;
  map_var->m_grid[32][1] = EMPTY;
  map_var->m_grid[33][1] = EMPTY;
  map_var->m_grid[34][1] = EMPTY;
  map_var->m_grid[35][1] = EMPTY;
  map_var->m_grid[36][1] = WALL;
  map_var->m_grid[37][1] = EMPTY;
  map_var->m_grid[38][1] = EMPTY;
  map_var->m_grid[39][1] = EMPTY;

  map_var->m_grid[0][2] = EMPTY;
  map_var->m_grid[1][2] = EMPTY;
  map_var->m_grid[2][2] = EMPTY;
  map_var->m_grid[3][2] = WALL;
  map_var->m_grid[4][2] = EMPTY;
  map_var->m_grid[5][2] = EMPTY;
  map_var->m_grid[6][2] = EMPTY;
  map_var->m_grid[7][2] = EMPTY;
  map_var->m_grid[8][2] = WALL;
  map_var->m_grid[9][2] = EMPTY;
  map_var->m_grid[10][2] = WALL;
  map_var->m_grid[11][2] = EMPTY;
  map_var->m_grid[12][2] = EMPTY;
  map_var->m_grid[13][2] = EMPTY;
  map_var->m_grid[14][2] = EMPTY;
  map_var->m_grid[15][2] = EMPTY;
  map_var->m_grid[16][2] = WALL;
  map_var->m_grid[17][2] = EMPTY;
  map_var->m_grid[18][2] = EMPTY;
  map_var->m_grid[19][2] = WALL;
  map_var->m_grid[20][2] = EMPTY;
  map_var->m_grid[21][2] = WALL;
  map_var->m_grid[22][2] = EMPTY;
  map_var->m_grid[23][2] = EMPTY;
  map_var->m_grid[24][2] = EMPTY;
  map_var->m_grid[25][2] = EMPTY;
  map_var->m_grid[26][2] = EMPTY;
  map_var->m_grid[27][2] = EMPTY;
  map_var->m_grid[28][2] = EMPTY;
  map_var->m_grid[29][2] = EMPTY;
  map_var->m_grid[30][2] = EMPTY;
  map_var->m_grid[31][2] = EMPTY;
  map_var->m_grid[32][2] = EMPTY;
  map_var->m_grid[33][2] = EMPTY;
  map_var->m_grid[34][2] = EMPTY;
  map_var->m_grid[35][2] = WALL;
  map_var->m_grid[36][2] = EMPTY;
  map_var->m_grid[37][2] = EMPTY;
  map_var->m_grid[38][2] = EMPTY;
  map_var->m_grid[39][2] = EMPTY;

  map_var->m_grid[0][3] = EMPTY;
  map_var->m_grid[1][3] = EMPTY;
  map_var->m_grid[2][3] = EMPTY;
  map_var->m_grid[3][3] = EMPTY;
  map_var->m_grid[4][3] = WALL;
  map_var->m_grid[5][3] = EMPTY;
  map_var->m_grid[6][3] = EMPTY;
  map_var->m_grid[7][3] = EMPTY;
  map_var->m_grid[8][3] = EMPTY;
  map_var->m_grid[9][3] = EMPTY;
  map_var->m_grid[10][3] = EMPTY;
  map_var->m_grid[11][3] = EMPTY;
  map_var->m_grid[12][3] = EMPTY;
  map_var->m_grid[13][3] = EMPTY;
  map_var->m_grid[14][3] = EMPTY;
  map_var->m_grid[15][3] = EMPTY;
  map_var->m_grid[16][3] = EMPTY;
  map_var->m_grid[17][3] = WALL;
  map_var->m_grid[18][3] = EMPTY;
  map_var->m_grid[19][3] = EMPTY;
  map_var->m_grid[20][3] = EMPTY;
  map_var->m_grid[21][3] = EMPTY;
  map_var->m_grid[22][3] = WALL;
  map_var->m_grid[23][3] = EMPTY;
  map_var->m_grid[24][3] = EMPTY;
  map_var->m_grid[25][3] = EMPTY;
  map_var->m_grid[26][3] = EMPTY;
  map_var->m_grid[27][3] = EMPTY;
  map_var->m_grid[28][3] = EMPTY;
  map_var->m_grid[29][3] = EMPTY;
  map_var->m_grid[30][3] = EMPTY;
  map_var->m_grid[31][3] = EMPTY;
  map_var->m_grid[32][3] = EMPTY;
  map_var->m_grid[33][3] = EMPTY;
  map_var->m_grid[34][3] = WALL;
  map_var->m_grid[35][3] = EMPTY;
  map_var->m_grid[36][3] = EMPTY;
  map_var->m_grid[37][3] = EMPTY;
  map_var->m_grid[38][3] = EMPTY;
  map_var->m_grid[39][3] = EMPTY;

  map_var->m_grid[0][4] = EMPTY;
  map_var->m_grid[1][4] = EMPTY;
  map_var->m_grid[2][4] = EMPTY;
  map_var->m_grid[3][4] = EMPTY;
  map_var->m_grid[4][4] = EMPTY;
  map_var->m_grid[5][4] = WALL;
  map_var->m_grid[6][4] = EMPTY;
  map_var->m_grid[7][4] = EMPTY;
  map_var->m_grid[8][4] = WALL;
  map_var->m_grid[9][4] = EMPTY;
  map_var->m_grid[10][4] = WALL;
  map_var->m_grid[11][4] = EMPTY;
  map_var->m_grid[12][4] = EMPTY;
  map_var->m_grid[13][4] = EMPTY;
  map_var->m_grid[14][4] = EMPTY;
  map_var->m_grid[15][4] = EMPTY;
  map_var->m_grid[16][4] = EMPTY;
  map_var->m_grid[17][4] = EMPTY;
  map_var->m_grid[18][4] = WALL;
  map_var->m_grid[19][4] = EMPTY;
  map_var->m_grid[20][4] = EMPTY;
  map_var->m_grid[21][4] = EMPTY;
  map_var->m_grid[22][4] = EMPTY;
  map_var->m_grid[23][4] = WALL;
  map_var->m_grid[24][4] = EMPTY;
  map_var->m_grid[25][4] = EMPTY;
  map_var->m_grid[26][4] = EMPTY;
  map_var->m_grid[27][4] = EMPTY;
  map_var->m_grid[28][4] = EMPTY;
  map_var->m_grid[29][4] = EMPTY;
  map_var->m_grid[30][4] = EMPTY;
  map_var->m_grid[31][4] = EMPTY;
  map_var->m_grid[32][4] = EMPTY;
  map_var->m_grid[33][4] = WALL;
  map_var->m_grid[34][4] = EMPTY;
  map_var->m_grid[35][4] = EMPTY;
  map_var->m_grid[36][4] = EMPTY;
  map_var->m_grid[37][4] = EMPTY;
  map_var->m_grid[38][4] = EMPTY;
  map_var->m_grid[39][4] = EMPTY;

  map_var->m_grid[0][5] = EMPTY;
  map_var->m_grid[1][5] = EMPTY;
  map_var->m_grid[2][5] = EMPTY;
  map_var->m_grid[3][5] = EMPTY;
  map_var->m_grid[4][5] = EMPTY;
  map_var->m_grid[5][5] = EMPTY;
  map_var->m_grid[6][5] = WALL;
  map_var->m_grid[7][5] = WALL;
  map_var->m_grid[8][5] = EMPTY;
  map_var->m_grid[9][5] = EMPTY;
  map_var->m_grid[10][5] = EMPTY;
  map_var->m_grid[11][5] = WALL;
  map_var->m_grid[12][5] = EMPTY;
  map_var->m_grid[13][5] = EMPTY;
  map_var->m_grid[14][5] = EMPTY;
  map_var->m_grid[15][5] = EMPTY;
  map_var->m_grid[16][5] = WALL;
  map_var->m_grid[17][5] = EMPTY;
  map_var->m_grid[18][5] = EMPTY;
  map_var->m_grid[19][5] = WALL;
  map_var->m_grid[20][5] = EMPTY;
  map_var->m_grid[21][5] = EMPTY;
  map_var->m_grid[22][5] = EMPTY;
  map_var->m_grid[23][5] = EMPTY;
  map_var->m_grid[24][5] = WALL;
  map_var->m_grid[25][5] = EMPTY;
  map_var->m_grid[26][5] = EMPTY;
  map_var->m_grid[27][5] = EMPTY;
  map_var->m_grid[28][5] = EMPTY;
  map_var->m_grid[29][5] = EMPTY;
  map_var->m_grid[30][5] = EMPTY;
  map_var->m_grid[31][5] = EMPTY;
  map_var->m_grid[32][5] = WALL;
  map_var->m_grid[33][5] = EMPTY;
  map_var->m_grid[34][5] = EMPTY;
  map_var->m_grid[35][5] = EMPTY;
  map_var->m_grid[36][5] = EMPTY;
  map_var->m_grid[37][5] = EMPTY;
  map_var->m_grid[38][5] = EMPTY;
  map_var->m_grid[39][5] = EMPTY;

  map_var->m_grid[0][6] = EMPTY;
  map_var->m_grid[1][6] = EMPTY;
  map_var->m_grid[2][6] = EMPTY;
  map_var->m_grid[3][6] = EMPTY;
  map_var->m_grid[4][6] = EMPTY;
  map_var->m_grid[5][6] = EMPTY;
  map_var->m_grid[6][6] = EMPTY;
  map_var->m_grid[7][6] = WALL;
  map_var->m_grid[8][6] = EMPTY;
  map_var->m_grid[9][6] = EMPTY;
  map_var->m_grid[10][6] = EMPTY;
  map_var->m_grid[11][6] = EMPTY;
  map_var->m_grid[12][6] = WALL;
  map_var->m_grid[13][6] = EMPTY;
  map_var->m_grid[14][6] = EMPTY;
  map_var->m_grid[15][6] = WALL;
  map_var->m_grid[16][6] = EMPTY;
  map_var->m_grid[17][6] = EMPTY;
  map_var->m_grid[18][6] = EMPTY;
  map_var->m_grid[19][6] = EMPTY;
  map_var->m_grid[20][6] = WALL;
  map_var->m_grid[21][6] = EMPTY;
  map_var->m_grid[22][6] = EMPTY;
  map_var->m_grid[23][6] = EMPTY;
  map_var->m_grid[24][6] = EMPTY;
  map_var->m_grid[25][6] = WALL;
  map_var->m_grid[26][6] = EMPTY;
  map_var->m_grid[27][6] = EMPTY;
  map_var->m_grid[28][6] = EMPTY;
  map_var->m_grid[29][6] = EMPTY;
  map_var->m_grid[30][6] = EMPTY;
  map_var->m_grid[31][6] = WALL;
  map_var->m_grid[32][6] = EMPTY;
  map_var->m_grid[33][6] = EMPTY;
  map_var->m_grid[34][6] = EMPTY;
  map_var->m_grid[35][6] = EMPTY;
  map_var->m_grid[36][6] = EMPTY;
  map_var->m_grid[37][6] = EMPTY;
  map_var->m_grid[38][6] = EMPTY;
  map_var->m_grid[39][6] = EMPTY;

  map_var->m_grid[0][7] = EMPTY;
  map_var->m_grid[1][7] = EMPTY;
  map_var->m_grid[2][7] = EMPTY;
  map_var->m_grid[3][7] = EMPTY;
  map_var->m_grid[4][7] = EMPTY;
  map_var->m_grid[5][7] = WALL;
  map_var->m_grid[6][7] = EMPTY;
  map_var->m_grid[7][7] = EMPTY;
  map_var->m_grid[8][7] = WALL;
  map_var->m_grid[9][7] = EMPTY;
  map_var->m_grid[10][7] = EMPTY;
  map_var->m_grid[11][7] = EMPTY;
  map_var->m_grid[12][7] = EMPTY;
  map_var->m_grid[13][7] = WALL;
  map_var->m_grid[14][7] = EMPTY;
  map_var->m_grid[15][7] = EMPTY;
  map_var->m_grid[16][7] = EMPTY;
  map_var->m_grid[17][7] = EMPTY;
  map_var->m_grid[18][7] = EMPTY;
  map_var->m_grid[19][7] = EMPTY;
  map_var->m_grid[20][7] = EMPTY;
  map_var->m_grid[21][7] = WALL;
  map_var->m_grid[22][7] = EMPTY;
  map_var->m_grid[23][7] = EMPTY;
  map_var->m_grid[24][7] = EMPTY;
  map_var->m_grid[25][7] = EMPTY;
  map_var->m_grid[26][7] = WALL;
  map_var->m_grid[27][7] = EMPTY;
  map_var->m_grid[28][7] = EMPTY;
  map_var->m_grid[29][7] = EMPTY;
  map_var->m_grid[30][7] = WALL;
  map_var->m_grid[31][7] = EMPTY;
  map_var->m_grid[32][7] = EMPTY;
  map_var->m_grid[33][7] = EMPTY;
  map_var->m_grid[34][7] = EMPTY;
  map_var->m_grid[35][7] = EMPTY;
  map_var->m_grid[36][7] = EMPTY;
  map_var->m_grid[37][7] = EMPTY;
  map_var->m_grid[38][7] = EMPTY;
  map_var->m_grid[39][7] = EMPTY;

  map_var->m_grid[0][8] = EMPTY;
  map_var->m_grid[1][8] = EMPTY;
  map_var->m_grid[2][8] = EMPTY;
  map_var->m_grid[3][8] = EMPTY;
  map_var->m_grid[4][8] = WALL;
  map_var->m_grid[5][8] = EMPTY;
  map_var->m_grid[6][8] = EMPTY;
  map_var->m_grid[7][8] = EMPTY;
  map_var->m_grid[8][8] = EMPTY;
  map_var->m_grid[9][8] = WALL;
  map_var->m_grid[10][8] = EMPTY;
  map_var->m_grid[11][8] = EMPTY;
  map_var->m_grid[12][8] = EMPTY;
  map_var->m_grid[13][8] = WALL;
  map_var->m_grid[14][8] = WALL;
  map_var->m_grid[15][8] = EMPTY;
  map_var->m_grid[16][8] = EMPTY;
  map_var->m_grid[17][8] = EMPTY;
  map_var->m_grid[18][8] = EMPTY;
  map_var->m_grid[19][8] = EMPTY;
  map_var->m_grid[20][8] = EMPTY;
  map_var->m_grid[21][8] = EMPTY;
  map_var->m_grid[22][8] = WALL;
  map_var->m_grid[23][8] = EMPTY;
  map_var->m_grid[24][8] = EMPTY;
  map_var->m_grid[25][8] = EMPTY;
  map_var->m_grid[26][8] = EMPTY;
  map_var->m_grid[27][8] = WALL;
  map_var->m_grid[28][8] = EMPTY;
  map_var->m_grid[29][8] = WALL;
  map_var->m_grid[30][8] = EMPTY;
  map_var->m_grid[31][8] = EMPTY;
  map_var->m_grid[32][8] = EMPTY;
  map_var->m_grid[33][8] = EMPTY;
  map_var->m_grid[34][8] = EMPTY;
  map_var->m_grid[35][8] = EMPTY;
  map_var->m_grid[36][8] = EMPTY;
  map_var->m_grid[37][8] = EMPTY;
  map_var->m_grid[38][8] = WALL;
  map_var->m_grid[39][8] = EMPTY;

  map_var->m_grid[0][9] = EMPTY;
  map_var->m_grid[1][9] = EMPTY;
  map_var->m_grid[2][9] = EMPTY;
  map_var->m_grid[3][9] = WALL;
  map_var->m_grid[4][9] = EMPTY;
  map_var->m_grid[5][9] = EMPTY;
  map_var->m_grid[6][9] = EMPTY;
  map_var->m_grid[7][9] = EMPTY;
  map_var->m_grid[8][9] = EMPTY;
  map_var->m_grid[9][9] = EMPTY;
  map_var->m_grid[10][9] = EMPTY;
  map_var->m_grid[11][9] = EMPTY;
  map_var->m_grid[12][9] = WALL;
  map_var->m_grid[13][9] = EMPTY;
  map_var->m_grid[14][9] = EMPTY;
  map_var->m_grid[15][9] = WALL;
  map_var->m_grid[16][9] = EMPTY;
  map_var->m_grid[17][9] = EMPTY;
  map_var->m_grid[18][9] = EMPTY;
  map_var->m_grid[19][9] = EMPTY;
  map_var->m_grid[20][9] = EMPTY;
  map_var->m_grid[21][9] = EMPTY;
  map_var->m_grid[22][9] = EMPTY;
  map_var->m_grid[23][9] = WALL;
  map_var->m_grid[24][9] = EMPTY;
  map_var->m_grid[25][9] = EMPTY;
  map_var->m_grid[26][9] = EMPTY;
  map_var->m_grid[27][9] = EMPTY;
  map_var->m_grid[28][9] = EMPTY;
  map_var->m_grid[29][9] = EMPTY;
  map_var->m_grid[30][9] = EMPTY;
  map_var->m_grid[31][9] = EMPTY;
  map_var->m_grid[32][9] = EMPTY;
  map_var->m_grid[33][9] = EMPTY;
  map_var->m_grid[34][9] = EMPTY;
  map_var->m_grid[35][9] = EMPTY;
  map_var->m_grid[36][9] = EMPTY;
  map_var->m_grid[37][9] = WALL;
  map_var->m_grid[38][9] = EMPTY;
  map_var->m_grid[39][9] = EMPTY;

  map_var->m_grid[0][10] = EMPTY;
  map_var->m_grid[1][10] = EMPTY;
  map_var->m_grid[2][10] = WALL;
  map_var->m_grid[3][10] = EMPTY;
  map_var->m_grid[4][10] = EMPTY;
  map_var->m_grid[5][10] = EMPTY;
  map_var->m_grid[6][10] = EMPTY;
  map_var->m_grid[7][10] = EMPTY;
  map_var->m_grid[8][10] = EMPTY;
  map_var->m_grid[9][10] = EMPTY;
  map_var->m_grid[10][10] = EMPTY;
  map_var->m_grid[11][10] = EMPTY;
  map_var->m_grid[12][10] = EMPTY;
  map_var->m_grid[13][10] = EMPTY;
  map_var->m_grid[14][10] = EMPTY;
  map_var->m_grid[15][10] = EMPTY;
  map_var->m_grid[16][10] = WALL;
  map_var->m_grid[17][10] = EMPTY;
  map_var->m_grid[18][10] = EMPTY;
  map_var->m_grid[19][10] = EMPTY;
  map_var->m_grid[20][10] = EMPTY;
  map_var->m_grid[21][10] = EMPTY;
  map_var->m_grid[22][10] = EMPTY;
  map_var->m_grid[23][10] = EMPTY;
  map_var->m_grid[24][10] = WALL;
  map_var->m_grid[25][10] = EMPTY;
  map_var->m_grid[26][10] = EMPTY;
  map_var->m_grid[27][10] = WALL;
  map_var->m_grid[28][10] = EMPTY;
  map_var->m_grid[29][10] = EMPTY;
  map_var->m_grid[30][10] = EMPTY;
  map_var->m_grid[31][10] = EMPTY;
  map_var->m_grid[32][10] = EMPTY;
  map_var->m_grid[33][10] = EMPTY;
  map_var->m_grid[34][10] = EMPTY;
  map_var->m_grid[35][10] = EMPTY;
  map_var->m_grid[36][10] = WALL;
  map_var->m_grid[37][10] = EMPTY;
  map_var->m_grid[38][10] = EMPTY;
  map_var->m_grid[39][10] = EMPTY;

  map_var->m_grid[0][11] = EMPTY;
  map_var->m_grid[1][11] = WALL;
  map_var->m_grid[2][11] = EMPTY;
  map_var->m_grid[3][11] = EMPTY;
  map_var->m_grid[4][11] = EMPTY;
  map_var->m_grid[5][11] = EMPTY;
  map_var->m_grid[6][11] = EMPTY;
  map_var->m_grid[7][11] = EMPTY;
  map_var->m_grid[8][11] = EMPTY;
  map_var->m_grid[9][11] = EMPTY;
  map_var->m_grid[10][11] = WALL;
  map_var->m_grid[11][11] = EMPTY;
  map_var->m_grid[12][11] = WALL;
  map_var->m_grid[13][11] = EMPTY;
  map_var->m_grid[14][11] = EMPTY;
  map_var->m_grid[15][11] = EMPTY;
  map_var->m_grid[16][11] = EMPTY;
  map_var->m_grid[17][11] = WALL;
  map_var->m_grid[18][11] = EMPTY;
  map_var->m_grid[19][11] = EMPTY;
  map_var->m_grid[21][11] = EMPTY;
  map_var->m_grid[22][11] = EMPTY;
  map_var->m_grid[23][11] = EMPTY;
  map_var->m_grid[24][11] = EMPTY;
  map_var->m_grid[25][11] = WALL;
  map_var->m_grid[26][11] = WALL;
  map_var->m_grid[27][11] = EMPTY;
  map_var->m_grid[28][11] = EMPTY;
  map_var->m_grid[29][11] = EMPTY;
  map_var->m_grid[30][11] = WALL;
  map_var->m_grid[31][11] = EMPTY;
  map_var->m_grid[32][11] = EMPTY;
  map_var->m_grid[33][11] = EMPTY;
  map_var->m_grid[34][11] = EMPTY;
  map_var->m_grid[35][11] = WALL;
  map_var->m_grid[36][11] = EMPTY;
  map_var->m_grid[37][11] = EMPTY;
  map_var->m_grid[38][11] = EMPTY;
  map_var->m_grid[39][11] = EMPTY;

  map_var->m_grid[0][12] = EMPTY;
  map_var->m_grid[1][12] = EMPTY;
  map_var->m_grid[2][12] = EMPTY;
  map_var->m_grid[3][12] = EMPTY;
  map_var->m_grid[4][12] = EMPTY;
  map_var->m_grid[5][12] = EMPTY;
  map_var->m_grid[6][12] = EMPTY;
  map_var->m_grid[7][12] = EMPTY;
  map_var->m_grid[8][12] = EMPTY;
  map_var->m_grid[9][12] = WALL;
  map_var->m_grid[10][12] = EMPTY;
  map_var->m_grid[11][12] = EMPTY;
  map_var->m_grid[12][12] = EMPTY;
  map_var->m_grid[13][12] = WALL;
  map_var->m_grid[14][12] = EMPTY;
  map_var->m_grid[15][12] = EMPTY;
  map_var->m_grid[16][12] = EMPTY;
  map_var->m_grid[17][12] = EMPTY;
  map_var->m_grid[18][12] = WALL;
  map_var->m_grid[19][12] = EMPTY;
  map_var->m_grid[20][12] = EMPTY;
  map_var->m_grid[21][12] = EMPTY;
  map_var->m_grid[22][12] = EMPTY;
  map_var->m_grid[23][12] = EMPTY;
  map_var->m_grid[24][12] = EMPTY;
  map_var->m_grid[25][12] = EMPTY;
  map_var->m_grid[26][12] = WALL;
  map_var->m_grid[27][12] = EMPTY;
  map_var->m_grid[28][12] = EMPTY;
  map_var->m_grid[29][12] = EMPTY;
  map_var->m_grid[30][12] = EMPTY;
  map_var->m_grid[31][12] = WALL;
  map_var->m_grid[32][12] = EMPTY;
  map_var->m_grid[33][12] = EMPTY;
  map_var->m_grid[34][12] = WALL;
  map_var->m_grid[35][12] = EMPTY;
  map_var->m_grid[36][12] = EMPTY;
  map_var->m_grid[37][12] = EMPTY;
  map_var->m_grid[38][12] = EMPTY;
  map_var->m_grid[39][12] = EMPTY;

  map_var->m_grid[0][13] = EMPTY;
  map_var->m_grid[1][13] = EMPTY;
  map_var->m_grid[2][13] = EMPTY;
  map_var->m_grid[3][13] = EMPTY;
  map_var->m_grid[4][13] = EMPTY;
  map_var->m_grid[5][13] = EMPTY;
  map_var->m_grid[6][13] = EMPTY;
  map_var->m_grid[7][13] = EMPTY;
  map_var->m_grid[8][13] = WALL;
  map_var->m_grid[9][13] = EMPTY;
  map_var->m_grid[10][13] = EMPTY;
  map_var->m_grid[11][13] = EMPTY;
  map_var->m_grid[12][13] = EMPTY;
  map_var->m_grid[13][13] = EMPTY;
  map_var->m_grid[14][13] = WALL;
  map_var->m_grid[15][13] = EMPTY;
  map_var->m_grid[16][13] = EMPTY;
  map_var->m_grid[17][13] = EMPTY;
  map_var->m_grid[18][13] = EMPTY;
  map_var->m_grid[19][13] = WALL;
  map_var->m_grid[20][13] = EMPTY;
  map_var->m_grid[21][13] = EMPTY;
  map_var->m_grid[22][13] = EMPTY;
  map_var->m_grid[23][13] = EMPTY;
  map_var->m_grid[24][13] = WALL;
  map_var->m_grid[25][13] = EMPTY;
  map_var->m_grid[26][13] = EMPTY;
  map_var->m_grid[27][13] = WALL;
  map_var->m_grid[28][13] = EMPTY;
  map_var->m_grid[29][13] = EMPTY;
  map_var->m_grid[30][13] = EMPTY;
  map_var->m_grid[31][13] = EMPTY;
  map_var->m_grid[32][13] = WALL;
  map_var->m_grid[33][13] = EMPTY;
  map_var->m_grid[34][13] = EMPTY;
  map_var->m_grid[35][13] = EMPTY;
  map_var->m_grid[36][13] = EMPTY;
  map_var->m_grid[37][13] = EMPTY;
  map_var->m_grid[38][13] = EMPTY;
  map_var->m_grid[39][13] = EMPTY;

  map_var->m_grid[0][14] = EMPTY;
  map_var->m_grid[1][14] = EMPTY;
  map_var->m_grid[2][14] = EMPTY;
  map_var->m_grid[3][14] = EMPTY;
  map_var->m_grid[4][14] = EMPTY;
  map_var->m_grid[5][14] = EMPTY;
  map_var->m_grid[6][14] = EMPTY;
  map_var->m_grid[7][14] = WALL;
  map_var->m_grid[8][14] = EMPTY;
  map_var->m_grid[9][14] = EMPTY;
  map_var->m_grid[10][14] = EMPTY;
  map_var->m_grid[11][14] = EMPTY;
  map_var->m_grid[12][14] = EMPTY;
  map_var->m_grid[13][14] = EMPTY;
  map_var->m_grid[14][14] = EMPTY;
  map_var->m_grid[15][14] = WALL;
  map_var->m_grid[16][14] = EMPTY;
  map_var->m_grid[17][14] = EMPTY;
  map_var->m_grid[18][14] = EMPTY;
  map_var->m_grid[19][14] = EMPTY;
  map_var->m_grid[20][14] = WALL;
  map_var->m_grid[21][14] = EMPTY;
  map_var->m_grid[22][14] = EMPTY;
  map_var->m_grid[23][14] = WALL;
  map_var->m_grid[24][14] = EMPTY;
  map_var->m_grid[25][14] = EMPTY;
  map_var->m_grid[26][14] = EMPTY;
  map_var->m_grid[27][14] = EMPTY;
  map_var->m_grid[28][14] = WALL;
  map_var->m_grid[29][14] = EMPTY;
  map_var->m_grid[30][14] = EMPTY;
  map_var->m_grid[31][14] = EMPTY;
  map_var->m_grid[32][14] = WALL;
  map_var->m_grid[33][14] = WALL;
  map_var->m_grid[34][14] = EMPTY;
  map_var->m_grid[35][14] = EMPTY;
  map_var->m_grid[36][14] = EMPTY;
  map_var->m_grid[37][14] = EMPTY;
  map_var->m_grid[38][14] = EMPTY;
  map_var->m_grid[39][14] = EMPTY;

  map_var->m_grid[0][15] = EMPTY;
  map_var->m_grid[1][15] = EMPTY;
  map_var->m_grid[2][15] = EMPTY;
  map_var->m_grid[3][15] = EMPTY;
  map_var->m_grid[4][15] = EMPTY;
  map_var->m_grid[5][15] = EMPTY;
  map_var->m_grid[6][15] = WALL;
  map_var->m_grid[7][15] = EMPTY;
  map_var->m_grid[8][15] = EMPTY;
  map_var->m_grid[9][15] = EMPTY;
  map_var->m_grid[10][15] = EMPTY;
  map_var->m_grid[11][15] = EMPTY;
  map_var->m_grid[12][15] = EMPTY;
  map_var->m_grid[13][15] = EMPTY;
  map_var->m_grid[14][15] = EMPTY;
  map_var->m_grid[15][15] = EMPTY;
  map_var->m_grid[16][15] = WALL;
  map_var->m_grid[17][15] = EMPTY;
  map_var->m_grid[18][15] = EMPTY;
  map_var->m_grid[19][15] = EMPTY;
  map_var->m_grid[20][15] = EMPTY;
  map_var->m_grid[21][15] = WALL;
  map_var->m_grid[22][15] = EMPTY;
  map_var->m_grid[23][15] = EMPTY;
  map_var->m_grid[24][15] = EMPTY;
  map_var->m_grid[25][15] = EMPTY;
  map_var->m_grid[26][15] = EMPTY;
  map_var->m_grid[27][15] = EMPTY;
  map_var->m_grid[28][15] = EMPTY;
  map_var->m_grid[29][15] = WALL;
  map_var->m_grid[30][15] = EMPTY;
  map_var->m_grid[31][15] = WALL;
  map_var->m_grid[32][15] = EMPTY;
  map_var->m_grid[33][15] = EMPTY;
  map_var->m_grid[34][15] = WALL;
  map_var->m_grid[35][15] = EMPTY;
  map_var->m_grid[36][15] = EMPTY;
  map_var->m_grid[37][15] = EMPTY;
  map_var->m_grid[38][15] = EMPTY;
  map_var->m_grid[39][15] = EMPTY;

  map_var->m_grid[0][16] = EMPTY;
  map_var->m_grid[1][16] = EMPTY;
  map_var->m_grid[2][16] = EMPTY;
  map_var->m_grid[3][16] = EMPTY;
  map_var->m_grid[4][16] = EMPTY;
  map_var->m_grid[5][16] = WALL;
  map_var->m_grid[6][16] = EMPTY;
  map_var->m_grid[7][16] = EMPTY;
  map_var->m_grid[8][16] = EMPTY;
  map_var->m_grid[9][16] = EMPTY;
  map_var->m_grid[10][16] = EMPTY;
  map_var->m_grid[11][16] = EMPTY;
  map_var->m_grid[12][16] = EMPTY;
  map_var->m_grid[13][16] = EMPTY;
  map_var->m_grid[14][16] = EMPTY;
  map_var->m_grid[15][16] = EMPTY;
  map_var->m_grid[16][16] = EMPTY;
  map_var->m_grid[17][16] = WALL;
  map_var->m_grid[18][16] = EMPTY;
  map_var->m_grid[19][16] = EMPTY;
  map_var->m_grid[20][16] = EMPTY;
  map_var->m_grid[21][16] = EMPTY;
  map_var->m_grid[22][16] = WALL;
  map_var->m_grid[23][16] = EMPTY;
  map_var->m_grid[24][16] = EMPTY;
  map_var->m_grid[25][16] = EMPTY;
  map_var->m_grid[26][16] = EMPTY;
  map_var->m_grid[27][16] = EMPTY;
  map_var->m_grid[28][16] = EMPTY;
  map_var->m_grid[29][16] = EMPTY;
  map_var->m_grid[30][16] = EMPTY;
  map_var->m_grid[31][16] = EMPTY;
  map_var->m_grid[32][16] = EMPTY;
  map_var->m_grid[33][16] = EMPTY;
  map_var->m_grid[34][16] = EMPTY;
  map_var->m_grid[35][16] = WALL;
  map_var->m_grid[36][16] = EMPTY;
  map_var->m_grid[37][16] = EMPTY;
  map_var->m_grid[38][16] = EMPTY;
  map_var->m_grid[39][16] = EMPTY;

  map_var->m_grid[0][17] = EMPTY;
  map_var->m_grid[1][17] = EMPTY;
  map_var->m_grid[2][17] = EMPTY;
  map_var->m_grid[3][17] = EMPTY;
  map_var->m_grid[4][17] = WALL;
  map_var->m_grid[5][17] = EMPTY;
  map_var->m_grid[6][17] = EMPTY;
  map_var->m_grid[7][17] = EMPTY;
  map_var->m_grid[8][17] = EMPTY;
  map_var->m_grid[9][17] = EMPTY;
  map_var->m_grid[10][17] = EMPTY;
  map_var->m_grid[11][17] = EMPTY;
  map_var->m_grid[12][17] = EMPTY;
  map_var->m_grid[13][17] = EMPTY;
  map_var->m_grid[14][17] = EMPTY;
  map_var->m_grid[15][17] = EMPTY;
  map_var->m_grid[16][17] = EMPTY;
  map_var->m_grid[17][17] = EMPTY;
  map_var->m_grid[18][17] = WALL;
  map_var->m_grid[19][17] = EMPTY;
  map_var->m_grid[20][17] = WALL;
  map_var->m_grid[21][17] = EMPTY;
  map_var->m_grid[22][17] = EMPTY;
  map_var->m_grid[23][17] = WALL;
  map_var->m_grid[24][17] = EMPTY;
  map_var->m_grid[25][17] = EMPTY;
  map_var->m_grid[26][17] = EMPTY;
  map_var->m_grid[27][17] = EMPTY;
  map_var->m_grid[28][17] = EMPTY;
  map_var->m_grid[29][17] = WALL;
  map_var->m_grid[30][17] = EMPTY;
  map_var->m_grid[31][17] = WALL;
  map_var->m_grid[32][17] = EMPTY;
  map_var->m_grid[33][17] = EMPTY;
  map_var->m_grid[34][17] = EMPTY;
  map_var->m_grid[35][17] = EMPTY;
  map_var->m_grid[36][17] = WALL;
  map_var->m_grid[37][17] = EMPTY;
  map_var->m_grid[38][17] = EMPTY;
  map_var->m_grid[39][17] = EMPTY;

  map_var->m_grid[0][18] = EMPTY;
  map_var->m_grid[1][18] = EMPTY;
  map_var->m_grid[2][18] = EMPTY;
  map_var->m_grid[3][18] = WALL;
  map_var->m_grid[4][18] = EMPTY;
  map_var->m_grid[5][18] = EMPTY;
  map_var->m_grid[6][18] = EMPTY;
  map_var->m_grid[7][18] = EMPTY;
  map_var->m_grid[8][18] = EMPTY;
  map_var->m_grid[9][18] = EMPTY;
  map_var->m_grid[10][18] = EMPTY;
  map_var->m_grid[11][18] = EMPTY;
  map_var->m_grid[12][18] = EMPTY;
  map_var->m_grid[13][18] = EMPTY;
  map_var->m_grid[14][18] = EMPTY;
  map_var->m_grid[15][18] = EMPTY;
  map_var->m_grid[16][18] = EMPTY;
  map_var->m_grid[17][18] = EMPTY;
  map_var->m_grid[18][18] = EMPTY;
  map_var->m_grid[19][18] = EMPTY;
  map_var->m_grid[20][18] = EMPTY;
  map_var->m_grid[21][18] = EMPTY;
  map_var->m_grid[22][18] = EMPTY;
  map_var->m_grid[23][18] = EMPTY;
  map_var->m_grid[24][18] = WALL;
  map_var->m_grid[25][18] = EMPTY;
  map_var->m_grid[26][18] = EMPTY;
  map_var->m_grid[27][18] = EMPTY;
  map_var->m_grid[28][18] = WALL;
  map_var->m_grid[29][18] = EMPTY;
  map_var->m_grid[30][18] = EMPTY;
  map_var->m_grid[31][18] = EMPTY;
  map_var->m_grid[32][18] = WALL;
  map_var->m_grid[33][18] = EMPTY;
  map_var->m_grid[34][18] = EMPTY;
  map_var->m_grid[35][18] = EMPTY;
  map_var->m_grid[36][18] = EMPTY;
  map_var->m_grid[37][18] = WALL;
  map_var->m_grid[38][18] = EMPTY;
  map_var->m_grid[39][18] = EMPTY;

  map_var->m_grid[0][19] = EMPTY;
  map_var->m_grid[1][19] = EMPTY;
  map_var->m_grid[2][19] = EMPTY;
  map_var->m_grid[3][19] = EMPTY;
  map_var->m_grid[4][19] = EMPTY;
  map_var->m_grid[5][19] = EMPTY;
  map_var->m_grid[6][19] = EMPTY;
  map_var->m_grid[7][19] = EMPTY;
  map_var->m_grid[8][19] = EMPTY;
  map_var->m_grid[9][19] = EMPTY;
  map_var->m_grid[10][19] = EMPTY;
  map_var->m_grid[11][19] = EMPTY;
  map_var->m_grid[12][19] = EMPTY;
  map_var->m_grid[13][19] = EMPTY;
  map_var->m_grid[14][19] = EMPTY;
  map_var->m_grid[15][19] = EMPTY;
  map_var->m_grid[16][19] = EMPTY;
  map_var->m_grid[17][19] = EMPTY;
  map_var->m_grid[18][19] = WALL;
  map_var->m_grid[19][19] = EMPTY;
  map_var->m_grid[20][19] = EMPTY;
  map_var->m_grid[21][19] = EMPTY;
  map_var->m_grid[22][19] = EMPTY;
  map_var->m_grid[23][19] = EMPTY;
  map_var->m_grid[24][19] = EMPTY;
  map_var->m_grid[25][19] = EMPTY;
  map_var->m_grid[26][19] = EMPTY;
  map_var->m_grid[27][19] = EMPTY;
  map_var->m_grid[28][19] = EMPTY;
  map_var->m_grid[29][19] = EMPTY;
  map_var->m_grid[30][19] = EMPTY;
  map_var->m_grid[32][19] = EMPTY;
  map_var->m_grid[33][19] = WALL;
  map_var->m_grid[34][19] = EMPTY;
  map_var->m_grid[35][19] = EMPTY;
  map_var->m_grid[36][19] = EMPTY;
  map_var->m_grid[37][19] = EMPTY;
  map_var->m_grid[38][19] = EMPTY;
  map_var->m_grid[39][19] = EMPTY;


}
