#ifndef ALGS_GRAPHS_GRAPH_SEARCH_HPP
#define ALGS_GRAPHS_GRAPH_SEARCH_HPP

#include "graph.hpp"
#include <fundamentals/stack.hpp>

/*
 * graph_search.hpp
 * Implement depth-first and breadth-first search, for the Graph class.
 * Both are implemented as a class holding a graph and a source.
 */

namespace algs {

// DepthFirstPaths ////////////////////////////////////////////////////////////
// Construct a dfs result, which can return a DF path in linear time.
////

template<class Graph>
class DepthFirstPaths {
public:

  // Member types
  using index_type = typename Graph::index_type;
  using path_type = Stack<index_type>;

  // Constructor
  DepthFirstPaths(const Graph& G, index_type s)
  : source(s), visited(G.V(), false), edge_to(G.V(), G.V()) {
    dfs(G, s);
  }

  // Path queries //

  // reachability
  bool reach(index_type v) const { return visited[v]; }

  // path from source to a target v
  path_type path_to(index_type v) const {
    path_type path;
    if (!reach(v)) return path;
    for (index_type x = v; x != source; x = edge_to[x]) // back trace
      path.push(x);
    path.push(source);
    return path;
  }

private:

  const index_type source;
  std::vector<bool> visited;
  std::vector<index_type> edge_to;

  // Implementation helper //

  // Recursive search
  void dfs(const Graph& G, index_type v) {
    visited[v] = true;
    for (index_type w : G.adjacency(v))
      if (!visited[w]) {
        edge_to[w] = v;
        dfs(G, w);
      }
  }

};


// Make a DFS result
template<class Graph>
DepthFirstPaths<Graph>
depth_first_search(const Graph& G, typename Graph::index_type src) {
  return DepthFirstPaths<Graph>(G, src); }


// BreadthFirstPaths //////////////////////////////////////////////////////////
// Construct a bfs result, which can return a BF path in linear time.
////

template<class Graph>
class BreadthFirstPaths {
public:

  // Member types
  using index_type = typename Graph::index_type;
  using path_type = Stack<index_type>;

  // Constructor
  BreadthFirstPaths(const Graph& G, index_type s)
  : source(s), visited(G.V(), false), edge_to(G.V(), G.V()) {
    dfs(G, s);
  }

private:

};


// Make a BFS result
template<class Graph>
BreadthFirstPaths<Graph>
breadth_first_search(const Graph& G, typename Graph::index_type src) {
  return DepthFirstPaths<Graph>(G, src); }

} // namespace algs

#endif
