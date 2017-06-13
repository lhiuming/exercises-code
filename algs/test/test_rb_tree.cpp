// Test rb_tree.hpp
#include <symbol_tables/rb_tree.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace algs;

int main()
{
  RedBlackBST<string, int> bst;

  cout << "-- Check insertions --" << endl;
  bst.insert("Nina", 17);
  bst.insert("Rita", 500);
  bst.insert("Mugaro", 10);
  bst.insert("Alexandra", 20);
  bst.insert("Favaro", 23);
  cout << bst << endl;

  return 0;
}
