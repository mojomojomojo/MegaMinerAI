#include "path.hpp"

#include <algorithm>
using namespace std;

Point go( Direction_t dir, coord_t x, coord_t y,
                    coord_t width, coord_t height ) {
  if (dir == North) {
    if (y-1 >= 0) return Point(x,y-1);
  } else if (dir == South) {
    if (y+1 < height) return Point(x,y+1);
  } else if (dir == West) {
    if (x-1 >= 0) return Point(x-1,y);
  } else if (dir == East) {
    if (x+1 < width) return Point(x+1,y);
  }
  return Point(255,255);
}

void reorderQueue( vector<Point>& queue );

bool impassable( MAPCODE c, AStarBehavior_t behavior ) {
  if (c == WALL || c == OPBASE || c == MYBASE) return true;
  if ((c == OPVIRUS || c == MYVIRUS) && behavior | AS_DontCrossViruses) return true;
  return false;
}

Path* path_astar( Map map, Point start, Point end,
                  AStarBehavior_t behavior ) {
  //uPath* path_astar( MapCode** map, Point start, Point end ) {

  // Create a parallel 2-D array of "shortest distances" (all "far")
  // Put the start node in the queue.
  // LOOP while queue is not empty
  //   dequeue the first point
  //   LOOP for each direction
  //     see if the distance to that tile is less than the distance here
  //     If so, update the distance.
  //   Reorder the queue.

  PathTrack** parallelMap = new PathTrack*[map.width()];
  for (int x=0; x<map.width(); x++) {
    parallelMap[x] = new PathTrack[map.height()];
    for (int y=0; y<map.height(); y++) {
      parallelMap[x][y].at.x = x;
      parallelMap[x][y].at.y = y;

      parallelMap[x][y].prev.x = 255; // no path back (yet)
      parallelMap[x][y].prev.y = 255;
      parallelMap[x][y].dist = EdgeFar;

      parallelMap[x][y].visited = false;
      parallelMap[x][y].queued = false;
    }
  }

  // Start is 0 from itself. The rest get calculated.
  parallelMap[start.x][start.y].dist = 0;

  Path empty;
  vector<Point> queue;
  Point curr;
  queue.push_back(start);
  while (queue.size() > 0) {
    /*
    cout << endl << asText(map,empty,parallelMap) << endl << endl;
    cout << "Queue: ";
    for (vector<Point>::iterator i = queue.begin();
         i != queue.end();
         i++) {
      cout << " " << (*i);
    }
    cout << endl;
    */

    // Get the first point in the queue.
    curr = queue[0];

    // Finished!
    if (curr == end) break;

    MAPCODE c = map.at(curr.x,curr.y);
    PathTrack* currPT = &(parallelMap[curr.x][curr.y]);
    //cout << "Current: " << curr << " (" << c << ") " << *currPT << endl;

    // Remove it from the queue.
    queue.erase(queue.begin());
    
    // Look at all its neighbors.
    for (int i=0; i<NumDirections; i++) {
      //cout << "  Check " << i << endl;

      Point nextP = go((Direction_t)i,curr.x,curr.y,map.width(),map.height());
      //cout << "   -> " << nextP << endl;
      if (nextP.bad()) continue; // skip edges.
      MAPCODE nextC = map.at(nextP.x,nextP.y);
      if (!((behavior & AS_AllowImpassableEnd) && nextP == end) &&
          (impassable(nextC,behavior))) {
        //cout << "IMPASSABLE! " << nextP << endl;
        continue;
      } // skip impassable moves

      // check the distance
      PathTrack *nextPT = &(parallelMap[nextP.x][nextP.y]);
      if (nextPT->visited) continue;
      EdgeCost nextD = currPT->dist + 1;
      //cout << "   Look: " << nextP << "(" << nextC << ") D(" << nextD << ") " << *nextPT << endl;
      if (nextPT->dist > nextD) {
        nextPT->dist = nextD;
        nextPT->prev = curr;
      }

      currPT->visited = true;
      // Add it to the queue.
      if (!nextPT->queued) {
        nextPT->queued = true;
        queue.push_back(nextP);
      }
    }

    // Prioritize the queue.
    reorderQueue(queue);
  }

  // return the path, if one exists.
  if (curr.bad() || curr != end) {
    cout << "No path from " << start << " to " << end << endl;
    return NULL;
  }
  // build it
  Path* retpath = new Path;
  retpath->start = start;
  retpath->end = end;
  Point p = end;
  while (p != start) {
    retpath->nodes.insert(retpath->nodes.begin(),p);
    PathTrack pt = parallelMap[p.x][p.y];
    p = pt.prev;
  }
  retpath->nodes.insert(retpath->nodes.begin(),start);
  
  return retpath;
}


Path* pathToNearestTarget( Map map, Point start, vector<MAPCODE>& accept ) {
  //Path* path_astar( MapCode** map, Point start, Point end ) {

  // Create a parallel 2-D array of "shortest distances" (all "far")
  // Put the start node in the queue.
  // LOOP while queue is not empty
  //   dequeue the first point
  //   LOOP for each direction
  //     see if the distance to that tile is less than the distance here
  //     If so, update the distance.
  //   Reorder the queue.

  PathTrack** parallelMap = new PathTrack*[map.width()];
  for (int x=0; x<map.width(); x++) {
    parallelMap[x] = new PathTrack[map.height()];
    for (int y=0; y<map.height(); y++) {
      parallelMap[x][y].at.x = x;
      parallelMap[x][y].at.y = y;

      parallelMap[x][y].prev.x = 255; // no path back (yet)
      parallelMap[x][y].prev.y = 255;
      parallelMap[x][y].dist = EdgeFar;

      parallelMap[x][y].visited = false;
      parallelMap[x][y].queued = false;
    }
  }

  // Start is 0 from itself. The rest get calculated.
  parallelMap[start.x][start.y].dist = 0;

  Path empty;
  vector<Point> queue;
  Point curr;
  queue.push_back(start);
  while (queue.size() > 0) {
    /*
    cout << endl << asText(map,empty,parallelMap) << endl << endl;
    cout << "Queue: ";
    for (vector<Point>::iterator i = queue.begin();
         i != queue.end();
         i++) {
      cout << " " << (*i);
    }
    cout << endl;
    */

    // Get the first point in the queue.
    curr = queue[0];

    MAPCODE c = map.at(curr.x,curr.y);
    bool found_good = false;
    for (vector<MAPCODE>::iterator pc = accept.begin();
         pc != accept.end();
         pc++) {
      if (*pc == c) {
        found_good = true;
        break;
      }
    }
    if (!found_good) {
      PathTrack* currPT = &(parallelMap[curr.x][curr.y]);
      //cout << "Current: " << curr << " (" << c << ") " << *currPT << endl;

      // Remove it from the queue.
      queue.erase(queue.begin());
      
      // Look at all its neighbors.
      for (int i=0; i<NumDirections; i++) {
        //cout << "  Check " << i << endl;

        Point nextP = go((Direction_t)i,curr.x,curr.y,map.width(),map.height());
        //cout << "   -> " << nextP << endl;
        if (nextP.bad()) continue; // skip edges.
        MAPCODE nextC = map.at(nextP.x,nextP.y);
        if (impassable(nextC,AS_IgnoreViruses)) {
          //cout << "IMPASSABLE! " << nextP << endl;
          continue;
        } // skip impassable moves

        // check the distance
        PathTrack *nextPT = &(parallelMap[nextP.x][nextP.y]);
        if (nextPT->visited) continue;
        EdgeCost nextD = currPT->dist + 1;
        //cout << "   Look: " << nextP << "(" << nextC << ") D(" << nextD << ") " << *nextPT << endl;
        if (nextPT->dist > nextD) {
          nextPT->dist = nextD;
          nextPT->prev = curr;
        }

        currPT->visited = true;
        // Add it to the queue.
        if (!nextPT->queued) {
          nextPT->queued = true;
          queue.push_back(nextP);
        }
      }

      // Prioritize the queue.
      reorderQueue(queue);
    } else {
      cout << "  Found acceptable square " << curr << endl;
      break;
    }
  }

  // return the path, if one exists.
  if (curr.bad()) {
    cout << "No path to open from " << start << endl;
    return NULL;
  }
  // build it
  Path* retpath = new Path;
  retpath->start = start;
  retpath->end = curr;
  Point p = curr;
  while (p != start) {
    retpath->nodes.insert(retpath->nodes.begin(),p);
    PathTrack pt = parallelMap[p.x][p.y];
    p = pt.prev;
  }
  retpath->nodes.insert(retpath->nodes.begin(),start);

  //cout << endl << asText(map,*retpath,parallelMap) << endl << endl;
  
  return retpath;
}



void reorderQueue( vector<Point>& queue ) {
  
}


string asText( Map &m, Path& p, PathTrack **tracking ) {
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

      if (p.nodes.size()) {
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
      }

      if (tracking) {
        if (tracking[x][y].visited) {
          sout << "*";
          continue;
        } else if (tracking[x][y].queued) {
          sout << "o";
          continue;
        }
      }

      sout << ".";
    }
    sout << endl;
  }

  return sout.str();
}
