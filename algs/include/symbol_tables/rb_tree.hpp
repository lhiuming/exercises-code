#ifndef ALGS_SYMBOL_TABLES_RB_TREE_HPP
#define ALGS_SYMBOL_TABLES_RB_TREE_HPP

#include <cstddef>    // std::size_t
#include <functional> // std::less
#include <utility>    // std::pair
#include <ostream>    // std::ostream

/*
 * rb_tree.hpp
 * Reb-black Binary Search Tree Symbol Table implementation.
 * Interface naming is mimicing std::map
 *
 * TODO: implementation without iterator
 * TODO: implementation with iterator
 * TODO: check interface compatibility with STL 11
 * TODO: Implement with allocator
 */

namespace algs {

template<
  class Key,
  class T,
  class Compare = std::less<Key>
> class RedBlackBST {
public:

  // Type alias
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using key_compare = Compare;
  // using allocator_type = Allocator
  using reference = value_type&;
  using const_reference = const value_type&;
  // using pointer = std::allocator_traits<Allocator>::pointer;
  // using const_pointer ...

  // Member class
  // TODO
  class value_compare;

private:

  // Color for red-black node
  enum class Color : bool { red, black };

  // Node class, with triple-link and color
  struct Node {
    value_type val; // key and mapped
    size_type count;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Color color;

    Node(Key&& k, T&& t, Node* par, Color c)
    : val(k, t), count(1), parent(par), color(c) {}
  };

public:

  // Iterator classes (Bidirectional Iterator)
  class iterator {
    // TODO
  };
  class const_iterator {
    // TODO
  };

  // Reverse Iterators alias
  // TODO: Implement iterator first
  //using reverse_iterator = std::reverse_iterator<iterator>;
  //using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  // Constructors
  // TODO : complete family
  RedBlackBST(Compare comp = Compare()) : root(nullptr), less(comp) {}
  RedBlackBST(const RedBlackBST& rhs) = delete;

  // Destructors
  // TODO
  ~RedBlackBST() = default;

  // Others
  // TODO
  RedBlackBST& operator=(const RedBlackBST& rhs);
  RedBlackBST& operator=(RedBlackBST&& rhs);
  // get_allocator() const

  // Iterators
  // TODO
  iterator begin();
  const_iterator begin() const;
  const_iterator cbegin() const;
  iterator end();
  const_iterator end() const;
  const_iterator cend() const;

  // Element access by key
  // TODO
  // mapped_type at(Key)
  // mapped_type operator[](Key )

  // Element access and modifiers
  void clear() noexcept { delete_down(root); }
  // TODO complete family of inserts
  void insert(const Key& k, const T& t);
  void insert(Key&& k, T&& t);
  // TODO
  // std::pair emplace();
  // std::pair emplace_hint();
  // TODO
  size_type erase(const Key& k);
  iterator erase(iterator pos);
  // TODO : may access allocator
  void swap(RedBlackBST& others) noexcept;

  // Capacity
  bool empty() const { return root == nullptr; }
  size_type size() const { return node_size(root); }
  size_type max_size() const; // TODO

  // Lookups
  // TODO
  size_type count(const Key& k) const;
  iterator find(const Key& k);
  const_iterator find(const Key& k) const;
  // TODO : range queries
  // std::pair<iterator,iterator> equal_range(const Key& k);
  // std::pair<const_iterator,const_iterator> equal_range(const Key& k) const;
  iterator lower_bound(const Key& k);
  const_iterator lower_bound(const Key& k) const ;
  iterator upper_bound(const Key& k);
  const_iterator upper_bound(const Key& k) const ;

  // Observer
  // TODO
  key_compare key_comp() const;
  value_compare value_comp() const;

  // Non-standards //

  // ALGS facilities or alias
  // TODO
  bool contains(const Key& k) const;
  const_iterator floor(const Key& k) const ;
  const_iterator ceiling(const Key& k) const ;
  size_type rank(const Key& k) const ;
  const Key& select(size_type r) const ;
  size_type size(const Key& lo, const Key& hi) const ;

  // Printing
  friend std::ostream& operator<<(std::ostream& os, const RedBlackBST& rb) {
    // TODO
    os << "RedBlackBST(" << rb.size() << ")[Not implemented]";
    return os;
  }

private:

  Node* root = nullptr;
  Compare less;

  // Implementation Helpers //

  // Get node size with checking
  static size_type node_size(Node* x) { return (x == nullptr) ? 0 : x->count; }

};


// Non-members //

// Lexicographically compares template
// TODO
// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=

// Template specialization
// TODO : Alloc template argument
template<class Key, class T, class Compare>
void swap(RedBlackBST<Key,T,Compare>& lhs, RedBlackBST<Key,T,Compare>& rhs)
noexcept {
  lhs.swap(rhs);
}

} // namespace algs

#endif
