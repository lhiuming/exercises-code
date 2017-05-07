// Test simple_sort.hpp

#include <vector>
#include <iostream>
#include <algorithm>

#include <sort/simple_sort.hpp>
#include <utils/io.hpp>

using namespace algs;
using std::vector;
using std::cout; using std::endl;

int main()
{
  vector<double> b, a{-1, -5, 0, 0, 123, 12123123, 0, 23};
  cout << "data is: " << a << endl;

  cout << "-- test selection sort --" << endl;
  b = a;
  selection_sort(b.begin(), b.end());
  cout << "sorted: " << b << endl;
  cout << "is sorted = " << is_sorted(b.begin(), b.end()) << endl;

  cout << "-- test insertion sort --" << endl;
  b = a;
  insertion_sort(b.begin(), b.end());
  cout << "sorted: " << b << endl;
  cout << "is sorted = " << is_sorted(b.begin(), b.end()) << endl;

  return 0;
}
