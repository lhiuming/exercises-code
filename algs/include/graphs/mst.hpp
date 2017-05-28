#ifndef ALGS_GRAPHS_MST_HPP
#define ALGS_GRAPHS_MST_HPP

#include <vector>
#include <ostream>

#include <sorting/heapsort.hpp> // for algs::MinPQ

/*
 * mst.hpp
 * Define a MST class and Prim's algorithm.
 */

namespace algs {

// MST class, to store the result
template<class EWGraph>
class MST {
public:

  // Member types
  using index_type = typename EWGraph::index_type;
  using edge_type = typename EWGraph::edge_type;
  using adj_type = typename EWGraph::adj_type;

  // Constructors
  MST() = delete;
  MST(adj_type&& edges) : mst(edges), total_weights(edge_weight_sum(mst)) {}

  // Access
  const adj_type& edges() const { return mst; }
  double weights() const { return total_weights; }

  // Self-printing
  friend std::ostream& operator<<(std::ostream& os, const MST& mst) {
    os << "MST(w=" << mst.weights() << "){" << std::endl;
    for (const edge_type& e : mst.edges())
      os << e << std::endl;
    return os << "}";
  }

private:

  const adj_type mst;
  const double total_weights = 0;

  // Helpers
  static double edge_weight_sum(const adj_type& edges) {
    double ret = 0;
    for (const edge_type& e : edges) ret += e.weight;
    return ret;
  }

};


// Lazy Prim's MST algorithm //

// helper
template<class EWGraph, class Index, class Marker, class PQ>
inline void __lazy_prims_mst_visit(const EWGraph& G, Index v,
  Marker& visited, PQ& pq) {
  visited[v] = true;
  for (const auto& e : G.adjacency(v))
    if (!visited[e.other(v)]) pq.insert(e);
}

// Main procedure of Lazy Prim
template<class EWGraph>
MST<EWGraph> lazy_prims_mst(const EWGraph& G) {

  // type alias
  using edge_type = typename EWGraph::edge_type;
  using adj_type = typename EWGraph::adj_type;

  // algorithm variables
  std::vector<bool> visited(G.V(), false);
  MinPQ<edge_type> edge_queue;
  adj_type mst;

  // Start lazy prim
  __lazy_prims_mst_visit(G, 0, visited, edge_queue); // start from vertex 0
  while (!edge_queue.empty())  {
    edge_type e = edge_queue.pop();
    bool ineligible = ( visited[e.v] && visited[e.w] );
    if (ineligible) continue;
    mst.add(e); // add the eligible edge
    if (!visited[e.v]) __lazy_prims_mst_visit(G, e.v, visited, edge_queue);
    if (!visited[e.w]) __lazy_prims_mst_visit(G, e.w, visited, edge_queue);
  }

  // Return a MST object
  return MST<EWGraph>(std::move(mst));
}



} // namespace algs

#endif
