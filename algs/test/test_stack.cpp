// Test stack.hpp

#include <iostream>
#include <string>

#include <fundamentals/stack.hpp>

using namespace std;
using namespace algs;

int main()
{
  // The following test use the client in ALGS book Section 1.3.

  // Create
  Stack<string> stack;

  // Read commands and print
  string s;
  while (cin >> s)
  {
    if (s != "-") stack.push(s);
    else if (!stack.empty()) cout << stack.pop() << " ";
  }
  cout << "( " << stack.size() << " left on stack)" << endl;

  return 0;
}
