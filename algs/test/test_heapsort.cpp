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

  vector<double> v({1.0, 2.0, 1.5, 9.4, -1, 55});
  MaxPQ<double> pq(v);
  cout << "created a MaxPQ:" << endl << pq << endl;
  cout << "Pop all elements: " << endl;
  while (!pq.empty()) {
    cout << pq.pop() << " | ";
  }
  cout << endl;

  MinPQ<double> mpq(v);
  cout << "Created a MinPQ with vector:" << endl;
  cout << mpq << endl;

  return 0;
}
