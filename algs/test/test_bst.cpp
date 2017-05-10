// Test binary search tree symbol tables

#include <string>
#include <iostream>

#include <symbol_tables/binary_tree.hpp>

using namespace std;
using namespace algs;

int main()
{
  BST<int, string> st;
  cout << "Created a BSST<String, int>." << endl;

  string heroin = "Miku";

  cout << "Trying to insert: " << endl;
  st.insert(0, heroin);
  st.insert(1, "Steve");
  st.insert(-9, "Jason");
  st.insert(-2, "Mye");
  cout << "Put things in bst: " << endl;
  cout << st << endl;

  cout << "get(0 : Miku) = " << (*(st.find(0))).second << endl;

  cout << "try iterating: " << endl;
  int count = 0;
  for (auto& kvp : static_cast<const decltype(st)>(st)) {
    ++count;
    cout << count << " : (" << kvp.first << ", " << kvp.second << ")" << endl;
    //kvp.second = "Smith"; // change is forbidden
  }

  //cout << "Is Rich inside?: " << st.contains("Rich") << endl;
  //cout << "Is Jason inside?: " << st.contains("Jason") << endl;

  //cout << "pop(Rich) = " << st.pop("Rich") << endl;
  //cout << "now st = " << st << endl;

  //cout << "containt(Miku) : " << st.contains("Miku") << endl;

  return 0;
}
