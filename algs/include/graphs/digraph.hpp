#ifndef ALGS_GRAPHS_DIGRAPH_HPP
#define ALGS_GRAPHS_DIGRAPH_HPP

#include <vector>

#include <fundamentals/bag.hpp>

namespace algs {

template<class Index = std::size_t>
class IndexDigraph {
public:

  // Member types
  using index_type = Index;
  using vertex_type = Index;
  using adj_type = Bag<vertex_type>;
  using adj_list_type = std::vector<adj_type>;

  // Constructors
  IndexDigraph() = delete;
  IndexDigraph(vertex_type V) : _V(V), adj(V) {}
  IndexDigraph(std::istream& in) {
    in >> _V >> _E; // read size
    adj.resize(_V); // initialized the container with capacity
    for (vertex_type e = 0; e < _E; ++e) { // read all undirected edges
      vertex_type v, w;
      in >> v >> w;
      adj[v].add(w);
    }
  }

  // Vertex adjacency access
  const adj_type& adjacency(vertex_type v) const { return adj[v]; }

  // Capacity
  vertex_type V() const { return _V; }
  vertex_type E() const { return _E; }

  // Modifiers
  void add_edge(vertex_type v, vertex_type w) { // undirected
    adj[v].add(w);
    ++_E;
  }

  // Reversion
  IndexDigraph reverse() const {
    IndexDigraph ret(V());
    for (index_type v = 0; v < V(); ++v)
      for (index_type w : adjacency(v))
        ret.add_edge(w, v);
    return ret;
  }

  // Swap
  void swap(IndexDigraph& other) noexcept {
    std::swap(adj, other.adj);
    std::swap(_V, other._V);
    std::swap(_E, other._E);
  }

  // Addional functionality //

  // self-printing
  friend std::ostream& operator<<(std::ostream& os, const IndexDigraph& g) {
    os << "Digraph(V = " << g._V << ", E = " << g._E << ") {";
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

// Define a most-common digraph
typedef IndexDigraph<int> Digraph;

} // namespace algs

#endif
