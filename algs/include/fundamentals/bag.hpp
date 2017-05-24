#ifndef ALGS_FUNDAMENTALS_BAG_HPP
#define ALGS_FUNDAMENTALS_BAG_HPP

#include "list.hpp"

/*
 * bag.hpp
 * Bag implemented with linked-list (List<>). This class use an interface
 * named in STL fashion (basically a simplified Stack)
 *
 * TODO: non-member functions and helper class.
 */

namespace algs {

template<class Item>
class Bag {
public:

  // Member types
  using container_type  = List<Item>;
  using value_type      = typename container_type::value_type;
  using size_type       = typename container_type::size_type;
  using const_reference	= typename container_type::const_reference;
  using const_iterator  = typename container_type::const_iterator;

  // Constructors
  // TODO : more constructors (see Stack)
  Bag() {}

  // Copy Constrol : basically controlled by List<Item>
  ~Bag() = default;

  // Iterators (required by ALGS book) (we dont allow modification)
  const_iterator begin() const noexcept { return data.begin(); }
  const_iterator cbegin() const noexcept { return data.cbegin(); }
  const_iterator end() const noexcept { return data.cend(); }
  const_iterator cend() const noexcept { return data.cend(); }

  // Capacity
  bool empty() const { return data.empty(); }
  size_type size() const { return N; }

  // Modifier //

  // just adding; Bag is simple!
  void add(const Item& item) { data.push_front(item); ++N; }
  void add(Item&& item) { data.push_front(std::move(item)); ++N; }

  // NOTE: we return const_reference
  template< class... Args > const_reference emplace( Args&&... args ) {
    ++N; return data.emplace_front(std::forward<Args>(args)...); }

  void swap(Bag& other) noexcept {
    using std::swap;
    swap(data, other.data);
  }

  // Non-standdard //

  // self-priting
  friend std::ostream& operator<<(std::ostream& os, const Bag& bag) {
    os << "Bag(" << bag.N << "){";
    if (bag.empty()) return os << "}";
    os << bag.data.front();
    for (auto i = ++(bag.begin()); i != bag.end(); ++i)
      os << ", " << *i;
    return os << "}";
  }

private:

  container_type data;
  size_type N = 0;

};


// Non-member functions //
// TODO

// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=
// std::swap(algs::Bag) (specification in std namespace)


// Helper class //
// TODO

// std::uses_allocator<algs::Bag>

} // namespace algs

#endif
