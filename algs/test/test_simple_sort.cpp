// Test simple_sort.hpp

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <functional>

#include <sorting/simple_sort.hpp>
#include <utils/random.hpp>
#include <utils/io.hpp>

using namespace algs;
using std::vector;
using std::string;
using std::cout; using std::endl;

int main()
{
  const int test_size = 100;
  const int seq_size = 50;

  using Iter = std::vector<double>::iterator;
  using SortFunc = std::function<void (Iter, Iter)>;
  auto test = [](string name, SortFunc sort) { // copy and sort
    vector<double> b;
    cout << "test " << name << ": ";
    for (int i = 0; i < test_size; ++i) {
      Random::uniform(b, seq_size);
      sort(b.begin(), b.end());
      if (!std::is_sorted(b.begin(), b.end())) {
        cout << "failed at " << i << " of " << test_size << endl;
        return;
      }
    } // end for
    cout << "\t passed. " << endl;
  };

  test("selection_sort", [=](Iter b, Iter e) { selection_sort(b, e); });
  test("insertion_sort", [=](Iter b, Iter e) { insertion_sort(b, e); });
  test("shellsort", [=](Iter b, Iter e) { shellsort(b, e); });

  return 0;
}
