// Exercise 3.6 (p96)
// replace the chars of a string

#include <string>
#include <iostream>

using namespace std;

int main() {
  string a;
  cin >> a;
  for (auto &c : a)
    c = 'X';
  cout << a << endl;
  return 0;
}
