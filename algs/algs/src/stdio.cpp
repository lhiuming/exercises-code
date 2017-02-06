#include "stdio.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdio>

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::endl;

namespace algs {

vector<int> read_ints() {
  vector<int> a;
  read_vector(a);
  return a;
}

void print_ints(const vector<int>& a) {
  typedef vector<int>::size_type size_t;
  for (size_t i = 0; i < a.size(); i++) {
    std::printf("%4d", a[i]);
  }
  cout << endl;
}

} // namespace algs
