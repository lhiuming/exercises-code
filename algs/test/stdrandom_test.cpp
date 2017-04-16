// test the std random class

#include "stdrandom.hpp"
#include <iostream>

using namespace std;
using namespace algs;

int main() {
  for (int i = 0; i < 10; ++i)
    cout << StdRandom::uniform(1000) << ' ';
  cout << endl;
  for (int i = 0; i < 5; ++i)
    cout << StdRandom::uniform() << ' ';
  cout << endl;
  vector<double> t(5);
  StdRandom::uniform(t);
  for (int i = 0; i < 5; ++i)
    cout << t[i] << '\t';
  cout << endl;
  return 0;
}
