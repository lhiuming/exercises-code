// Test string_sort.hpp

#include <iostream>

#include <strings/string_sort.hpp>
#include <utils.hpp>

using namespace std;
using namespace algs;

int main()
{
  vector<string> a { "abd", "ZZZ", "Abd", "Qdd", "dZZ" , "Abd"};
  cout << a << endl;
  lsd_string_sort(a.begin(), a.end());
  cout << "sorted : " << a << endl;

  return 0;
}
