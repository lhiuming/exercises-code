// Test heapsort.hpp

#include <vector>
#include <iostream>

#include <sort/heapsort.hpp>

using namespace std;
using namespace algs;

int main ()
{
  MaxPQ<int> pqt1(10);
  MaxPQ<char> pqt2{};
  cout << "Created a MaxPQ<int>(10) and MaxPQ<char>()" << endl;

  vector<double> v({1.0, 2.0, 1.5});
  MaxPQ<double> pq(v);
  cout << "created a MaxPQ(v):" << endl;
  while (!pq.isEmpty()) {
    cout << pq.delMax() << endl;
  }

  return 0;
}
