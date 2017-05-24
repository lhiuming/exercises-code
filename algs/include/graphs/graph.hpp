#ifndef ALGS_GRAPHS_GRAPH_HPP
#define ALGS_GRAPHS_GRAPH_HPP

#include <vector> // for fixed graph
#include <set> // for dynamic graph
#include <unordered_map> // default symbol table
#include <istream> // input construction
#include <ostream> // self-printing

#include <fundamentals/bag.hpp>

/*
 * graph.hpp
 * Graph and DynamicGraph template class. Using adjacency-list implementation
 * described in the ALGS book.
 *
 * TODO: add a SymbolGraph implementaion (adapt a graph)
 */

namespace algs {

// Graph //////////////////////////////////////////////////////////////////////
// A simple, fixed-vertices-number graph.
////

template<class Index = std::size_t>
class Graph {
public:

  // Member types
  using index_type = Index;
  using vertex_type = Index;
  using adj_type = Bag<vertex_type>;
  using adj_list_type = std::vector<adj_type>;

  // Constructors
  Graph() {}
  Graph(vertex_type V) : _V(V), adj(V) {}
  Graph(std::istream& in) {
    in >> _V >> _E; // read size
    adj.resize(_V); // initialized the container with capacity
    for (vertex_type e = 0; e < _E; ++e) { // read all undirected edges
      vertex_type v, w;
      in >> v >> w;
      adj[w].add(v);
      adj[v].add(w);
    }
  }

  // Vertex adjacency access
  const adj_type& adjacency(vertex_type v) const { return adj[v]; }

  // Capacity
  vertex_type V() const { return _V; }
  vertex_type E() const { return _E; }

  // Modifiers
  void add_edge(vertex_type w, vertex_type v) { // undirected
    adj[w].add(v);
    adj[v].add(w);
    ++_E;
  }

  // Swap
  void swap(Graph& other) noexcept {
    std::swap(adj, other.adj);
    std::swap(_V, other._V);
    std::swap(_E, other._E);
  }

  // Addional functionality //

  // self-printing
  friend std::ostream& operator<<(std::ostream& os, const Graph& g) {
    os << "Graph(V = " << g._V << ", E = " << g._E << ") {";
    for (vertex_type v = 0; v < g._V; ++v) {
      os << std::endl;
      os << v << " : ";
      for (vertex_type w : g.adjacency(v)) os << w << " ";
    }
    return os << std::endl << "}";
  }

private:

  vertex_type _V = 0; // vertices number; fixed after construction
  vertex_type _E = 0; // edge number
  adj_list_type adj; // adjacency list

};


// DynamicGraph ///////////////////////////////////////////////////////////////
// A dynamic graph (allow erasing veteices and edges)
// Container should support insert and erase.
////

template<
  class Index = std::size_t,
  class Container = std::set<Index>, // used as adjacency list
  class SymbolTable = std::unordered_map<Index, Container>
> class DynamicGraph {
public:

  // Member types
  using index_type = Index;
  using vertex_type = Index;
  using adj_type = Container;

  // Constructors
  DynamicGraph() {}
  DynamicGraph(std::istream& in) {
    in >> _V >> _E; // read size
    for (vertex_type e = 0; e < _E; ++e) { // read all undirected edges
      vertex_type v, w;
      in >> v >> w;
      adj[w].insert(v);
      adj[v].insert(w);
    }
  }

  // Vertex adjacency access
  const adj_type& adjacency(vertex_type v) const { return adj.at(v); }

  // Capacity
  vertex_type V() const { return _V; }
  vertex_type E() const { return _E; }

  // Modifiers
  void add_edge(vertex_type w, vertex_type v) { // undirected
    adj[w].insert(v);
    adj[v].insert(w);
    ++_E;
  }

  // Swap
  void swap(DynamicGraph& other) noexcept {
    std::swap(adj, other.adj);
    std::swap(_V, other._V);
    std::swap(_E, other._E);
  }

  // Addional functionality //

  // self-printing
  friend std::ostream& operator<<(std::ostream& os, const DynamicGraph& g) {
    os << "Graph(V = " << g._V << ", E = " << g._E << ") {";
    for (vertex_type v = 0; v < g._V; ++v) {
      os << std::endl;
      os << v << " : ";
      for (vertex_type w : g.adjacency(v)) os << w << " ";
    }
    return os << std::endl << "}";
  }

private:

  vertex_type _V = 0; // vertices number; fixed after construction
  vertex_type _E = 0; // edge number
  SymbolTable adj; // adjacency list

  // Implementation helpers //


};

} // namespace algs

#endif
