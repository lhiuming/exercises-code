#ifndef ALGS_SYMBOL_TABLES_RB_TREE_HPP
#define ALGS_SYMBOL_TABLES_RB_TREE_HPP

#include <cstddef>    // std::size_t
#include <functional> // std::less
#include <utility>    // std::pair
#include <ostream>    // std::ostream
#include <cassert> // debug

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
    value_type val; // std::pair<key, mapped_value>
    size_type count;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Color color;

    Node(Key&& k, T&& t, Node* par, Color c)
    : val(std::move(k), std::move(t)), count(1), parent(par), color(c) {}
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
  ~RedBlackBST() { delete_down(root); }

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

  // Modifiers
  void clear() noexcept { delete_down(root); }
  // TODO complete family of inserts
  void insert(const Key& k, const T& t);
  void insert(Key&& k, T&& t) {
    root = put(root, k, t); // actually moved
    root->color = Color::black; // make sure always black
  }
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
  size_type size() const { return size(root); }
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
    os << "RedBlackBST(" << rb.size() << "){";
    if (rb.root) os << "\n" << rb.root;
    return os << "}";
  }
  friend std::ostream& operator<<(std::ostream& os, const Node* r) {
    const char* sp = ", \n";
    if (r) {
      if (r->left) os << r->left << sp;
      os << r->val.first << " : " << r->val.second;
      if (r->right) os << sp << r->right;
    }
    return os;
  }

private:

  Node* root = nullptr;
  Compare less;

  // Implementation Helpers //

  // Get node size with checking
  static size_type size(Node* x) { return (x == nullptr) ? 0 : x->count; }

  // Check color
  static bool is_red(Node* x) { return x && (x->color == Color::red); }
  static bool is_black(Node* x) { return !x || (x->color == Color::black); }

  // Re-link helpers
  static void take_parent(Node* x, Node* old_child) {
    Node* new_parent = old_child->parent;
    x->parent = new_parent;
    if (new_parent) { // check the parent direction
      if (new_parent->left == old_child) new_parent->left = x;
      else new_parent->right = x;
    }
  }

  // Delete a tree
  static void delete_down(Node* x) {
    if (x == nullptr) return;
    delete_down(x->left);
    delete_down(x->right);
    delete x;
  }

  // Tree rotations //

  // Left rotation; return new root
  static Node* rotate_left(Node* x) {
    Node* y = x->right;
    assert(y->color == Color::red);
    // relink the middle node
    x->right = y->left;
    if (y->left) y->left->parent = x;
    y->left = nullptr; // TODO : no need
    // change position of x and y
    take_parent(y, x); // y take the parent of x
    y->color = x->color;
    x->color = Color::red;
    y->left = x; // relink x and y
    x->parent = y;
    // reset counts
    y->count = x->count;
    x->count = 1 + size(x->left) + size(x->right);

    return y;
  }

  // Right rotation; return new root
  static Node* rotate_right(Node* y) {
    Node* x = y->left;
    assert(x->color == Color::red);
    // relink the middle node
    y->left = x->right;
    if (x->right) x->right->parent = y;
    x->right = nullptr; // TODO : not need
    // change position of x and y
    take_parent(x, y);
    x->color = y->color;
    y->color = Color::red;
    x->right = y; // relink y and x
    y->parent = x;
    // reset counts
    x->count = y->count;
    y->count = 1 + size(y->left) + size(y->right);

    return x;
  }

  // Change 4-node to red node
  static void flip_colors(Node* x) {
    assert(x->left->color == Color::red);
    assert(x->right->color == Color::red);
    assert(x->color == Color::black);
    x->left->color = Color::black;
    x->right->color = Color::black;
    x->color = Color::red;
  }

  // Insertion and deletion of tree-nodes //

  // Insert/Put a pair into a tree; return the root after insertion
  // NOTE: the input pair (k, mapped) is alyways moved !
  Node* put(Node* x, Key& k, T& mapped, Node* parent = nullptr) {
    if (x == nullptr) // default color is red
      return new Node(std::move(k), std::move(mapped), parent, Color::red);

    if (less(k, x->val.first)) x->left = put(x->left, k, mapped, x);
    else if (less(x->val.first, k)) x->right = put(x->right, k, mapped, x);
    else x->val.second = std::move(mapped);

    if (is_red(x->right) && is_black(x->left)) x = rotate_left(x);
    if (is_red(x->left) && is_red(x->left->left)) x = rotate_right(x);
    if (is_red(x->left) && is_red(x->right)) flip_colors(x);

    x->count = 1 + size(x->left) + size(x->right);
    return x;
  }

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
