// Test the graph class

#include <graphs/graph.hpp>
#include <iostream>

using namespace std;
using namespace algs;

int main() {

  Graph g(cin);
  cout << "Created a graph from cin." << endl;
  cout << g << endl;

  return 0;
}
