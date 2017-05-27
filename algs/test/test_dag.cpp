// test dag.hpp

#include <iostream>

#include <graphs/digraph.hpp>
#include <graphs/dag.hpp>

using namespace std;
using namespace algs;

int main()
{
  Digraph dig(cin);
  auto result = depth_first_order(dig);
  cout << "pre is : " << result.pre() << endl;
  cout << "Topological sort is : " << topological_order(dig) << endl;


  return 0;
}
