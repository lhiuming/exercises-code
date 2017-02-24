// Exercise 8.1 (p314)
// using istream

#include <iostream>
#include <string>

std::istream& printFile(std::istream& in)
{
  std::string a;
  while (!in.eof()) {
    in >> a;
    std::cout << a << std::endl;
  }

  in.clear();
  return in;
}
