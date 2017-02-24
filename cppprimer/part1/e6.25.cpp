// Exercise 6.25 (p220)
// reading command line arguments

#include <iostream>
#include <string>
#include <cstddef>

using namespace std;

int main(int argc, char **argv)
{
  string ret;
  for (size_t i = 1; i != argc; ++i)
    ret += argv[i];
  cout << ret << endl;
  return 0;
}
