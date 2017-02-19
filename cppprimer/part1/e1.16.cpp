// Exercise 1.16 (p17)
// write a program to prints the sum of intergers from cin


#include <iostream>
int main() {
  std::cout << "Please input a sequence of integers "
            << "(terminated with Ctrl-d or non-interger input): "<< std::endl;

  int a, res = 0;
  while(std::cin >> a)
    res += a;
    
  std::cout << "Ths sum is: " << res << std::endl;

  return 0;
}
