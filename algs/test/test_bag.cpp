// Test bag.hpp

#include <fundamentals/bag.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace algs;

int main()
{
  // Construct
  Bag<string> bag;

  // Modifier
  bag.add("Sai");
  bag.add("Lily.B.Anry");
  cout << "added 2: " << bag << endl;

  return 0;
}
