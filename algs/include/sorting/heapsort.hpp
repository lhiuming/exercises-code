#ifndef ALGS_SORTING_HEAPSORT_HPP
#define ALGS_SORTING_HEAPSORT_HPP

#include <vector> // default container in PQ
#include <ostream> // for PQ print
#include <string>  // for PQ print
#include <functional>
#include <iterator>

/*
 * Priority Queue, two wrapper calss, and Heapsort.
 *
 *   - heapsort use the same interface as std::sort.
 *   - PQs use the same interface as std::priority_queue.
 *
 * TODO: check STL compatibility for PQ.
 * TODO: add some Heap operations, like in std::algorithms.
 */

namespace algs {

// Some usefull definition //

// Pair printing
template<class T1, class T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pair) {
    return os << "<" << pair.first << ", " << pair.second << ">";
  }

// Priority Queue /////////////////////////////////////////////////////////////
// Comparable must be default-constructable.
// Comparable should supports operator> (for MaxPQ ) or operator< (for MinPQ).
////

// Priority Queue base class
template<
  class T,
  class Container = std::vector<T>,
  class Compare = std::less<T>
> class PQ {

public:

  // Member types
  using container_type = Container;
  using value_compare = Compare;
  using value_type = typename Container::value_type;
  using size_type = typename Container::size_type;
  using reference = typename Container::reference;
  using const_reference	= typename Container::const_reference;

  // Constructors and Copy controls //

  // Default constructor
  explicit PQ(Compare comp = Compare()) : compare_less(comp) {};
  // Initialized with reserved capacity
  explicit PQ(size_type c, Compare comp = Compare()) : PQ(comp) {
    heap.reserve(c + 1); }

  // Initialized with given elements (moving)
  template<class InputIt>
  PQ(InputIt b, InputIt e, Compare comp = Compare()) : PQ(comp) {
    for (; b != e; ++b) insert(std::move(*b)); }

  // Copy or Move the elements in a given container
  PQ(const Container& a, Compare comp = Compare()) : PQ(comp) {
    for (auto&& v : a) insert(v); }
  PQ(Container&& a, Compare comp = Compare()) : PQ(a.size(), comp) {
    for (auto&& v : a) insert(v); }

  // Operations //

  // Copy&Move an element into the queue
  void insert(const T& v) { heap.push_back(v); swim(++N); }
  // Move a element into the queue
  void insert(T&& v) { heap.push_back(v); swim(++N); }

  // Emplace an element in the queue
  // TODO
  void emplace();

  // Return a direct reference to the most prior element
  const_reference top() const { return heap[1]; }
  // TODO: remove this
  const T& head() const { return heap[1]; }
  // Return and delete the most prior element
  value_type pop() {
    T head = std::move(heap[1]); // take the most prior element
    exch(1, N--); // put the head at the end
    sink(1); // re-heapify
    heap.pop_back(); // delete the old head
    return head;
  }

  // Size of the queue
  bool empty() const { return N == 0; }
  size_type size() const { return N; }

  // Swap
  // TODO
  void swap();

  // Print the queue
  friend std::ostream& operator<<(std::ostream& os, const PQ& pq) {
    using std::endl;
    os << pq.name() << "[";
    int head = 1;
    while (head <= pq.size() ) {
      os << endl;
      for (int i = head; (i <= pq.size()) && (i < 2 * head); ++i)
        os << pq.heap[i] << " ";
      head *= 2;
    }
    os << "]";
    return os;
  }

protected:

  // compare object
  Compare compare_less;

  // data member
  Container heap{T()}; // heap[0] is not used.
  size_type N = 0; // index of last valid element = number of valid elements

  // pure virtuals; used to make MaxPQ and MinPQ from PQ
  virtual std::string name() const { return "PQ"; };

  // implementation helpers
  bool prior(size_type i, size_type j) const {
    return compare_less(heap[j], heap[i]);
  }
  void exch(size_type i, size_type j) {
    using std::swap; swap(heap[i], heap[j]); }
  size_type swim(size_type k) { // let heap[k] to swim up to right position
    while (k > 1 && prior(k, k/2)) {
      exch(k/2, k); // exchange with parent
      k = k/2;
    }
    return k; // return final position
  } // end swim
  size_type sink(size_type k) { // let heap[k] to sink down to right position
    while (2 * k <= N) {
      size_type j = 2 * k;  // index of left-child
      if (j < N && prior(j+1, j)) j++; // choose right-child if it is prior
      if (!prior(j, k)) break; // end of sink : both children are not prior
      exch(k, j);
      k = j;
    }
    return k; // return final position
  } // end sink

};


// Max Priority Queue; just a simple wrapper of PQ
template<class Comparable, class Container = std::vector<Comparable>>
class MaxPQ : public PQ<Comparable, Container, std::less<Comparable> > {
  // Define the virtual member for name
  virtual std::string name() const override { return "MaxPQ"; }
public:
  // Default constructor
  MaxPQ() = default;
  // Inheritate other base class constructors
  using PQ<Comparable, Container, std::less<Comparable> >::PQ;
};


// Min Priority Queue; just a simple wrapper of PQ
template<class Comparable, class Container = std::vector<Comparable>>
class MinPQ : public PQ<Comparable, Container, std::greater<Comparable> > {
  // Define the virtual member for name
  virtual std::string name() const override { return "MinPQ"; }
public:
  // Default constructor
  MinPQ() = default;
  // Inheritate other base class constructors
  using PQ<Comparable, Container, std::greater<Comparable> >::PQ;
};


// Heapsort ///////////////////////////////////////////////////////////////////
// In-place heapsort by swapping and sinking.
////

// sink
template<class RandomIt, class DiffType, class Compare>
void heapsort_sink(RandomIt k, DiffType k_pos, DiffType N, const Compare& less)
{ // let [k] sink down to right position; assumming (k, e) is heaplified
  // NOTE: we start from 0, not 1 (like in the PQ)
  DiffType j;
  while ((j = 2 * k_pos + 1) < N) { // left_child exist
    RandomIt lc = k + (k_pos + 2), rc = lc--;
    if ( (j + 1) < N && less(*lc, *rc) ) {// choose right-child if it is larger
      ++j; lc = rc; }
    if (!less(*k, *lc)) break; // end of sink : both children are not larger
    using std::swap;
    swap(*k, *lc);
    k = lc;
    k_pos = j;
  }
} // end sink


// Heapsort with a customized less-comparing object
template<class RandomIt, class Compare>
void heapsort(RandomIt b, RandomIt e, Compare less)
{
  // check the input
  if (b == e) return;
  using diff_type = typename std::iterator_traits<RandomIt>::difference_type;
  // heaplify the range
  diff_type N = e - b, k_pos = (N + 1) / 2;
  RandomIt k = b + k_pos;
  do { heapsort_sink(--k, --k_pos, N, less); } while (k_pos > 0);
  // pop the head to the end of heap
  while (--e != b) {
    using std::swap;
    swap(*b, *e);
    --N;
    heapsort_sink(b, static_cast<diff_type>(0), N, less);
  }
}

// Heapsort with default less-compare (usually is `operator<`)
template<class RandomIt>
inline void heapsort(RandomIt b, RandomIt c)
{
  using value_type = typename std::iterator_traits<RandomIt>::value_type;
  heapsort(b, c, std::less<value_type>());
}

} // namespace algs

#endif
