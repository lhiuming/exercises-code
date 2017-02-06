// Exercise 2.12 (p47)
// to see wiich is an invalid name

// int double = 3.1; // double is reserved
int _ = 1; // no idea. Actually valid! but it is outside a function...
  int _a = 0; // this is also valid; but they should be reserved ...
  // may be clang++ just imposes a looser constrain...
// int catch-22; // - is no allowed
// int 1_or_2 = ; // cannt begin with digits
double Double = 3.14; // valid

#include <iostream>
int main() {
  std::cout << _ << _a;
  return 0;
}
