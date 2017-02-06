// Exercise 1.8 (p11)
// indentify legal statements, fixed the illegal ones.

#include <iostream>
int main() {
  std::cout << "/*";
  std::cout << "*/";
//  std::cout << /* "*/" */;  // this one is illegal
  std::cout << /* "*/" /* "/*" */;
}
