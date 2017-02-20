// Exercise 3.41 (p126)
// initilaize a vector from array

#include <vector>
#include <iostream>

using namespace std;

int main() {
  int arr[] = {1, 2, 3, 3, 4};
  vector<int> v(begin(arr), end(arr));

  // print to check
  for (auto i = v.begin(); i != v.end(); i++)
    cout << *i << ' ';
  cout << endl;

  return 0;
}
