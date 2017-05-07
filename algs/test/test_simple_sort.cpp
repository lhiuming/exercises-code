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
  vector<double> a{-1, 123, 12123123, 0, 23};
  cout << "a = " << a << endl;
  selection_sort(a.begin(), a.end());
  cout << "sorted a = " << a << endl;
  cout << "a sorted: " << is_sorted(a.begin(), a.end()) << endl;
}
