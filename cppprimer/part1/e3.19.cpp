// Exercise 3.19 (p105)
// three ways to initialize/give a vector with ten element of 42

#include <vector>
#include <iostream>

using namespace std;

void printInts(vector<int> &v) {
  for (int x : v)
    cout << x << " ";
  cout << endl;
}

int main() {
  // the first way, which I prefer, due to simplicity as well as efficiency
  vector<int> a(10, 42);
  // the second way; combersome
  vector<int> b{42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
  // the third way; combersome and possibly inefficient
  vector<int> c;
  for(int i = 0; i < 10; ++i) c.push_back(42);

  // check the result
  printInts(a);
  printInts(b);
  printInts(c);

  return 0;
}
