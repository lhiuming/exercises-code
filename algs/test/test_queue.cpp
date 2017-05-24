// Test queue.hpp

#include <fundamentals.hpp>
#include <iostream>
#include <string>

using namespace std;
using namespace algs;

int main()
{
  Queue<string> q;
  q.push("Spenser");
  q.push("Eriri");
  q.push("Katou");
  cout << "Created q: " <<  q << endl;
  cout << "q.pop(): " << q.pop() << endl;
  cout << "Popped q: " << q << endl;

  return 0;
}
