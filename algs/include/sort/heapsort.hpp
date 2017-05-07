#ifndef ALGS_HEAPSORT_H
#define ALGS_HEAPSORT_H

#include <vector> // default container in PQ
#include <ostream> // for PQ print
#include <string>  // for PQ print
#include <functional>
#include <iterator>

/*
 * Priority Queue, two wrapper calss, and Heapsort.
 */

namespace algs {

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

  using size_type = typename Container::size_type;

  // Default constructor
  explicit PQ(Compare comp = Compare()) : compare_less(comp) {};
  // Initialized with reserved capacity
  explicit PQ(size_type c, Compare comp = Compare()) : PQ(comp) {
    heap.reserve(c + 1); }

  // Initialized with given elements (moving)
  template<class ForwardIt>
  PQ(ForwardIt b, ForwardIt e, Compare comp = Compare()) : PQ(comp) {
    for (; b != e; ++b) insert(std::move(*b)); }

  // Copy or Move the elements in a given container
  PQ(const Container& a, Compare comp = Compare()) : PQ(comp) {
    for (auto&& v : a) insert(v); }
  PQ(Container&& a, Compare comp = Compare()) : PQ(a.size(), comp) {
    for (auto&& v : a) insert(v); }

  // Copy a element into the queue
  void insert(const T& v) { heap.push_back(v); swim(++N); }
  // Move a element into the queue
  void insert(T&& v) { heap.push_back(v); swim(++N); }

  // Return a direct reference to the most prior element
  const T& head() const { return heap[1]; }
  // Return and delete the most prior element
  T pop() {
    T head = std::move(heap[1]); // take the most prior element
    exch(1, N--); // put the head at the end
    sink(1); // re-heapify
    heap.pop_back(); // delete the old head
    return head;
  }

  // Size of the queue
  bool empty() const { return N == 0; }
  std::size_t size() const { return N; }

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
    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
  }
  void swim(size_type k) { // let heap[k] to swim up to right position
    while (k > 1 && this->prior(k, k/2)) { // dynamic binding ?
      exch(k/2, k); // exchange with parent
      k = k/2;
    }
  } // end swim
  void sink(size_type k) { // let heap[k] to sink down to right position
    while (2 * k <= N) {
      size_type j = 2 * k;  // index of left-child
      if (j < N && prior(j+1, j)) j++; // choose right-child if it is prior
      if (!prior(j, k)) break; // end of sink : both children are not prior
      exch(k, j);
      k = j;
    }
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


// Heapsort ////////////////////////////////////////////////////////////////////
// Do a in-place heapsort using a PQ.
////

// Heapsort with a customized less-comparing object
template<class ForwardIt, class Compare>
void heapsort(ForwardIt b, ForwardIt e, Compare less)
{
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  // Move out the elements in to a PQ
  using std::placeholders::_1;
  using std::placeholders::_2;
  auto greater = std::bind(less, _2, _1); // used to reverse PQ's direction
  PQ<value_type, std::vector<value_type>, decltype(greater)> pq(b, e, greater);
  // Move back from the PQ
  for (; b != e; ++b) (*b) = pq.pop(); // thie should cause `move`
}

// Heapsort with default less-compare (usually is `operator<`)
template<class ForwardIt>
inline void heapsort(ForwardIt b, ForwardIt c)
{
  using value_type = typename std::iterator_traits<ForwardIt>::value_type;
  heapsort(b, c, std::less<value_type>());
}

} // namespace algs

#endif
