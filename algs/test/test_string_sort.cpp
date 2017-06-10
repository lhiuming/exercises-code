// Test string_sort.hpp

#include <iostream>

#include <strings/string_sort.hpp>
#include <utils.hpp>

using namespace std;
using namespace algs;

int main()
{
  vector<string> a { "abd", "ZZZ", "Abd", "Qdd", "dZZ" , "Abd"};
  cout << "origin: " << a << endl;
  lsd_string_sort(a.begin(), a.end(), 3);
  cout << "sorted: " << a << endl;

  return 0;
}
