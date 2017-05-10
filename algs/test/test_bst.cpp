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

  st.insert(0, heroin);
  //st.put(1, "Steve");
  //st.put(-9, "Jason");
  //st.put(-2, "Mye");
  cout << "Put things in bst: " << endl;
  cout << st << endl;

  //cout << "get(Miku) = " << st.get("Miku") << endl;
  //cout << "get(nana) = " << st.get("nana") << endl;

  //cout << "pop(Rich) = " << st.pop("Rich") << endl;
  //cout << "now st = " << st << endl;

  //cout << "containt(Miku) : " << st.contains("Miku") << endl;

  return 0;
}
