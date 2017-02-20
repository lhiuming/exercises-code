// Exercise 3.43 (p130)
// using multidimensional array

#include <iostream>
#include <cstddef>

using namespace std;

int main() {
  int ai[3][4] = {
    0, 1, 2, 3,
    4, 5, 6, 7,
    8, 9, 10, 11
  };

  // range for
  for (int (&r)[4] : ai) {
    for (int c : r)
      cout << c << ' ';
    cout << endl;
  }
  cout << "- - -" << endl;

  // subscript loop
  for (size_t i = 0; i < end(ai) - begin(ai); ++i) {
    for (size_t j = 0; j < end(ai[i]) - begin(ai[i]); ++j)
      cout << ai[i][j] << ' ';
    cout << endl;
  }
  cout << "- - -" << endl;

  // pointer loop
  for (int (*p)[4] = begin(ai); p < end(ai); ++p) {
    for (int *q = begin(*p); q < end(*p); ++q)
      cout << *q << ' ';
    cout << endl;
  }

  return 0;
}
