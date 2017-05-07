// Test heapsort.hpp

#include <vector>
#include <iostream>
#include <algorithm>

#include <sort/heapsort.hpp>

using namespace algs;
using std::vector;
using std::cout; using std::endl;
using std::is_sorted;

int main ()
{
  MaxPQ<int> pqt1(10);
  MaxPQ<char> pqt2{};
  cout << "Created a MaxPQ<int>(10) and MaxPQ<char>()" << endl;

  vector<double> v({1.0, 2.0, 1.5, 9.4, -1, 55});
  MaxPQ<double> pq(std::move(v));
  cout << "created a MaxPQ:" << endl << pq << endl;
  cout << "Pop all elements: " << endl;
  while (!pq.empty()) {
    cout << pq.pop() << " | ";
  }
  cout << endl;

  MinPQ<double> mpq(v);
  cout << "Created a MinPQ with vector:" << endl;
  cout << mpq << endl;

  v = vector<double>{0, 2, 1, 3, -4, 9};
  heapsort(v.begin(), v.end());
  cout << "v is sorted: " << is_sorted(v.begin(), v.end()) << endl;

  return 0;
}
