#include <string>
#include <iostream>

int main()
{
  std::string a = "front";
  std::string b = a + ", is " + "ok?";
  std::string c = "eh, " + a + ", is " + "ok?";
  //std::string d = "eh, " + "fail, " + a + ", is " + "ok?";

  std::cout << a  << std::endl;
  std::cout << b << std::endl;
  std::cout << c << std::endl;
  // std::cout << d << std::endl;
  return 0;
}
