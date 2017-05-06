#ifndef ALGS_HEAPSORT_H
#define ALGS_HEAPSORT_H

#include <vector>
#include <ostream>
#include <string>

/*
 * Priority Queue, and Heapsort.
 * TODO: implement Heapsort.
 */


namespace algs {

// Priority Queue /////////////////////////////////////////////////////////////
// Currently using only std::vector as contatiner.
// Comparable should supports operator> (for MaxPQ ) or operator< (for MinPQ)

// Priority Queue base class
template<typename Comparable>
class PQ {

public:

  using Container = typename std::vector<Comparable>;
  using size_type = typename Container::size_type;

  // Default constructor
  PQ() {};
  // Initialized with given capacity
  PQ(size_type cap) { heap.reserve(cap + 1); }

  // Copy a element into the queue
  void insert(const Comparable& v) { heap.push_back(v); swim(++N); }
  // Move a element into the queue
  void insert(Comparable&& v) { heap.push_back(v); swim(++N); }

  // Return a direct reference to the most prior element
  const Comparable& head() const { return heap[1]; }
  // Return and delete the most prior element
  Comparable pop() {
    Comparable head = std::move(heap[1]); // take the most prior element
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

  // data member
  Container heap{Comparable()}; // heap[0] is not used.
  size_type N = 0; // index of last valid element = number of valid elements

  // pure virtuals; used to make MaxPQ and MinPQ from PQ
  virtual bool prior(size_type i, size_type j) const = 0;
  virtual std::string name() const = 0; // return "MaxPQ" or "MinPQ"

  // implementation helpers
  void exch(size_type i, size_type j) {
    Comparable temp = heap[i];
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


// Max Priority Queue
template<typename Comparable>
class MaxPQ : public PQ<Comparable> {

  using typename PQ<Comparable>::size_type;  // necessary: parent class
  using typename PQ<Comparable>::Container;  // is not instantiated yet.

  // Define pure virtual members
  virtual bool prior(size_type i, size_type j) const override {
    return this->heap[i] > this->heap[j]; }
  virtual std::string name() const override { return "MaxPQ"; }

public:

  // Default constructor; delegated
  MaxPQ() = default;

  // Inheritate the base class constructors
  using PQ<Comparable>::PQ;
  // Copy the given elements
  MaxPQ(Container& a) : PQ<Comparable>(a.size() + 1) {
    for (Comparable& v : a) this->insert(v); }

};


// Min Priority Queue
template<typename Comparable>
class MinPQ : public PQ<Comparable> {

  using typename PQ<Comparable>::size_type;
  using typename PQ<Comparable>::Container;

  // Define pure virtual members
  virtual bool prior(size_type i, size_type j) const override {
    return this->heap[i] < this->heap[j]; }
  virtual std::string name() const override { return "MinPQ"; }

public:

  // Default constructor
  MinPQ() = default;

  // Inheritate the base class constructors
  using PQ<Comparable>::PQ;
  // Copy the given elements
  MinPQ(Container& a) : PQ<Comparable>(a.size() + 1) {
    for (Comparable& v : a) this->insert(v); }

};

} // namespace algs

#endif
