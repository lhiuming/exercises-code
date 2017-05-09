#ifndef ALGS_FUNDAMENTALS_STACK_HPP
#define ALGS_FUNDAMENTALS_STACK_HPP

#include "list.hpp"

/*
 * stack.hpp
 * Stack implemented with linked list.
 */

namespace algs {

template<class Item>
class Stack {

public:

  using size_type = typename List<Item>::size_type;

  // Default constructor
  Stack() {};

  // Copy Constrol : basically controlled by List<Item>
  ~Stack() = default;
  Stack(const Stack&) = default;
  Stack& operator=(const Stack&) = default;

  // basic interface
  void push(Item&& item);
  Item pop();
  bool empty();
  size_type size();

private:

  List<Item> data;

};

} // namespace algs

#endif
