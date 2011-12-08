#include "Coverage.h"
#include <string>

using namespace std;

bool CoverageOfficer::advance() {
  // 
}

int CoverageOfficer::NextDir( int cDir, int aDir ) {
  int n = cDir + aDir;
  if (n<0) n += NumDirs;
  n %= NumDirs;

  return n;
}


Point CoverageOfficer::go( Direction_t dir, coord_t x, coord_t y,
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

bool CoverageOfficer::impassable( MAPCODE c ) {
  if (c == WALL || c == OPBASE || c == MYBASE) return true;
  // Check for virus strength; perhaps avoid being check-mated by a stronger
  //  virus.
  //  if ((c == OPVIRUS || c == MYVIRUS) && behavior | AS_DontCrossViruses) return true;
  return false;
}

Path* CoverageOfficer::pathToNearestTarget(
    Map map, Point start,
    vector<MAPCODE>& acceptPri, // prioritized
    int cDir, int aDir
) {
  // This is Djikstra's algorithm.

  // Create a parallel 2-D array of "shortest distances" (all "far")
  // Put the start node in the queue.
  // LOOP while queue is not empty
  //   dequeue the first point
  //   LOOP for each direction (according to dirOrient)
  //     If the distance here is greater than the distance to the remembered
  //       acceptable target. Accept that point as the target.
  //
  //     If this point is an acceptable target:
  //       If there is no remembered acceptable target, remember this one.
  //       Otherwise, if this one has a higher priority than the remembered
  //         one, remember this one.
  //
  //     See if the distance to that tile is less than the distance here
  //     If so, update the distance.


  // This is the parallel 2-D array used to track backward from a point
  //   to the start point.
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
  Point curr,best(255,255);
  size_t best_priority; // A lower number is a higher priority.
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

    if (!best.bad() && 
        parallelMap[best.x][best.y].dist < parallelMap[curr.x][curr.y].dist) {
      // Stop looking.
      _NotifySubordinates("All distances are greater than the best: ("
                          <<parallelMap[best.x][best.y].dist<<") "<<best);
      break;
    }

    // Determine if the current point is an acceptable target.
    MAPCODE c = map.at(curr.x,curr.y);
    size_t c_priority = 0xFFFF; // really low
    bool found_good = false;
    for (size_t i=0; i<acceptPri.size(); i++) {
      if (acceptPri[i] == c) {
        found_good = true;
        c_priority = i;
        _TakeNotes("Curr is acceptable: ("<<c_priority<<") "<<curr);
        break;
      }
    }
    if (found_good) {
      // Check to see if this move could make the virus at 'start' vulnerable
      //   to an attack. (one move lookahead)

      // If there is no remembered acceptable target, remember this one.
      // Otherwise, if this one has a higher priority than the remembered
      //   one, remember this one.
      if (best.bad() ||
          best_priority > c_priority) {
        if (best.bad()) _TakeNotes(" No previously found acceptable target.");
        best = curr;
        best_priority = c_priority;
        _TakeNotes("Found acceptable target: ("<<best_priority<<") "<<best);
      }
    }
    
    // Keep looking...
    PathTrack* currPT = &(parallelMap[curr.x][curr.y]);
    //cout << "Current: " << curr << " (" << c << ") " << *currPT << endl;

    // Remove it from the queue.
    queue.erase(queue.begin());
    
    // Look at all its neighbors.
    // Check the directions in the specified order (cDir,aDir).
    bool first = true;
    for (int i=cDir; !first&&i!=cDir; i=NextDir(i,aDir),first=false) {
      _TakeNotes(" Checking " << i);

      Point nextP = go((Direction_t)i,curr.x,curr.y,map.width(),map.height());
      _TakeNotes("   -> " << nextP);

      if (nextP.bad()) continue; // skip edges.
      MAPCODE nextC = map.at(nextP.x,nextP.y);
      if (impassable(nextC)) {
        //cout << "IMPASSABLE! " << nextP << endl;
        continue;
      } // skip impassable moves

      // check the distance
      PathTrack *nextPT = &(parallelMap[nextP.x][nextP.y]);
      if (nextPT->visited) continue;
      EdgeCost nextD = currPT->dist + 1;
      _TakeNotes("   Look: " << nextP << "(" << nextC << ") D(" << nextD << ") " << *nextPT);
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
  }

  // return the path, if one exists.
  if (curr.bad()) {
    cout << "No path to open from " << start << endl;
    return NULL;
  }
  // build it
  Path* retpath = new Path;
  retpath->start = start;
  retpath->end = best;
  Point p = curr;
  while (p != start) {
    retpath->nodes.insert(retpath->nodes.begin(),p);
    PathTrack pt = parallelMap[p.x][p.y];
    p = pt.prev;
  }
  retpath->nodes.insert(retpath->nodes.begin(),start);

  _TakeNotes(endl << asText(map,*retpath,parallelMap) << endl << endl);
  
  return retpath;
}


string CoverageOfficer::asText( Map &m, Path& p, PathTrack **tracking ) {
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
