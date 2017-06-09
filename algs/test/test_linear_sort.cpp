// Test linear_sort.hpp

#include <vector>
#include <iostream>

#include <sorting/linear_sort.hpp>
#include <utils/io.hpp>

using namespace std;
using namespace algs;

int main()
{
  vector<int> a {1, 3, 0, 2, 9, 4, -4, 999, -3, -100010};
  radix_sort(a.begin(), a.end());

  cout << a << endl;

  return 0;
}
