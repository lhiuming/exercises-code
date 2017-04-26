#ifndef ALGS_HEAPSORT_H
#define ALGS_HEAPSORT_H

#include <vector>
#include <ostream>
#include <string>

/*
 * Priority Queue, and Heapsort.
 * TODO: implement Heapsort with MaxPQ.
 */


namespace algs {

// Priority Queue /////////////////////////////////////////////////////////////
// Currently using only std::vector as contatiner.
// TODO: support C++11 move

// Bass PQ
template<typename Comparable>
class PQ {

public:

  typedef typename std::vector<Comparable> Container;
  typedef typename Container::size_type size_type;

  // Constructor
  PQ() {};
  PQ(size_type cap) { // with initial capacity
    heap.reserve(cap+1); }
  PQ(Container& a) { // with a container of elements
    heap.reserve(a.size() + 1);
    for (Comparable& v : a)
      insert(v);
  }

  // Operations
  void insert(Comparable& v) { heap.push_back(v); swim(++N); }
  void insert(Comparable&& v) { heap.push_back(v); swim(++N); }
  const Comparable& max() const { return heap[1]; }
  Comparable delMax() {
    Comparable max = std::move(heap[1]);
    exch(1, N--); // put the max at the end
    heap.erase(--(heap.end())); // delete the old max (shrink size)
    sink(1); // re-heapify
    return max;
  }
  bool isEmpty() const { return N == 0; }
  std::size_t size() const { return N; }

  // print
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

  Container heap{Comparable()}; // heap[0] is not used.
  size_type N = 0; // index of last valid element = number of valid elements

  // implementation helpers
  virtual bool less(size_type i, size_type j) const = 0;
  virtual std::string name() const = 0; // return "MaxPQ" or "MinPQ"
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


// Max Priority Queue
template<typename Comparable>
class MaxPQ : public PQ<Comparable> {

  using typename PQ<Comparable>::size_type;
  using typename PQ<Comparable>::Container;

  // Define pure virtual members
  virtual bool less(size_type i, size_type j) const override {
    return this->heap[i] < this->heap[j]; }
  virtual std::string name() const override { return "MaxPQ"; }

public:

  // Constructors
  MaxPQ() {};
  MaxPQ(size_type cap) { // with initial capacity
    this->heap.reserve(cap+1); }
  MaxPQ(Container& a) { // with a container of elements
    this->heap.reserve(a.size() + 1);
    for (Comparable& v : a)
      this->insert(v);
  }

};


// Min Priority Queue
template<typename Comparable>
class MinPQ : public PQ<Comparable> {

  using typename PQ<Comparable>::size_type;
  using typename PQ<Comparable>::Container;

  // Define pure virtual members
  virtual bool less(size_type i, size_type j) const override {
    return this->heap[i] > this->heap[j]; }
  virtual std::string name() const override { return "MinPQ"; }

public:

  // Constructors
  MinPQ() {};
  MinPQ(size_type cap) { // with initial capacity
    this->heap.reserve(cap+1); }
  MinPQ(Container& a) { // with a container of elements
    this->heap.reserve(a.size() + 1);
    for (Comparable& v : a)
      this->insert(v);
  }

};

} // namespace algs

#endif
