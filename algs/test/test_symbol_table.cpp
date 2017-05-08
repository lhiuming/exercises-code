// Test symbol tables

#include <string>
#include <iostream>

#include <search/binary.hpp>

using namespace std;
using namespace algs;

int main()
{
  BinarySearchST<string, int> st;
  cout << "Created a BSST<String, int>." << endl;

  st.put("Jason", 0);
  st.put("Rich", 9);
  st.put("Miku", -3);
  cout << "Put things in st: " << endl;
  cout << st << endl;

  return 0;
}
