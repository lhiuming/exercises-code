// Exercise 1.11 (p13)
// print a inclusive range defeind by inputed intergers.

#include <iostream>
int main() {
  std::cout << "Enter 2 intergers: " << std::endl;
  int a, b;
  std::cin >> a >> b;
  while (a <= b) {
    std::cout << a << " ";
    a ++; // it seems that space is allowed before ++ operator
  }
  std::cout << std::endl;
  return 0;
}
