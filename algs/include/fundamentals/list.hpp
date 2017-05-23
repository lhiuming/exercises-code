#ifndef ALGS_FUNDAMENTALS_LIST_HPP
#define ALGS_FUNDAMENTALS_LIST_HPP

#include <cstddef> // std::size_t
#include <ostream> // for self-printing
#include <iterator> // std::iterator_traits
#include <cstddef> // std::ptrdiff_t

/*
 * list.hpp
 * Singly linked-list, with interface similar to std::forward_list.
 *
 * TODO: add allocator support
 * TODO: try to make the collection class meeting STL Container requirement.
 * TODO: add complete noexcept support
 */

namespace algs {

template<class Item>
class List {

  // private node class
  struct Node {
    Item item;
    Node* next;
  };

public:

  // iterator class
  class ForwardIt {
  public:
    friend List;

    // type alias (traits support)
    using difference_type	  = std::ptrdiff_t;
    using value_type        = Item;
    using pointer           = value_type*;
    using reference	        = value_type&;
    using iterator_category = std::forward_iterator_tag;

    // Constructors (using default copy controls)
    ForwardIt() : pNode(nullptr) {} // singular iterator requirement
    ForwardIt(Node* pn) : pNode(pn) {}

    // Forward iterator operations //

    // equality comparable
    bool operator!=(const ForwardIt& rhs) const {
      return this->pNode != rhs.pNode; }
    bool operator==(const ForwardIt& rhs) const {
      return this->pNode == rhs.pNode; }

    // deferenceable
    reference operator*() const { return pNode->item; }
    pointer operator->() const { return &(pNode->item); }

    // increaseable
    ForwardIt& operator++() { pNode = pNode->next; return *this; }
    ForwardIt operator++(int) { ForwardIt ret(*this);
      this->operator++(); return ret; }

  protected:
    Node* pNode;

  };

  // const iterator class
  class ConstForwardIt : public ForwardIt {
  public:
    friend List;

    // new alias
    using reference = const typename ForwardIt::value_type&;
    using pointer = typename ForwardIt::value_type* const;

    ConstForwardIt() {};
    ConstForwardIt(Node* pn) : ForwardIt(pn) {};

    // replace the dereferencing operator by a const one
    reference operator*() const { return ForwardIt::operator*(); }
    pointer operator->() const { return ForwardIt::operator->(); }
  };

  // type alias
  using size_type = std::size_t;
  using iterator = ForwardIt;
  using const_iterator = ConstForwardIt;

  // Default constructor
  List() = default;

  // Copy constrols (very limited) //

  List(const List&) = delete; // not support
  List(List&&) = delete; // not support

  List& operator=(const List&) = delete; // not support
  List& operator=(List&&) = delete; // not support

  ~List() { // destroy all nodes
    Node* head = front;
    while (head != nullptr) {
      Node* tobe_delete = head;
      head = head->next; // head pointer to next node
      delete tobe_delete;
    }
  } // end ~List

  // Assign //
  // TODO
  void assign() {}

  // Get allocator //
  // TODO
  void get_allocator() {}

  // Element access //



  // Iterator //

  // TODO
  void before_begin() {}
  void cbefore_begin() {}

  iterator begin() noexcept { return ForwardIt(front); }
  const_iterator begin() const noexcept { return cbegin(); }
  const_iterator cbegin() const noexcept { return ConstForwardIt(front); }

  iterator end() noexcept { return ForwardIt(nullptr); }
  const_iterator end() const noexcept { return cend(); }
  const_iterator cend() const noexcept { return ConstForwardIt(nullptr); }

  // Capacity
  bool empty() const { return N == 0; }
  size_type size() const { return N; }

  // Modifier : inserters
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

  // Modifier : erasers
  Item pop_front() { // remove and return the first element
    // assume not empty
    Node* old_front = front;
    Item ret = std::move(old_front->item);
    front = old_front->next;
    delete old_front;
    --N;
    return ret;
  }
  void erase_after(const ForwardIt& pos) { //remove a element after pos
    // assume pos is not equal to this->end()
    Node* const current = pos.pNode;
    Node* tobe_delete = current->next;
    current->next = tobe_delete->next;
    --N;
    delete tobe_delete;
  }

  // Printing
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
