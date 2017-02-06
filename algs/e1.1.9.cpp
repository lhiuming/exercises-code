#include <string>
#include <iostream>

std::string toBinString(int n)
{
  std::string ret;
  if(n == 0) return "0";
  bool neg = (n < 0);
  if(neg) n = -n;
  for (; n > 0; n /= 2) ret = std::to_string(n % 2) + ret;
  if(neg) ret = "-" + ret;
  return ret;
}

int main()
{
  std::cout << toBinString(0) << std::endl;
  std::cout << toBinString(-1) << std::endl;
  std::cout << toBinString(2) << std::endl;
  std::cout << toBinString(-15) << std::endl;
  std::cout << toBinString(17) << std::endl;
  return 0;
}
