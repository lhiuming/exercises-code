#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

int main()
{
  const int dim = 7;

  cout << endl;
  for (int i = 0; i != dim; ++i)
    cout << string(dim, '*') << endl;
  cout << endl;

  for (int i = 1; i <= dim; ++i)
    cout << string(i, '*') << endl;
  cout << endl;

  return 0;
}
