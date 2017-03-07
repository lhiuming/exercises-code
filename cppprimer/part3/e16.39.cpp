// Exercise 16.39 (p683)
// use explicit template argument

template <typename T>
int compare(const T v1, const T v2)
{
  if (v1 < v2) return -1;
  if (v2 < v1) return  1;
  return 0;
}

#include <string>
#include <iostream>

using namespace std;

int main() {
  cout << "compare(literal \"Alice\", literal \"Marisa\") : "
       << compare<string>("Alice", "Marisa") << endl;

  return 0;
}
