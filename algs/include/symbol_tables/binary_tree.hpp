#ifndef ALGS_SYMBOL_TABLES_BINARY_TREE_HPP
#define ALGS_SYMBOL_TABLES_BINARY_TREE_HPP

#include <cstddef>
#include <functional> // for std::less
#include <utility> // for std::pair
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
  class T,
  class Compare = std::less<Key>
> class BST {

public:

  // Type alias
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const Key, T>;
  using size_type = std::size_t;

private:

  // A private triple-link node
  struct Node {
    value_type val;
    std::size_t count;
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    Node(Key&& k, T&& t, Node* p)
     : val(std::move(k), std::move(t)), count(1), parent(p) {};
  };

  // Iterator class
  class BidirectIt {
  public:
    BidirectIt(Node* pn = nullptr) : pNode(pn) {}
    value_type& operator*() const { return pNode->val; }
    BidirectIt& operator++() {
      if (pNode->right != nullptr) // go the min of right sub-tree, if exists
        pNode = min(pNode->right);
      else // no right sub-tree, then climp up to left
        do {
          Node* old = pNode;
          pNode = pNode->parent; // update
          if (pNode->right != old) break;
        } while (pNode != nullptr);
      return *this;
    }
    BidirectIt& operator--() {
      if (pNode->left != nullptr) // go to the max of left sub-tree if exists
        pNode = max(pNode->left);
      else // no left sub-tree, then climp up to the right
        do {
          Node* old = pNode;
          pNode = pNode->parent; // update
          if (pNode->right != old) break;
        } while (pNode != nullptr);
      return *this;
    }
    bool operator==(const BidirectIt& rhs) const { return pNode == rhs.pNode; }
    bool operator!=(const BidirectIt& rhs) const { return pNode != rhs.pNode; }
  protected:
    Node* pNode = nullptr;
  };

  // Const iterator class
  class ConstBidirectIt : public BidirectIt {
  public:
    ConstBidirectIt(Node* pn = nullptr) : BidirectIt(pn) {}
    ConstBidirectIt(BidirectIt&& rhs) : BidirectIt(rhs) {}
    // block the non-const operator*
    const value_type& operator*() const { return BidirectIt::pNode->val; }
  };

public:

  // More type alias
  using iterator = BidirectIt;
  using const_iterator = ConstBidirectIt;

  // Default constructor
  BST(Compare comp = Compare()) : root(nullptr), less(comp) {};

  // Copy controls
  ~BST() = default;

  // Iterators
  BidirectIt begin() { // the role of min in ALGS book
    if (root == nullptr) return this->end();
    return iterator(min(root));
  }
  ConstBidirectIt begin() const { return cbegin(); }
  ConstBidirectIt cbegin() const { return const_cast<BST*>(this)->begin(); }
  BidirectIt end() { // the role of max in ALGS book
    if (root == nullptr) return BidirectIt();
    return BidirectIt();
  }
  ConstBidirectIt end() const { return cend(); }
  ConstBidirectIt cend() const { return const_cast<BST*>(this)->end(); }

  // Element access and modifiers
  void insert(const Key& k, const T& t) { // put
    insert(Key(k), T(t)); }
  void insert(Key&& k, T&& t) { // move put
    put(root, k, t, nullptr); }
  iterator find(const Key& k) { // get a iterator by key
    return iterator(get(root, k)); }
  T pop(const Key& k) { // erase a key-value pair
    // TODO
    return T();
  }

  // capacity
  bool empty() const { return root == nullptr; }
  size_type size() const { return node_size(root); }

  // lookup
  bool contains(const Key& k) const { // existency query
    return get(root, k) != nullptr;
  }
  const Key& min() const { // smallest key
    if (root == nullptr) return;
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
  void put(Node* &x, Key& key, T& mapped, Node* parent = nullptr) {
    // Make a new node if it's the first one
    if (x == nullptr) {
      x = new Node(std::move(key), std::move(mapped), parent);
      return;
    }
    if (less(key, root->val.first)) put(x->left, key, mapped, x);
    else if (less(root->val.first, key)) put(x->right, key, mapped, x);
    else x->val.second = std::move(mapped);
    x->count = node_size(x->left) + node_size(x->right) + 1;
  }

  // Get a node* by key from a (sub-)tree; return nullptr if not found.
  Node* get(Node* x, const Key& key) const {
    if (x == nullptr) return nullptr;
    if (less(key, x->val.first)) return get(x->left, key);
    if (less(x->val.first, key)) return get(x->right, key);
    return x;
  }

  // Get the left-most node; assume x != nullptr
  static Node* min(Node* x) {
    if (x->left == nullptr) return x;
    return min(x->left);
  }

  // Get the right-most node; assuem x != nullptr
  static Node* max(Node* x) {
    if (x->right == nullptr) return x;
    return max(x->right);
  }

  // recursive printing of nodes
  friend std::ostream& operator<<(std::ostream& os, Node* x) {
    if (x == nullptr) return os;
    os << x->left;
    os << "  " << x->val.first << " : " << x->val.second << "," << std::endl;
    os << x->right;
    return os;
  }

};

} // namespace algs

#endif
