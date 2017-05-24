#ifndef ALGS_FUNDAMENTALS_QUEUE_HPP
#define ALGS_FUNDAMENTALS_QUEUE_HPP

#include <deque> // std::dequeue as default container

/*
 * queue.hpp
 * LIFO Queue implemented with linked list. This class use the same interface
 * as std::queue.
 *
 * TODO: implement a algs::double_list as default container
 */

namespace algs {

template<
  class Item,
  class Container = std::deque<Item>
> class Queue {
public:

  // Member types
  using container_type  = Container;
  using value_type      = typename container_type::value_type;
  using size_type       = typename container_type::size_type;
  using reference	      = typename container_type::reference;
  using const_reference	= typename container_type::const_reference;
  using iterator        = typename container_type::iterator;
  using const_iterator  = typename container_type::const_iterator;

  // Default constructor
  // TODO: support more
  Queue() {};

  // Copy controls
  ~Queue() {};

  // Element access
  reference front() { return data.front(); }
  const_reference front() const { return data.front(); }
  reference back() { return data.back(); }
  const_reference back() const { return data.back(); }

  // Capacity
  bool empty() const { return data.empty(); }
  size_type size() const { return data.size(); }

  // Modifiers (push&emplace - back, pop - front) //

  void push(const value_type& value) { data.push_back(); }
  void push(value_type&& value) { data.push_back(std::move(value)); }

  template<class... Args>
  reference emplace(Args&&... args) {
    return data.emplace_back(std::forward<Args>(args)...); }

  // NOTE: std::queue version returns void
  value_type pop() {
    value_type ret = std::move(data.front());
    data.pop_front();
    return ret;
  }

  // Swap
  void swap(Queue& other) noexcept { using std::swap; swap(data, other.data); }

  // Non-standards //

  // Iterators. This is required in the ALGS book
  iterator begin() noexcept { return data.begin(); }
  const_iterator begin() const noexcept { return data.begin(); }
  const_iterator cbegin() const noexcept { return data.cbegin(); }
  iterator end() noexcept { return data.end(); }
  const_iterator end() const noexcept { return data.end(); }
  const_iterator cend() const noexcept { return data.cend(); }

  // self-priting
  friend std::ostream& operator<<(std::ostream& os, const Queue& queue) {
    os << "Queue(" << queue.size() << "){";
    if (queue.empty()) return os << "}";
    os << queue.front();
    for (auto i = ++(queue.begin()); i != queue.end(); ++i)
      os << ", " << *i;
    return os << "}";
  }

private:

  container_type data;

};


// Non-member functions //
// TODO

// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=
// std::swap(algs::Stack) (specification in std namespace)


// Helper class //
// TODO

// std::uses_allocator<algs::Queue>


} // namespace algs

#endif
