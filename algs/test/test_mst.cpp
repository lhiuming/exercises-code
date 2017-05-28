// Test MST module

#include <iostream>
#include <graphs/mst.hpp>
#include <graphs/weighted_graph.hpp>

using namespace std;
using namespace algs;

int main()
{
  EdgeWeightedGraph g(cin);
  cout << "Input ewg: " << g << endl;
  auto mst = lazy_prims_mst(g);
  cout << mst << endl;

  return 0;
}
