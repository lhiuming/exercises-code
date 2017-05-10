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

  cout << "get(0 : Miku) = " << *(st.find(0)) << endl;
  //cout << "get(nana) = " << st.get("nana") << endl;

  //cout << "pop(Rich) = " << st.pop("Rich") << endl;
  //cout << "now st = " << st << endl;

  //cout << "containt(Miku) : " << st.contains("Miku") << endl;

  return 0;
}
