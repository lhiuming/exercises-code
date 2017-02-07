// Exercise 2.32 (p67)
// pointer and constexpr

int null = 0;
int *p = &null; // wierd solutions; Is this the intend of the exercise?

#include <iostream>
int main() {
  std::cout << p << std::endl;
  return 0;
}
