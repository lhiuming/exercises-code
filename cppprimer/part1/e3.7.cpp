// Exercise 3.7 (p96)
// a variation of 3.6

#include <string>
#include <iostream>

using namespace std;

int main() {
  string a;
  cin >> a;
  for (char &c : a)
    c = 'X';
  cout << a << endl;
  return 0;
}
