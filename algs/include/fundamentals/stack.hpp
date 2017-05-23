#ifndef ALGS_FUNDAMENTALS_STACK_HPP
#define ALGS_FUNDAMENTALS_STACK_HPP

#include "list.hpp"

/*
 * stack.hpp
 * LIFO Stack implemented with linked list.
 * (Very simple, because List<> has done everything.)
 *
 * TODO: add full STL compatibility
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
  void push(const Item& item) { data.push_front(item); ++N; }
  void push(Item&& item) { data.push_front(item); ++N; }
  Item pop() { return data.pop_front(); --N; }
  bool empty() { return data.empty(); }
  size_type size() { return N; }

private:

  List<Item> data;
  size_type N = 0;

};

} // namespace algs

#endif
