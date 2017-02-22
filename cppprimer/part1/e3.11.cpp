// Exercise 3.11 (p96)
// What is the type of c?

// I think it is a reference to const char .

#include <string>
#include <iostream>
using namespace std;
int main() {
  const string s = "Keep out!";
  for (auto &c : s)
    c = '3';
  cout << s;
  return 0;
}
