#include <stdlib.h>
#include <time.h>

#include <queue>
#include <iostream>
using namespace std;

class A {
public:
  int a;
  int b;
};

int main() {
  priority_queue<int> q;
  srand(time(NULL));

  for (int i=0; i<15; i++) {
    q.push(rand()%100);
  }

  for (priority_queue<int>::iterator i = q.begin();
       i != q.end();
       i++) {
    cout << " " << *i;
  }
  cout << endl;
}
