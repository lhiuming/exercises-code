// Test mergetsort.hpp

#include <vector>
#include <algorithm>

#include <sorting/mergesort.hpp>
#include <utils.hpp>

using namespace algs;
using std::vector;
using std::cout; using std::endl;
using std::is_sorted;

int main()
{
  vector<int> a = {1, 4, 6, 8};
  vector<int> b = {-9, -2, 3, 8, 9};
  vector<int> o(a.size() + b.size());
  cout << "-- merging --" << endl;
  cout << "a : " << a << endl;
  cout << "b : " << b << endl;
  merge(a.begin(), a.end(), b.begin(), b.end(), o.begin());
  cout << "merge a&b :" << o << endl;


  return 0;
}
