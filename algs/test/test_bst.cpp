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

  cout << "-- Trying to insert -- " << endl;
  st.insert(0, heroin);
  st.insert(1, "Steve");
  st.insert(-9, "Jason");
  st.insert(8, "Jess");
  st.insert(-2, "Mye");
  st.insert(-2, "Maye");
  cout << "Things in bst: ";
  cout << st << endl;

  cout << "get(0 : Miku) = " << (*(st.find(0))).second << endl;

  cout << "-- try iterating -- " << endl;
  int count = 0;
  for (auto& kvp : static_cast<const decltype(st)>(st)) {
    ++count;
    cout << count << " : (" << kvp.first << ", " << kvp.second << ")" << endl;
    //kvp.second = "Smith"; // change is forbidden
  }

  cout << "-- Test look-ups -- " << endl;
  cout << "Is 99 inside?: " << st.contains(99) << endl;
  cout << "Is -9 inside?: " << st.contains(-9) << endl;
  cout << "floor of -8 (should be -9): " << st.floor(-8)->first << endl;
  cout << "floor of -9 (should be -9): " << st.floor(-9)->first << endl;
  cout << "ceili of  0 (should be 0): " << st.ceiling(0)->first << endl;
  cout << "ceili of -1 (should be 0): " << st.ceiling(-1)->first << endl;
  cout << "erase -2 : Mye = " << st.erase(-2) << endl;
  cout << "now bst = " << st << endl;

  //cout << "containt(Miku) : " << st.contains("Miku") << endl;

  return 0;
}
