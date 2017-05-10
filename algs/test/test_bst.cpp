// Test binary search tree symbol tables

#include <string>
#include <iostream>

#include <symbol_tables/binary_tree.hpp>

using namespace std;
using namespace algs;

int main()
{
  BST<string, int> st;
  cout << "Created a BSST<String, int>." << endl;

  st.put("Jason", 0);
  //st.put("Rich", 9);
  //st.put("Miku", -3);
  cout << "Put things in st: " << endl;
  cout << st << endl;

  //cout << "get(Miku) = " << st.get("Miku") << endl;
  //cout << "get(nana) = " << st.get("nana") << endl;

  //cout << "pop(Rich) = " << st.pop("Rich") << endl;
  //cout << "now st = " << st << endl;

  //cout << "containt(Miku) : " << st.contains("Miku") << endl;

  return 0;
}
