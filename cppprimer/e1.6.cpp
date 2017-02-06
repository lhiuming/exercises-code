// Exercise 1.6 (p9)
// fix a buggy program about printing

/*
 * Original, illegal code is
 *
 * std::cout << "The sum of " << v1;
 *           << " and " << v2;
 *           << " is " << v1 + v2 << std::endl;
 *
 * To fix them, you just remove some semi-colons; they discard
 * the return value of some << operators, leaving no left
 * operants for some following operators.
 */

#include <iostream>
int main() {
  std::cout << "Enter two nums: " << std::endl;
  int v1 = 0, v2 = 0;
  std::cin >> v1 >> v2;
  // -- beginning of fixed code --
  std::cout << "The sum of " << v1
            << " and " << v2
            << " is " << v1 + v2 << std::endl;
  // -- the end of fixed code --
  return 0;
}
