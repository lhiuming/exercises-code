// Test directed graph

#include <iostream>

#include <graphs/digraph.hpp>

using namespace std;
using namespace algs;

int main()
{
  Digraph dig(cin);
  cout << "Create a digrap" << endl;
  cout << dig << endl;

  cout << "Reverse it: " << dig.reverse() << endl;

  return 0;
}
