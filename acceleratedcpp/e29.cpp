#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
  // reading the input
  int a, b;
  cout << "Please input 2 numbers: ";
  cin >> a >> b;

  // store the larger one in 'a'
  if (b > a)
    a = b;

  // print a
  cout << "The larger one is : " << b << endl;

  return 0;
}
