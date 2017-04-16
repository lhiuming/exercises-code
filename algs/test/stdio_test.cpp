// test the stdio functions

#include "stdio.hpp"
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::endl;
using std::vector;
using std::string;

int main()
{
  // test read_ints()
  cout << "--- read_ints() and print_ints()--" << endl;
  vector<int> a = algs::read_ints();
  algs::print_ints(a);

  return 0;
}
