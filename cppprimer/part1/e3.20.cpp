// Exercise 3.20 (p105)
// read and process a vector of integers.

#include <vector>
#include <iostream>

using namespace std;

int main() {
  // read integers
  int x;
  vector<int> v;
  while(cin >> x)
    v.push_back(x);

  // print the original numbers
  cout << "the origin: ";
  for (int x : v)
    cout << x << " ";
  cout << endl;

  // print the first require result
  for (int i = 0; i < v.size() - 1; i+=2)
    cout << v[i] + v[i+1] << " ";
  cout << endl;

  // print the second require result
  auto s = v.size();
  for (int i = 0; i < (s + 1) / 2; ++i)  // include the middle when s is odd
    cout << v[i] + v[s-1-i] << " ";
  cout << endl;

  return 0;
}
