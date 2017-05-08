#ifndef ALGS_COLLECTIONS_LIST_HPP
#define ALGS_COLLECTIONS_LIST_HPP

/*
 * list.hpp
 * Node and (linked-)List. Would be used for Bag, Queue, Stack and others (like
 * Symbol Table. )
 */

namespace algs {

template<Item>
class Node {
  Item item;
  Node* next;
}

} // namespace algs

#endif
