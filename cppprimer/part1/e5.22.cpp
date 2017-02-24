// Exercise 5.22 (p193)
// eliminate goto by loop

#include <iostream>

int get_size() { int i; std::cin >> i; return i;}

int main() {
  int sz;
  do sz = get_size();
  while ( sz <= 0 );

  return 0;
}
