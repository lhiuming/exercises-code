#ifndef ALGS_SYMBOL_TABLES_BINARY_TREE_HPP
#define ALGS_SYMBOL_TABLES_BINARY_TREE_HPP

#include <cstddef>
#include <functional> // for std::less
#include <ostream> // self printing

/*
 * binary_tree.hpp
 * Binary Search Tree (BST) Symbol Table Implementation.
 * Interface naming is mimicing std::map.
 *
 * TODO: implement basic interface
 * TODO: add iterators
 */

namespace algs {

template<
  class Key,
  class Value,
  class Compare = std::less<Key>
> class BST {

  // a private two-children node
  struct Node {
    Key key;
    Value val;
    std::size_t count;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(Key&& k, Value&& v) : key(k), val(v), count(1) {};
  };

  // iterator class
  class BidirectIt {
  public:
    BidirectIt() {}
    BidirectIt(Node* pn, Node* pp = nullptr) : pNode(pn), pParent(pp) {}
    Value& operator*() const { return pNode->val; }
    BidirectIt& operator++() { return *this; } // TODO
    BidirectIt& operator--() { return *this; } // TODO
  private:
    Node* pNode = nullptr;
    Node* pParent = nullptr;
  };
  class ConstBidirectIt : public BidirectIt {

  };

public:

  // More type alias
  using key_type = Key;
  using value_type = Value;
  using size_type = std::size_t;
  using iterator = BidirectIt;
  using const_iterator = ConstBidirectIt;

  // Default constructor
  BST(Compare comp = Compare()) : root(nullptr), less(comp) {};

  // Copy controls
  ~BST() = default;

  // Iterators
  BidirectIt begin(); // TODO
  BidirectIt end() { return BidirectIt(); } // TODO
  ConstBidirectIt cbegin() const; // TODO
  ConstBidirectIt cend() const { return ConstBidirectIt(); }  // TODO

  // Element access and modifiers
  void insert(const Key& k, const Value& v) { // put
    insert(Key(k), Value(v)); }
  void insert(Key&& k, Value&& v) { // move put
    put(root, k, v); }
  iterator find(const Key& k) { // get a value by key
    Node* parent = nullptr; // initial value
    Node* hit = get(root, k, parent);
    if( hit )
      return iterator(hit, parent);
    return this->end();
  }
  Value pop(const Key& k) { // erase a key-value pair
    // TODO
    return Value();
  }

  // capacity
  bool empty() const { return root == nullptr; }
  size_type size() const { return node_size(root); }

  // lookup
  bool contains(const Key& k) const { // existency query
    // TODO
    return true;
  }
  const Key& min() const { // smallest key
    // TODO
    return Key();
  }
  const Key& max() const { // greatest key
    // TODO
    return Key();
  }
  const Key& floor(const Key& k) const { // largest key <= k
    // TODO
    return Key();
  }
  const Key& ceiling(const Key& k) const { // smallest key >= k
    // TODO
    return Key();
  }
  size_type rank(const Key& k) const { // number of keys < k
    // TODO
    return 0;
  }
  const Key& select(size_type r) const { // key of rank r
    // TODO
    return Key();
  }
  size_type size(const Key& lo, const Key& hi) const {
    // number of keys in [lo, hi]
    // TODO
    return 0;
  }

  // Printing
  friend std::ostream& operator<<(std::ostream& os, const BST& bst) {
    // TODO : use an iterator ?
    os << "BST(" << bst.size() << "){" << std::endl;
    os << bst.root;
    os << "}";
    return os;
  }


private:

  Node* root = nullptr;
  Compare less;

  // Implementation Helpers //

  // Take the node size
  size_type node_size(Node* x) const { return (x == nullptr) ? 0 : x->count; }

  // Put a pair into a (sub-)tree, return the new (subtree-)root
  void put(Node* &x, Key& key, Value& val) {
    // Make a new node if it's the first one
    if (x == nullptr) {
      x = new Node(std::move(key), std::move(val));
      return;
    }
    if (less(key, root->key)) put(x->left, key, val);
    else if (less(root->key, key)) put(x->right, key, val);
    else x->val = std::move(val);
    x->count = node_size(x->left) + node_size(x->right) + 1;
  }

  // Get a node* by key from a (sub-)tree; return nullptr if not found.
  Node* get(Node* x, const Key& key, Node* &parent_ret) const {
    if (x == nullptr) return nullptr;
    if (less(key, x->key)) return get(x->left, key, parent_ret = x);
    if (less(x->key, key)) return get(x->right, key, parent_ret = x);
    return x;
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
