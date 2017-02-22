// Exercise 3.11 (p96)
// remove punctuation from a string

#include <string>
#include <iostream>
#include <cctype>

using namespace std;

int main() {
  string a;
  cin >> a;
  for (auto &c : a)
    if (!ispunct(c))
      cout << c;
  cout << endl;
  return 0;
}
