#ifndef ALGS_GRAPHS_GRAPH_HPP
#define ALGS_GRAPHS_GRAPH_HPP

#include <vector> // default container
#include <istream> // input construction
#include <ostream> // self-printing

#include <fundamentals/bag.hpp>

/*
 * graph.hpp
 * Graph template class. Using adjacency-list implementation described in
 * the ALGS book.
 *
 * TODO: implement a adjacency-set Graph (with ST and SET)
 */

namespace algs {

template<class IndexType = std::size_t>
class Graph {
public:

  // Member types
  using index_type = IndexType;
  using adj_type = Bag<index_type>;
  using adj_list_type = std::vector<adj_type>;

  // Constructors
  Graph() {}
  Graph(index_type V) : _V(V), adj(V) {}
  Graph(std::istream& in) {
    in >> _V >> _E; // read size
    adj.resize(_V); // initialized the container with capacity
    for (index_type e = 0; e < _E; ++e) { // read all undirected edges
      index_type v, w;
      in >> v >> w;
      adj[w].add(v);
      adj[v].add(w);
    }
  }

  // Vertex adjacency access
  const adj_type& adjacency(index_type v) const { return adj[v]; }

  // Capacity
  index_type V() const { return _V; }
  index_type E() const { return _E; }

  // Modifiers
  void add_edge(index_type w, index_type v) { // undirected
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

private:

  index_type _V = 0; // vertices number; fixed after construction
  index_type _E = 0; // edge number
  adj_list_type adj; // adjacency list

};

} // namespace algs

#endif
