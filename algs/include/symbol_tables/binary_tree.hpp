#ifndef ALGS_SYMBOL_TABLES_BINARY_TREE_HPP
#define ALGS_SYMBOL_TABLES_BINARY_TREE_HPP

#include <cstddef>    // for size_type
#include <functional> // for std::less
#include <utility>    // for std::pair
#include <ostream> // self printing

/*
 * binary_tree.hpp
 * Binary Search Tree (BST) Symbol Table Implementation.
 * Interface naming is mimicing std::map.
 *
 * TODO: thre rest interface (rank-based query) (probably never do it)
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
    friend BST;
  public:
    BidirectIt(Node* pn = nullptr) : pNode(pn) {}
    value_type& operator*() const { return pNode->val; }
    value_type* operator->() const { return &(pNode->val); }
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
    friend BST;
  public:
    ConstBidirectIt(Node* pn = nullptr) : BidirectIt(pn) {}
    ConstBidirectIt(BidirectIt&& rhs) : BidirectIt(rhs) {}
    // block the non-const operator* and operator->
    const value_type& operator*() const { return BidirectIt::pNode->val; }
    value_type* const operator->() const { return &(BidirectIt::pNode->val); }
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
  iterator begin() { // the role of min in ALGS book
    if (root == nullptr) return this->end();
    return iterator(min(root));
  }
  const_iterator begin() const { return cbegin(); }
  const_iterator cbegin() const { return const_cast<BST*>(this)->begin(); }
  iterator end() { // the role of max in ALGS book
    return iterator();
  }
  const_iterator end() const { return cend(); }
  const_iterator cend() const { return const_cast<BST*>(this)->end(); }

  // Element access and modifiers
  void insert(const Key& k, const T& t) { insert(Key(k), T(t)); }
  void insert(Key&& k, T&& t) { put(root, k, t); }
  iterator find(const Key& k) { // get a iterator by key
    return iterator(get(root, k)); }
  size_type erase(const Key& k) { // erase a key-value pair
    Node* x = get(root, k);
    if (x == nullptr) return 0;
    Node* succ = erase(x);
    if (root == x) root = succ;
    delete x; // release the erased node
    return 1;
  }
  iterator erase(iterator pos) {
    Node* succ = erase(pos.pNode);
    delete pos.pNode;
    return iterator(succ);
  }

  // Capacity
  bool empty() const { return root == nullptr; }
  size_type size() const { return node_size(root); }

  // lookup
  bool contains(const Key& k) const { // existency query
    return get(root, k) != nullptr; }
  const_iterator floor(const Key& k) const { // largest key <= k (floor)
    return const_iterator(floor(root, k)); }
  const_iterator ceiling(const Key& k) const { // smallest key >= k (ceiling)
    return const_iterator(ceiling(root, k)); }
  const_iterator lower_bound(const Key& k) const { // first key >= k
    return ceiling(k); }
  const_iterator upper_bound(const Key& k) const { // first key > k
    return const_iterator(upper_bound(root, k)); }
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
  static size_type node_size(Node* x) { return (x == nullptr) ? 0 : x->count; }

  // Put a pair into a (sub-)tree, return the new (subtree-)root
  void put(Node* &x, Key& key, T& mapped, Node* parent = nullptr) {
    // Make a new node if it's the first one
    if (x == nullptr) {
      x = new Node(std::move(key), std::move(mapped), parent);
      return;
    }
    if (less(key, x->val.first)) put(x->left, key, mapped, x);
    else if (less(x->val.first, key)) put(x->right, key, mapped, x);
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

  // Get the largest node <= the given key
  Node* floor(Node* x, const Key& key) const {
    if (x == nullptr) return nullptr;
    if (less(key, x->val.first)) return floor(x->left, key);
    if (less(x->val.first, key)) {
      Node* hit = floor(x->right, key);
      if (hit == nullptr) return x;
      else return hit;
    }
    return x;
  }

  // Get the smallest node >= the given key
  Node* ceiling(Node* x, const Key& key) const {
    if (x == nullptr) return nullptr;
    if (less(x->val.first, key)) return ceiling(x->right, key);
    if (less(key, x->val.first)) {
      Node* hit = ceiling(x->left, key);
      if (hit == nullptr) return x;
      else return hit;
    }
    return x;
  }

  // Get the smallest node > the given key
  Node* upper_bound(Node* x, const Key& key) const {
    if (x == nullptr) return nullptr;
    if (less(key, x->val.first)) {
      Node* hit = upper_bound(x->left, key);
      if (hit == nullptr) return x;
    }
    return upper_bound(x->right, key);
  }

  // Helper for removes
  static void relink(Node* up, Node* down, Node* hint) {
    if (down != nullptr) down->parent = up;
    if (up != nullptr) {
      if (up->left == hint) up->left = down;
      else up->right = down;
    }
  }

  // Remove the min node from a sub-tree while maitaining the counts;
  // return pointer to the removed node
  static Node* remove_min(Node* x) {
    if (x == nullptr) return nullptr;
    if (x->left == nullptr) { // if x has no left, just replace x by x->right
      relink(x->parent, x->right, x);
      return x;
    } else { // otherwise, remove_min on the left-subtree
      Node* ret = remove_min(x->left);
      x->count = node_size(x->left) + node_size(x->right) + 1;
      return ret;
    }
  }

  // Pop-out the given node while maitaining the counts
  // return a pointer to the succesor node (may be nullptr)
  Node* erase(Node* x) {
    if (x == nullptr) return nullptr;
    Node* succ;
    if (x->left == nullptr) { // Trivial case 1: no left child
      succ = x->right;
      relink(x->parent, x->right, x);
    } else if (x->right == nullptr) { // Trivial case 2: no right child
      succ = x->left;
      relink(x->parent, x->left, x);
    } else { // Non-Trivial case: both children exist
      succ = remove_min(x->right);
      // replace x by succ relinking the neighbours of x
      relink(x->parent, succ, x);
      relink(succ, x->left, nullptr); // NOTE: succ->left must be nullptr
      relink(succ, x->right, succ->right);
      // update succ's count
      succ->count = node_size(succ->left) + node_size(succ->right) + 1;
    }
    // Update the count of all ancesters (use x, because succ can be nullptr)
    for (Node* anc = x->parent; anc != nullptr; anc = anc->parent)
      anc->count = node_size(anc->left) + node_size(anc->right) + 1;
    return succ;
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
