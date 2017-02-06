#include <iostream>
#include <string>

int main()
{
  const std::string exclaim = "!";
  const std::string message = "Hello" + exclaim + " World" + exclaim;

  std::cout << message << std::endl;

  return 0;
}
