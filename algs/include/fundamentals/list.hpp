#ifndef ALGS_FUNDAMENTALS_LIST_HPP
#define ALGS_FUNDAMENTALS_LIST_HPP

#include <cstddef> // std::size_t
#include <ostream> // for self-printing
#include <iterator> // std::iterator_traits
#include <cstddef> // std::ptrdiff_t
#include <limits> // for max_size()

/*
 * list.hpp
 * Singly linked-list, with interface similar to std::forward_list.
 *
 * TODO: add allocator support, full construtors, and full copy controls
 * TODO: try to make the collection class meeting STL Container requirement.
 * TODO: add complete noexcept support
 */

namespace algs {

// The List class
template<class Item>
class List {

  // Private node class
  struct Node {
    Item item;
    Node* next;
  };

public:

  // Iterator Classes /////////////////////////////////////////////////////////

  // Non-const iterator class
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

  // Const iterator class
  class ConstForwardIt : public ForwardIt {
  public:
    friend List;

    // new alias
    using reference = const typename ForwardIt::value_type&;
    using pointer = typename ForwardIt::value_type* const;

    ConstForwardIt() {}
    ConstForwardIt(Node* pn) : ForwardIt(pn) {}
    ConstForwardIt(const ForwardIt& b) : ForwardIt(b) {}

    // replace the dereferencing operator by a const one
    reference operator*() const { return ForwardIt::operator*(); }
    pointer operator->() const { return ForwardIt::operator->(); }
  };


  // Member types /////////////////////////////////////////////////////////////

  using value_type       = Item;
  //using allocator_type Allocator
  using size_type	       = std::size_t;
  using difference_type	 = std::ptrdiff_t;
  using reference	       = value_type&;
  using const_reference  = const value_type&;
  //using pointer	= std::allocator_traits<Allocator>::pointer
  using pointer           = Item*;
  //using const_pointer	= std::allocator_traits<Allocator>::const_pointer
  using const_pointer    = Item* const;
  using iterator         = ForwardIt;
  using const_iterator   = ConstForwardIt;


  // Member functions /////////////////////////////////////////////////////////

  // Constructors //
  // TODO: add full family of constructors

  // Default constructors
  List() = default;

  // Copy constrols (very limited) //

  // Copy (deep)
  List(const List& other) {
    if (other.empty()) return;
    // make the first node
    const_iterator other_head = other.begin();
    this->pfront = new Node{*other_head++, nullptr};
    // insert other nodes by iteration
    iterator my_head = this->begin();
    while (other_head != other.end())
      my_head = insert_after(my_head, *other_head++);
  }

  // Move (take pointer)
  List(List&& other) { this->pfront = other.pfront; other.pfront = nullptr; }

  List& operator=(const List&) = delete; // not support
  List& operator=(List&&) = delete; // not support

  ~List() { clear(); } // everything else is automatic

  // Assign //
  // TODO
  void assign() {}

  // Get allocator //
  // TODO
  void get_allocator() {}

  // Element access //
  reference front() { return pfront->item; }
  const_reference front() const { return pfront->item; }


  // Iterators //

  // TODO
  void before_begin() {}
  void cbefore_begin() {}

  // Iterator to the first item
  iterator begin() noexcept { return ForwardIt(pfront); }
  const_iterator begin() const noexcept { return cbegin(); }
  const_iterator cbegin() const noexcept { return ConstForwardIt(pfront); }

  // Iterator pass the end
  iterator end() noexcept { return ForwardIt(nullptr); }
  const_iterator end() const noexcept { return cend(); }
  const_iterator cend() const noexcept { return ConstForwardIt(nullptr); }

  // Capacity //

  // Empty check
  bool empty() const noexcept { return pfront == nullptr; }

  // Max possible list length
  size_type max_size() const noexcept { // kind of useless ...
    return std::numeric_limits<size_type>::max(); }

  // Modifier //

  // Remove all nodes
  void clear() noexcept {
    Node* phead = pfront;
    while (phead != nullptr) {
      Node* tobe_delete = phead;
      phead = phead->next; // head pointer to next node
      delete tobe_delete;
    }
  }

  // Insert after given position or range (iteartor or index)
  iterator insert_after(const_iterator pos, const Item& item) {
    return insert_after(pos, Item(item)); }
  iterator insert_after(const_iterator pos, Item&& item) {
    // pos must not equal to this->end().
    Node * const current = pos.pNode;
    Node* new_p = new Node{item, current->next};
    current->next = new_p;
    return iterator(new_p);
  }
  // TODO : other inserters
  iterator insert_after( const_iterator pos, size_type count, const Item& item);
  template<class InputIt> iterator insert_after( const_iterator pos, InputIt first, InputIt last );
  iterator insert_after( const_iterator pos, std::initializer_list<Item> ilist );

  // Emplace after given position (iterator)
  // TODO
  template< class... Args > iterator emplace_after( const_iterator pos, Args&&... args );

  // Erase after given position or range (iterator)
  iterator erase_after(const_iterator pos) {
    Node* const current = pos.pNode;
    Node* tobe_delete = current->next;
    current->next = tobe_delete->next;
    delete tobe_delete;
    return iterator(current->next); // would be end() if next is nullptr
  }
  // TODO
  iterator erase_after(const_iterator first, const_iterator last) {
    // first is not removed
    while (first != last) first = erase_after(first);
    return first; // == last
  }

  // Push at the front
  void push_front(const Item& item) { push_front(Item(item)); }
  void push_front(Item&& item) { // push before the first element
    if (pfront == nullptr) pfront = new Node{std::move(item), nullptr};
    else pfront = new Node{item, pfront};
  }

  // Emplace at the front (NOTE: using C++17 version)
  // TODO
  template< class... Args > reference emplace_front( Args&&... args );

  // Pop front ( NOTE: std::forwad_list version returns void )
  Item pop_front() {
    // assume not empty
    Node* old_front = pfront;
    Item ret = std::move(old_front->item);
    pfront = old_front->next;
    delete old_front;
    return ret;
  }

  // Resize
  // TODO
  void resize( size_type count );
  void resize( size_type count, const Item& item );

  // Swap content ( NOTE: using C++17 version)
  void swap(List& other) noexcept {
    std::swap(this->pfront, other.pfront); }

  // Other operations //

  // Merge two lists (assuem both *this and other are sorted)
  // TODO
  void merge(List& other) {
    this->merge(List(other)); }
  void merge(List&& other) {
    this->merge(other, std::less<value_type>()); }
  template <class Compare> void merge(List& other, Compare less) {
    this->merge(List(other), less); }
  template <class Compare> void merge(List&& other, Compare less) {
    // no copy or move; just reconnect nodes
    // Trivial cases
    if (other.empty()) return;
    if (this->empty()) { this->swap(other); return; }
    // Both non-empty : make a empth head, then alternating insert
    Node* in1 = this->pfront;
    Node* in2 = other.pfront;
    // choose the new pfront (the first node)
    if (less(in2->item, in1->item)) {
      this->pfront = in2;
      in2 = in2->next;
    } else {
      this->pfront = in1;
      in1 = in1->next;
    }
    // insert the rest
    Node* out = this->pfront;
    while ( (in1 != nullptr) && (in2 != nullptr) ) {
      if (less(in2->item, in1->item)) {
        out->next = in2;
        in2 = in2->next;
      } else {
        out->next = in1;
        in1 = in1->next;
      }
      out = out->next;
    } // end while
    if (in1 != nullptr) { out->next = in1; }
    if (in2 != nullptr) { out->next = in2; }
    other.pfront = nullptr; // prevent node destruction
  }

  // Splice with another list
  // TODO
  void splice_after( const_iterator pos, List& other );
  void splice_after( const_iterator pos, List&& other );
  void splice_after( const_iterator pos, List& other, const_iterator it );
  void splice_after( const_iterator pos, List&& other, const_iterator it );
  void splice_after( const_iterator pos, List& other, const_iterator first, const_iterator last );
  void splice_after( const_iterator pos, List&& other, const_iterator first, const_iterator last );

  // Remove elements from list
  // TODO
  void remove( const Item& item );
  template< class UnaryPredicate > void remove_if( UnaryPredicate p );

  // Reverse order of list
  // TODO
  void reverse() noexcept;

  // Remove consecutive duplicated items
  // TODO
  void unique();
  template< class BinaryPredicate > void unique( BinaryPredicate p );

  // Sort the list (mergesort: stable and O(NlogN))
  void sort() { this->sort(std::less<value_type>()); }
  template<class Compare> void sort(Compare less) {
    // TODO: implement by split and merg
    if ( (pfront == nullptr) || (pfront->next == nullptr) ) return;
    // split into two List
    List that = this->split();
    this->sort();
    that.sort();
    this->merge(std::move(that));
  }


  // Non-standard interfaces //////////////////////////////////////////////////

  // Printing
  friend std::ostream& operator<<(std::ostream& os, const List& list) {
    os << "List[";
    Node* head = list.pfront;
    while(head != nullptr) {
      os << head->item;
      if ( (head = head->next) != nullptr ) os << ", ";
    }
    os << "]";
    return os;
  }

private:

  Node* pfront = nullptr;

  // Implementation Helpers //

  // Private constructor : from a pointer
  List(Node* np) : pfront(np) {}

  // split this list into two half; return the second half
  // assume list has at least 2 nodes;
  List split() {
    Node* slow = pfront;
    Node* fast = pfront->next->next;
    while (fast != nullptr) {
      slow = slow->next;
      if ( (fast = fast->next) ) fast = fast->next;  // double move
    }
    List ret(slow->next);
    slow->next = nullptr; // cut the connection
    return ret;
  }

};

} // namespace algs

#endif
