#ifndef ALGS_SYMBOL_TABLES_BINARY_TREE_HPP
#define ALGS_SYMBOL_TABLES_BINARY_TREE_HPP

#include <functional> // for std::less
#include <ostream> // self printing

#include "symbol_table.hpp" // base class

/*
 * binary_tree.hpp
 * Binary Search Tree (BST) Symbol Table Implementation.
 *
 * TODO: implement basic interface
 * TODO: add iterators
 */

namespace algs {

template<
  class Key,
  class Value,
  class Compare = std::less<Key>
> class BST : public ST<Key, Value> {

  using size_type = typename ST<Key, Value>::size_type;

  // a private two-children node
  struct Node {
    Key key;
    Value val;
    size_type count;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(Key&& k, Value&& v) : key(k), val(v), count(1) {};
  };

public:

  // Default constructor
  BST(Compare comp = Compare()) : root(nullptr), less(comp) {};

  // Copy controls
  ~BST() = default;

  // element access and modifiers
  void put(const Key& k, const Value& v) override { // put a key-value pair
    put(Key(k), Value(v)); }
  void put(Key&& k, Value&& v) override { // move a key-value pair
    put(root, std::move(k), std::move(v)); }
  const Value& get(const Key& k) const override { // get a value by key
    // TODO
    return Value();
  }
  Value pop(const Key& k) override { // erase a key-value pair
    // TODO
    return Value();
  }

  // capacity
  bool empty() const override { return root == nullptr; }
  size_type size() const override { // number of all kay-value pairs
    if (this->empty()) return 0;
    return root->count;
  }

  // lookup
  bool contains(const Key& k) const override { // existency query
    // TODO
    return true;
  }
  const Key& min() const override { // smallest key
    // TODO
    return Key();
  }
  const Key& max() const override { // greatest key
    // TODO
    return Key();
  }
  const Key& floor(const Key& k) const override { // largest key <= k
    // TODO
    return Key();
  }
  const Key& ceiling(const Key& k) const override { // smallest key >= k
    // TODO
    return Key();
  }
  size_type rank(const Key& k) const override { // number of keys < k
    // TODO
    return 0;
  }
  const Key& select(size_type r) const override { // key of rank r
    // TODO
    return Key();
  }
  size_type size(const Key& lo, const Key& hi) const override {
    // number of keys in [lo, hi]
    // TODO
    return 0;
  }

  // Printing
  friend std::ostream& operator<<(std::ostream& os, const BST& bst) {
    // TODO : use an iterator ?
    os << "{" << std::endl;
    os << bst.root;
    os << "}";
    return os;
  }


private:
  Node* root = nullptr;
  Compare less;

  // Implementation Helpers //

  // Put a pair into a (sub-)tree, return the new (subtree-)root
  void put(Node* &x, Key&& key, Value&& val) {
    // Make a new node if it's the first one
    if (x == nullptr) {
      x = new Node(std::move(key), std::move(val));
      return;
    }
    if (less(key, root->key)) put(x->left, std::move(key), std::move(val));
    else if (less(root->key, key)) put(x->right, std::move(key), std::move(val));
    else x->val = std::move(val);
  }

  // recursive printing of nodes
  friend std::ostream& operator<<(std::ostream& os, Node* x) {
    if (x == nullptr) return os;
    os << x->left;
    os << "  " << x->key << " : " << x->val << "," << std::endl;
    os << x->right;
    return os;
  }

};

} // namespace algs

#endif
