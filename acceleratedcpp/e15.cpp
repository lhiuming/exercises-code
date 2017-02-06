#include <iostream>
#include <string>

int main()
{
  { std::string s = "a string";
    { std::string x = s + ", nested";
      std::cout << x << std::endl;}
    std::cout << s << std::endl;
  }

  return 0;
}
   
