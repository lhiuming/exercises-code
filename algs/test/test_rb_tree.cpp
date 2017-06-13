// Test rb_tree.hpp
#include <symbol_tables/rb_tree.hpp>

#include <iostream>
#include <string>

using namespace std;
using namespace algs;

int main()
{
  RedBlackBST<string, int> bst;
  cout << bst << endl;

  return 0;
}
