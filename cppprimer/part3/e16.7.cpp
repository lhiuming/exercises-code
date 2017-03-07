// Exercise 16.7 (p658)
// return size of an array

template <typename V, unsigned N>
constexpr unsigned arraysize(V (&arr)[N]) { return N; }

#include <iostream>

using namespace std;

int main() {
  char a[34];
  const unsigned n = arraysize(a);

  cout << "array size is " << n << endl;

  return 0;
}
