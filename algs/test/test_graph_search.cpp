// Test graph_search.hpp

#include <graphs.hpp>

#include <iostream>

using namespace std;
using namespace algs;

int main()
{
  cout << "-- read the graph --" << endl;
  Graph<> g(cin);
  cout << g << endl;

  // DFS
  cout << "-- do dfs --" << endl;
  auto dfs = depth_first_search(g, 0);
  cout << "path(0 -> 3): " <<  dfs.path_to(3) << endl;

  return 0;
}
