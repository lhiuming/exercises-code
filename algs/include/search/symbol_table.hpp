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
  //iterator begin() = 0;
  //iterator end() = 0;
  //iterator begin(Key k) = 0;
  //iterator end(Key k) = 0; // at least one past k

  // element access and modifiers
  virtual void put(const Key& k, const Value& v) = 0;  // put a key-value pair
  virtual void put(Key&& k, Value&& v) = 0;  // move a key-value pair
  virtual const Value& get(const Key& k) = 0;          // get a value by key
  virtual Value pop(const Key& k) = 0; // erase a key-value pair
  virtual Value pop_min() { return pop(min()); }  // erase smallest key
  virtual Value pop_max() { return pop(max()); }  // erase largest key

  // capacity
  virtual bool empty() = 0; // is the table empty ?
  virtual int size() = 0;   // number of all kay-value pairs

  // lookup
  virtual bool contains(Key k) = 0; // existency query
  virtual const Key& min() = 0; // smallest key
  virtual const Key& max() = 0; // greatest key
  virtual const Key& floor(const Key& k) = 0;   // largest key that is >= k
  virtual const Key& ceiling(const Key& k) = 0; // smallest key that is < k
  virtual size_type rank(const Key& k) = 0;    // number of keys < k
  virtual const Key& select(size_type r) = 0; // key of rank r
  virtual size_type size(const Key& lo, const Key& hi) = 0; // number of keys in [lo, hi]

};

} // namespace

#endif
