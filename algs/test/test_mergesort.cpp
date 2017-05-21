// Test mergetsort.hpp

#include <vector>
#include <algorithm>

#include <sorting/mergesort.hpp>
#include <utils.hpp>

using std::vector;
using std::cout; using std::endl;
using std::is_sorted;
using namespace algs;

int main()
{
  cout << "-- merging --" << endl;
  vector<int> a = {1, 4, 6, 8, 9, 9, 10, 13, 88};
  vector<int> b = {-9, -2, 3, 8, 9};
  vector<int> o(a.size() + b.size());
  cout << "a : " << a << endl;
  cout << "b : " << b << endl;
  merge(a.begin(), a.end(), b.begin(), b.end(), o.begin());
  cout << "merge a&b :" << o << endl;

  cout << "-- inplace merging --" << endl;
  vector<int> im = a;
  im.insert(im.end(), b.begin(), b.end());
  cout << "im : " << im << endl;
  algs::inplace_merge(im.begin(), im.begin() + a.size(), im.end());
  cout << "inplace merged : " << im << endl;

  cout << "-- mergesort --" << endl;
  vector<double> v;
  Random::uniform(v, 100);
  mergesort(v.begin(), v.end());
  cout << "v is_sorted: " << is_sorted(v.begin(), v.end()) << endl;

  cout << "-- BU mergesort --" << endl;
  vector<double> u;
  Random::uniform(u, 100);
  bottomup_mergesort(u.begin(), u.end());
  cout << "v is_sorted: " << is_sorted(u.begin(), u.end()) << endl;

  return 0;
}
