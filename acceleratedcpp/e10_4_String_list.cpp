#include <string>

#include "e10_4_String_list.h"

using std::string;

node* String_list::push_back(string s) {
  node *p = new node;
  p->item = s;
  if (n == 0) {
    first_p = p;
    last_p = p;
  } else {
    last_p->next = p;
    p->prev = last_p;
  }
  // move on
  last_p = p;
  ++n;
  return p;
}

String_list::String_list() {
  node* p = new node;
  first_p = p;
  last_p = p;
}

String_list::String_list(int count, char **ss) {
  String_list();
  if (count > 0) {
    for (int i = 0; i < count; i++)
      push_back(string(ss[i]));
  }
}
