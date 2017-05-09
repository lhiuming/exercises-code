#ifndef ALGS_COLLECTIONS_LIST_HPP
#define ALGS_COLLECTIONS_LIST_HPP

#include <cstddef> // std::size_t
#include <ostream> // for self-printing

/*
 * list.hpp
 * (Linked-)List. Would be used for Bag, Queue, Stack and others (like
 * Symbol Table. )
 *
 * TODO: test const_iterator
 * TODO: support STL iterator_traits template
 * TODO: try to make the collection class meeting STL Container requirement.
 */

namespace algs {

// List ///////////////////////////////////////////////////////////////////////
// Singly-linked list. The interface basically mimics std::forward_list
// (only partially implemented)
////

template<class Item>
class List {

  // node class
  struct Node {
    Item item;
    Node* next;
  };

  // iterator class
  class ForwardIt {
  public:
    friend List;
    ForwardIt() {};
    ForwardIt(Node* pn) : pNode(pn) {};
    void operator++() { pNode = pNode->next; }
    Item& operator*() const { return pNode->item; }
    bool operator==(const ForwardIt& rhs) const {
      return this->pNode == rhs.pNode; }
    bool operator!=(const ForwardIt& rhs) const {
      return !(*this == rhs); }
  protected:
    Node* pNode = nullptr;
  };

  // const iterator
  class ConstForwardIt : public ForwardIt {
  public:
    friend List;
    ConstForwardIt() {};
    using ForwardIt::ForwardIt;
    const Node& operator*() const { return *(this->pNode); }
  };

public:

  using size_type = std::size_t;
  using iterator = ForwardIt;
  using const_iterator = ConstForwardIt;

  // Default constructor
  List() {}

  // Destructor
  ~List() { // destroy all nodes
    Node* head = front;
    while (head != nullptr) {
      Node* tobe_delete = head;
      head = head->next; // head pointer to next node
      delete tobe_delete;
    }
  } // end ~List

  // Copy constrols : forbidden
  List(const List&) = delete; // not support
  List(List&&) = delete; // not support
  List& operator=(const List& rhs) = delete; // not support
  List& operator=(List&& rhs) = delete; // not support

  // Iterator
  ForwardIt begin() const { return ForwardIt(front); }
  ForwardIt end() const { return ForwardIt(nullptr); }

  // capacity
  bool empty() const { return N == 0; }
  size_type size() const { return N; }

  // modifier
  void push_front(const Item& item) { push_front(Item(item)); }
  void push_front(Item&& item) { // push before the first element
    if (front == nullptr) make_first(std::move(item));
    else front = new Node{item, front};
    ++N;
  }
  void push_back(const Item& item) { push_back(Item(item)); }
  void push_back(Item&& item) { // push after the last element
    if (front == nullptr) make_first(std::move(item));
    else { back->next = new Node{item, nullptr};
           back = back->next; }
    ++N;
  }
  void insert_after(const ForwardIt& pos, const Item& item) {
    insert_after(pos, Item(item)); }
  void insert_after(const ForwardIt& pos, Item&& item) {
    // insert an item after position. pos must not equal to this->end().
    Node * const current = pos.pNode;
    Node* new_p = new Node{item, current->next};
    current->next = new_p;
    ++N;
  }
  Item pop_front() { // remove and return the first element
    // assume not empty
    Node* old_front = front;
    Item ret = std::move(old_front->item);
    front = old_front->next;
    delete front;
    return ret;
  }
  void erase_after(const ForwardIt& pos) { //remove a element after pos
    // assume pos is not equal to this->end()
    Node* const current = pos.pNode;
    Node* tobe_delete = current->next;
    current->next = tobe_delete->next;
    delete tobe_delete;
  }

  // self-priting
  friend std::ostream& operator<<(std::ostream& os, const List& list) {
    os << "List(" << list.size() << ")[";
    Node* head = list.front;
    while(head != nullptr) {
      os << head->item;
      if ( (head = head->next) != nullptr ) os << ", ";
    }
    os << "]";
    return os;
  }

private:

  Node* front = nullptr;
  Node* back = nullptr;
  size_type N = 0;

  // Implementation Helpers
  void make_first(Item&& item) {
    front = new Node{item, nullptr};
    back = front;
  }

};

} // namespace algs

#endif
