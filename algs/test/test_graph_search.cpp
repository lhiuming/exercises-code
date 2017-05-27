// Test graph_search.hpp

#include <graphs.hpp>

#include <iostream>

using namespace std;
using namespace algs;

int main()
{
  cout << "-- read the graph --" << endl;
  Graph g(cin);
  cout << g << endl;

  // DFS
  cout << "-- do dfs --" << endl;
  auto dfs = depth_first_search(g, 0);
  cout << "df path(0 -> 3): " <<  dfs.path_to(3) << endl;

  // bfs
  cout << "-- do bfs --" << endl;
  auto bfs = breadth_first_search(g, 0);
  cout << "bf path(0->3): " << bfs.path_to(3) << endl;

  return 0;
}
