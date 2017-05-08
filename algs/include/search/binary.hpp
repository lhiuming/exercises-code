#ifndef ALGS_SEARCH_BINARY_HPP
#define ALGS_SEARCH_BINARY_HPP

#include <functional> // for std::less (default less_compare)
#include <vector> // container

#include "symbol_table.hpp" // base class

/*
 * binary.hpp
 * Binary Search Symbol Table, using a ordered container. Just a basic ST.
 * NOTE: don't supports custume containers
 */

namespace algs {

template<
  class Key,
  class Value,
  class Compare = std::less<Key>
> class BinarySearchST : public ST<Key, Value> {

public:

  using size_type = typename std::vector<Value>::size_type;

  // Default constructor
  BinarySearchST() = default;
  // Iniialized with initial capacity
  BinarySearchST(size_type cap) {
    keys.reserve(cap);
    values.reserve(cap);
  }

  // Destructor
  ~BinarySearchST() = default;

  // element access and modifiers
  void put(const Key& k, const Value& v) override {
    // TODO
    // binary search (rank k) to find position of k
    // step elements to the right
    return;
  }
  void put(Key&& k, Value&& v) override {
    // TODO
    // use a procedure shared with above
    return;
  }
  const Value& get(const Key& k) override {
    // TODO
    return values.back();
  }
  Value pop(const Key& k) override {
    // TODO
    return values.back();
  }

  // capacity
  bool empty() override { return keys.empty(); }
  int size() override { return keys.size(); }

  // lookup
  bool contains(Key k) override {
    // TODO
    return false;
  }
  const Key& min() override { return keys.front(); }
  const Key& max() override { return keys.back(); }
  const Key& floor(const Key& k) override {
    // TODO
    return keys.front();
  }
  const Key& ceiling(const Key& k) override {
    // TODO
    return keys.front();
  }
  size_type rank(const Key& k) override {
    // TODO
    // binary search
    return keys.size();
  }
  const Key& select(size_type r) override {
    // TODO
    return keys.front();
  }
  size_type size(const Key& lo, const Key& hi) override {
    // TODO
    return keys.size();
  }

private:
  std::vector<Key> keys;
  std::vector<Value> values;

  // Implementation helpers
  bool binary_search_k(Key k, size_type& ind) {
    // if find k, return true, else return false
  }

};

} // namespace algs

#endif
