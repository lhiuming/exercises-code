#ifndef ALGS_SEARCH_BINARY_HPP
#define ALGS_SEARCH_BINARY_HPP

#include <functional> // for std::less (default less_compare)
#include <vector> // container
#include <ostream> // for self-print

#include "symbol_table.hpp" // base class

/*
 * binary.hpp
 * Binary Search Symbol Table, using a ordered container. Just a basic ST.
 * Memory management is delegated to STL (by using standard std::vector).
 */

namespace algs {

template<
  class Key,
  class Value,
  class Compare = std::less<Key>
> class BinarySearchST : public ST<Key, Value> {

  using size_type = std::size_t; // base not instantiated yet

public:

  // Default constructor
  BinarySearchST(Compare comp = Compare()) : less(comp) {};
  // Iniialized with initial capacity
  BinarySearchST(size_type cap, Compare comp = Compare()) : less(comp) {
    keys.reserve(cap);
    values.reserve(cap);
  }

  // Destructor
  ~BinarySearchST() = default;

  // element access and modifiers
  void put(const Key& k, const Value& v) override { // delegated
    this->put( std::move(Key(k)), std::move(Value(v)) ); }
  void put(Key&& k, Value&& v) override {
    // binary search (rank k) to find proper postion of k
    size_type ind = rank(k, 0, this->size());
    // put at the position
    if (ind == this->size()) { // push back if key should be at the end
      keys.push_back(k);
      values.push_back(v);
    } else if (!less(k, keys[ind]))  // replace the element if key has exists
      values[ind] = v;
    else { // otherwise, just insert; std::vector move elements for us
      keys.insert(keys.begin() + ind, k);
      values.insert(values.begin() + ind, v);
    }
  }
  const Value& get(const Key& k) const override {
    return values.at(rank(k, 0, this->size())); }
  Value pop(const Key& k) override {
    size_type ind = rank(k, 0, this->size());
    Value take = std::move(values.at(ind));
    keys.erase(keys.begin() + ind);
    values.erase(values.begin() + ind);
    return std::move(take);
  }

  // capacity
  bool empty() const override { return keys.empty(); }
  size_type size() const override { return keys.size(); }

  // lookup
  bool contains(const Key& k) const override {
    size_type ind = rank(k);
    return (ind < this->size()) && !less(k, keys[ind]);
  }
  const Key& min() const override { return keys.front(); }
  const Key& max() const override { return keys.back(); }
  const Key& floor(const Key& k) const override {
    size_type ind = rank(k);
    if (!less(k, keys[ind])) return k;
    return keys.at(ind - 1);
  }
  const Key& ceiling(const Key& k) const override {
    return keys.at(rank(k)); }
  size_type rank(const Key& k) const override {
    return rank(k, 0, this->size()); }
  const Key& select(size_type r) const override {
    return keys.at(r); }
  size_type size(const Key& lo, const Key& hi) const override {
    if (less(hi, lo)) return 0;
    if (contains(hi)) return rank(hi) - rank(lo) + 1;
    return rank(hi) - rank(lo);
  }

  // Print like a dictionary
  friend std::ostream& operator<<(std::ostream& os, const BinarySearchST& st)
  {
    os << "{" << std::endl;
    for (size_type i = 0; i < st.size(); ++i)
      os << "  " << st.keys[i] << " : " << st.values[i] << ", " << std::endl;
    os << "}";
    return os;
  }

private:

  Compare less;
  std::vector<Key> keys;
  std::vector<Value> values;

  // Implementation helpers //

  // return rank of k from [lo, hi), using binary search. (assume: hi <= size())
  size_type rank(const Key& k, size_type lo, size_type hi) const {
    if (hi <= lo) return lo; // terminates recursion
    size_type mid = lo + (hi - lo) / 2;
    const Key& mid_key = keys[mid];
    if (less(k, mid_key)) return rank(k, lo, mid);
    if (less(mid_key, k)) return rank(k, mid + 1, hi);
    return mid;
  }

};

} // namespace algs

#endif
