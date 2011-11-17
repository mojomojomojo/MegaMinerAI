#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  vector<int> randomOrder;
  for (int i=0; i<10; i++) {
    randomOrder.push_back(rand()%10000 * 100 + i);
  }
  for (vector<int>::iterator i = randomOrder.begin();
       i != randomOrder.end();
       i++ ) {
    cout << setw(6) << *i << endl;
  }
  sort(randomOrder.begin(),randomOrder.end());
  cout << endl << "Sorted:" << endl;
  for (vector<int>::iterator i = randomOrder.begin();
       i != randomOrder.end();
       i++ ) {
    cout << setw(6) << *i << endl;
  }
}
