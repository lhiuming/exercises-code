// Test the graph class

#include <graphs/graph.hpp>
#include <iostream>

using namespace std;
using namespace algs;

int main() {
  Graph<> g(cin);
  cout << "Created a graph from cin." << endl;
  cout << "V: " << g.V() << endl;
  cout << "E: " << g.E() << endl;

  return 0;
}
