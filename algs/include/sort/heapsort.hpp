#ifndef ALGS_HEAPSORT_H
#define ALGS_HEAPSORT_H

#include <vector>

/*
 * Priority Queue, Binary Heap, and Heapsort.
 */


namespace algs {

// Max PQ /////////////////////////////////////////////////////////////////////
// Currently using only std::vector as contatiner, using native compara
// operator (<) of the Comparable type.
// TODO: support C++11 move
template<typename Comparable>
class MaxPQ {
public:

  typedef typename std::vector<Comparable> Container;
  typedef typename Container::size_type size_type;

  // Constructor
  MaxPQ() {};
  MaxPQ(size_type cap) { // with initial capacity
    heap.reserve(cap+1); }
  MaxPQ(Container& a) { // with a container of elements
    heap.reserve(a.size() + 1);
    for (Comparable& v : a)
      insert(v);
  }

  // Operations
  void insert(Comparable& v) { heap.push_back(v); swim(++N); }
  const Comparable& max() const { return heap[1]; }
  Comparable delMax() {
    Comparable max = heap[1];
    exch(1, N--); // put the max at the end
    heap.erase(--(heap.end()));
    sink(1); // re-heapify
    return max;
  }
  bool isEmpty() const { return N == 0; }
  std::size_t size() const { return N; }

private:

  Container heap{Comparable()}; // heap[0] is not used.
  size_type N = 0; // index of last valid element = number of valid elements

  // implementation helpers
  bool less(size_type i, size_type j) const { return heap[i] < heap[j]; }
  void exch(size_type i, size_type j) {
    Comparable tmp = heap[i]; heap[i] = heap[j]; heap[j] = tmp; }
  void swim(size_type k) { // let heap[k] to swim up to right position
    while (k > 1 && less(k/2, k)) {
      exch(k/2, k); // exchange with parent
      k = k/2;
    }
  } // end swim
  void sink(size_type k) { // let heap[k] to sink down to right position
    while (2 * k <= N) {
      size_type j = 2 * k;  // index of left-child
      if (j < N && less(j, j+1)) j++; // choose right-child if it is larger
      if (!less(k, j)) break; // end of sink : both children are smaller
      exch(k, j);
      k = j;
    }
  } // end sink

};

} // namespace algs

#endif
