// Exercise 16.2 (p658)
// test the compare template function

template <typename T>
int compare(T v1, T v2)
{
  if (v1 < v2) return -1;
  if (v2 < v1) return  1;
  return 0;
}

// test the result
#include <iostream>
#include <string>
using namespace std;
int main() {
  cout << "compare(1, 2): " << compare(1, 2) << endl;

  string s1("Alice"), s2("Barubatosu");
  cout << "compare(string Alice, string Barubatosu): " << compare(s1, s2) << endl;

  return 0;
}
