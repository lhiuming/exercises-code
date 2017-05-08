#ifndef ALGS_SEARCH_SYMBOL_TABLE_HPP
#define ALGS_SEARCH_SYMBOL_TABLE_HPP

#include <cstddef> // for std::size_t

/*
 * symbol_table.hpp
 * Define the ST (symbol table) interface. We assume each key is distinctive.
 */

namespace algs {

template<class Key, class Value>
class ST {
public:

  using key_type = Key;
  using value_type = Value;
  using size_type = std::size_t;

  // Constructor and Virtual Destructor
  ST() {};
  virtual ~ST() {};

  // Interfaces //

  // iterators
  //iterator cbegin() = 0;
  //iterator cend() = 0;
  //iterator cbegin(Key k) = 0;
  //iterator cend(Key k) = 0; // at least one past k

  // element access and modifiers
  virtual void put(const Key& k, const Value& v) = 0;  // put a key-value pair
  virtual void put(Key&& k, Value&& v) = 0;  // move a key-value pair
  virtual const Value& get(const Key& k) const = 0;          // get a value by key
  virtual Value pop(const Key& k) = 0; // erase a key-value pair
  virtual Value pop_min() { return pop(min()); }  // erase smallest key
  virtual Value pop_max() { return pop(max()); }  // erase largest key

  // capacity
  virtual bool empty() const = 0; // is the table empty ?
  virtual size_type size() const = 0;   // number of all kay-value pairs

  // lookup
  virtual bool contains(const Key& k) const = 0; // existency query
  virtual const Key& min() const = 0; // smallest key
  virtual const Key& max() const = 0; // greatest key
  virtual const Key& floor(const Key& k) const = 0;   // largest key that is <= k
  virtual const Key& ceiling(const Key& k) const = 0; // smallest key that is >= k
  virtual size_type rank(const Key& k) const = 0;    // number of keys < k
  virtual const Key& select(size_type r) const = 0; // key of rank r
  virtual size_type size(const Key& lo, const Key& hi) const = 0; // number of keys in [lo, hi]

};

} // namespace

#endif
