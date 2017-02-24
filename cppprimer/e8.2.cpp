// Exercise 8.2 (p314)
// using the function in e8.1.hpp

#include "e8.1.hpp"
#include <iostream>

using namespace std;

int main() {
  istream &a = printFile(cin);
  cout << "- - - First read finished. - - -" << endl;

  printFile(a);
  cout << "- - - Second read finished. - - -" << endl;
  return 0;
}
