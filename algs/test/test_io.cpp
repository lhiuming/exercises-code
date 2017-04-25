// Test io.hpp

#include <vector>
#include <iostream>

#include <utils/io.hpp>

using namespace std;
using namespace algs;

int main()
{
  vector<int> read;
  cin >> read;
  cout << "Read numbers: " << read << endl;

  return 0;
}
