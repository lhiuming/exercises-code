#ifndef ALGS_SYMBOL_TABLES_BINARY_TREE_HPP
#define ALGS_SYMBOL_TABLES_BINARY_TREE_HPP

#include "symbol_tables.hpp"

/*
 * binary_tree.hpp
 * Binary Search Tree (BST) Symbol Table Implementation.
 */

namespace algs {

template<
  class Key,
  class Value
  class Compare = std::less<Key>
> class BST : public ST<Key, Value> {

  using size_type = typename ST<Key, Value>::size_type;

public:

private:

};

} // namespace algs

#endif
