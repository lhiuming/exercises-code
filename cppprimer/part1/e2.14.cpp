// Exercise 2.14 (p49)
// name scope of 'for' statements

#include <iostream>
int main() {
  int i = 100, sum = 0;
  for (int i = 0; i != 10; ++i)
    sum += i;
  // should print 100.
  std::cout << i << " " << sum << std::endl;
}
