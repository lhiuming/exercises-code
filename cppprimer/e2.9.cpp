// Exercise 2.9 (p44)
// test the result of the examples

#include <iostream>
int main()
{
  // std::cin >> int intput_value; // should fail. declarement should be alone.
  int i = { 3.14 }; // should fail; curly braces require narrowed conversion
    // in fact, only warning in clang++ !
  // double salary = wage = 9999.99; // should fail; what type is wage?
  int j = 3.14; // should be ok

  return 0;
}
