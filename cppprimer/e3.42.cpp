// Exercise 3.42 (p126)
// copy a vector into a array

#include <vector>
#include <iostream>

using namespace std;

int main() {
  vector<int> v = {1, 2, 4, 4, 2};
  int arr[5];

  for (int i = 0; i < begin(arr) - end(arr); ++i)
    arr[i] = v[i];

  return 0;
}
