// test the std random class

#include "stdrandom.hpp"
#include <iostream>

using namespace std;
using namespace algs;

int main() {
  for (int i = 0; i < 10; ++i)
    cout << StdRandom::uniform(1000) << endl;
  for (int i = 0; i < 10; ++i)
    cout << StdRandom::uniform() << endl;
  return 0;
}
