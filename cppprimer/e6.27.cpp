// Exercise 6.27 (p222)
// using initializer_list

#include <iostream>
#include <initializer_list>

int list_sum(std::initializer_list<int> il)
{
  int ret = 0;
  for(const int &i : il)
    ret += i;
  return ret;
}

int main() {
  std::cout << list_sum({1, 2, 3}) << std::endl;
  return 0;
}
