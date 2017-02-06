#ifndef GUARD_String_list_h
#define GUARD_String_list_h

struct node {
  std::string item;
  node *prev;
  node *next;
}; // expected ';' after struct!!!

class String_list {
public:
  String_list();
  String_list(int, char**);

  int size() { return n; }
  int empty() { return n == 0; }
  node* push_back(std::string);

  class iterator {
  public:
    iterator(node* p) { current = p; }

    std::string operator*() { return current->item; }
    void operator++(int n) { current = current->next; } // n ignored
    void operator--(int n) { current = current->prev; } // n ignored
    bool operator==(const iterator p) { return current == p.current; }
    bool operator!=(const iterator p) { return current != p.current; }
  private:
    node *current;
  };

  iterator begin() { return iterator(first_p); }
  iterator end() { return iterator(last_p->next); }

private:
  node *first_p, *last_p;
  int n; // don't use size: confused with size() member function
}; // expected ';' after class!!!


#endif
