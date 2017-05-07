// Test simple_sort.hpp

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

#include <sort/simple_sort.hpp>
#include <utils/io.hpp>

using namespace algs;
using std::vector;
using std::string;
using std::cout; using std::endl;

int main()
{
  vector<double>  a{-1, -5, 0, 0, 123, 12123123, 0, 23};
  cout << "data is: " << a << endl;

  using Iter = std::vector<double>::iterator;
  using SortFunc = std::function<void (Iter, Iter)>;
  auto test = [a](string name, SortFunc sort) { // copy and sort
    vector<double> b = a;
    cout << "-- test " << name << " --" << endl;
    sort(b.begin(), b.end());
    cout << "sorted: " << b << endl;
    cout << "is sorted: " << std::is_sorted(b.begin(), b.end()) << endl;
  };

  test("selection_sort", [=](Iter b, Iter e) { selection_sort(b, e); });
  test("insertion_sort", [=](Iter b, Iter e) { insertion_sort(b, e); });
  test("shellsort", [=](Iter b, Iter e) { shellsort(b, e); });

  return 0;
}
