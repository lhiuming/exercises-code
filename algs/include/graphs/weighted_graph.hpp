#ifndef ALGS_GRAPHS_WEIGHTED_GRAPH_HPP
#define ALGS_GRAPHS_WEIGHTED_GRAPH_HPP

#include <vector>
#include <stdexcept> // runtime error
#include <ostream> // self-printing
#include <istream> // input construction

#include <fundamentals.hpp> // for algs::Bag

/*
 * weighted_graph.hpp
 * Implement Edge-weighted (undirected) Graph class.
 *
 * TODO: use a more space efficient alternative for adj_type 
 */

namespace algs {

// An Edge class
template<class Index>
class Edge {
public:

  // Public data member
  Index v;
  Index w;
  double weight;

  // Constructor and copy control
  Edge() : v(0), w(0), weight(0.0) {} // must allow for algs::PQ implementation
  Edge(Index v, Index w, double weight) : v(v), w(w), weight(weight) {}

  // Access
  Index other(Index i) const {
    if (i == v) return w;
    if (i == w) return v;
    throw std::runtime_error("Inconsistent edge");
  }

  // Compare
  bool operator<(const Edge& rhs) const { return this->weight < rhs.weight; }
  bool operator>(const Edge& rhs) const { return this->weight > rhs.weight; }

  // Self printing
  friend std::ostream& operator<<(std::ostream& os, const Edge& e) {
    return os << e.v << "-" << e.w << " " << e.weight;
  }

};


// Fixed size Edge-weighted Graph
template<class Index = std::size_t>
class EdgeWeightedIndexGraph {
public:

  // Member types
  using index_type = Index;
  using vertex_type = Index;
  using edge_type = Edge<Index>;
  using adj_type = Bag<edge_type>;
  using adj_list_type = std::vector<adj_type>;

  // Constructor
  EdgeWeightedIndexGraph() = delete;
  EdgeWeightedIndexGraph(index_type V) : _V(V), adj(V) {}
  EdgeWeightedIndexGraph(std::istream& in) {
    in >> _V >> _E;
    adj.resize(_V);
    for (index_type e = 0; e < _E; ++e) {
      index_type v, w;
      double weight;
      in >> v >> w >> weight;
      adj[v].emplace(v, w, weight);
      adj[w].emplace(v, w, weight); // TODO: improve space
    }
  }

  // Vertex adjacency access
  const adj_type& adjacency(vertex_type v) const { return adj[v]; }
  adj_type edges() const {
    adj_type ret;
    for (index_type v = 0; v < _V; v++)
      for (const edge_type& e : adjacency(v))
        if (e.other(v) > v) ret.add(e);
    return ret;
  }

  // Capacity
  vertex_type V() const { return _V; }
  vertex_type E() const { return _E; }

  // Modifiers
  void add_edge(const edge_type& e) { // undirected
    adj[e.v].add(e);
    adj[e.w].add(e);
    ++_E;
  }

  // Reversion
  EdgeWeightedIndexGraph reverse() const {
    EdgeWeightedIndexGraph ret(V());
    for (edge_type e : edges())
      ret.add_edge(edge_type(e.w, e.v, e.weight));
    return ret;
  }

  // Swap
  void swap(EdgeWeightedIndexGraph& other) noexcept {
    std::swap(adj, other.adj);
    std::swap(_V, other._V);
    std::swap(_E, other._E);
  }

  // Addional functionality //

  // self-printing
  friend std::ostream&
  operator<<(std::ostream& os, const EdgeWeightedIndexGraph& g) {
    os << "EWGraph(V = " << g._V << ", E = " << g._E << "){";
    for (edge_type e : g.edges())
      os << std::endl << e;
    return os << std::endl << "}";
  }

private:

  index_type _V = 0; // vertices number; fixed after construction
  index_type _E = 0; // edge number
  adj_list_type adj; // adjacency list

};


// Common usage
typedef EdgeWeightedIndexGraph<int> EdgeWeightedGraph;


} // namespace algs

#endif
