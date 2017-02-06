// Exercise 1.4 (p9)
// multiply 2 numbers instead of adding (see page 6)

#include <iostream>
int main()
{
  std::cout << "Enter two nums: " << std::endl;
  int a = 0, b = 0;
  std::cin >> a >> b;
  std::cout << "The product of " << a << " and " << b
            << " is " << a * b << std::endl;
  return 0;
}
