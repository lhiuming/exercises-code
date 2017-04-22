// test the Array class

#include <iostream>
#include <vector>

#include "Array.hpp"

using namespace algs;
using namespace std;

int main(int argc, char **argv)
{
  Array<int> a(10);
  cout << "Success create a Array(10)." << endl;

  int temp[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5,
  1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5,
  1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
  Array<int> b(temp);
  cout << "Success converting from a c-array " << endl;

  cout << "Try to print it: " << b << endl;
  cout << "Print successed" << endl;

  cout << "b[1] = " << b[1] << ", b[2] = " << b[2] << endl;
  cout << "OK random access" << endl;

  return 0;
}
