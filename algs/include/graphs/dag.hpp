#ifndef ALGS_GRAPHS_DAG_HPP
#define ALGS_GRAPHS_DAG_HPP

#include <vector>

#include <fundamentals.hpp> // queue and stack

/*
 * dag.hpp
 * Some algorithms about DAG.
 */

namespace algs {

template<class Graph>
class DepthFirstOrders {
public:

  // Member types
  using index_type = typename Graph::index_type;
  using pre_type = Queue<index_type>;
  using post_type = Queue<index_type>;
  using reverse_post_type = Stack<index_type>;

  // Constructor
  DepthFirstOrders(const Graph& G) : visited(G.V())
  {
    for (index_type i = 0; i < G.V(); ++i)
      if (!visited[i]) dfs(G, i);
  }

  // Result access
  const pre_type& pre() const { return pre_queue; }
  const post_type& post() const { return post_queue; }
  const reverse_post_type& reverse_post() const { return rp_stack; }

private:

  std::vector<bool> visited;
  pre_type pre_queue;
  post_type post_queue;
  reverse_post_type rp_stack;

  void dfs(const Graph& G, index_type s) {
    visited[s] = true;

    pre_queue.push(s);

    for (index_type w : G.adjacency(s))
      if (!visited[w]) dfs(G, w);

    post_queue.push(s);
    rp_stack.push(s);
  }

};

// Make a DF order result
template<class Graph>
DepthFirstOrders<Graph> depth_first_order(const Graph& G) {
  return DepthFirstOrders<Graph>(G);
}

template<class Graph>
typename DepthFirstOrders<Graph>::reverse_post_type
topological_order(const Graph& G) {
  return DepthFirstOrders<Graph>(G).reverse_post();
}

} // namespace algs

#endif
