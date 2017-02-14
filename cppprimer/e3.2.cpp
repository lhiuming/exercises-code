// Exercise 3.2 (p90)
// write progarm read the std input a line/word a time

#include <iostream>
#include <string>

using namespace std;

void readLine(string &a) {
  getline(cin, a);
}

void readWord(string &a) {
  cin >> a;
}

int main() {
  string a;
  readWord(a);
  while (!a.empty()) {
    cout << "I read: " << a << endl;
    readWord(a);
  }

  return 0;
}
