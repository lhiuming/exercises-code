// Exercise 6.37 (p230)
// more practice on writing function return types
// also see e6.36.h

#include "e6.36.h" // test whether all declaration agree
#include <string>
#include <iostream>

using namespace std;

string s1[10] = {"a"};
string s2[10] = {"y"};

// definition
string (&func(int i))[10] {
  if (i == 1)
    return s1;
  return s2;
}


// alternative declarations
// 1. using type alias
using stringArrRef = string (&) [10];
stringArrRef func(int);
// 2. using trailing return
auto func(int) -> string (&) [10];

int main() {
  func(1)[2] = "b";
  cout << func(1)[0] << endl;
  cout << func(99)[0] << endl;
  cout << func(1)[2] << endl;
  return 0;
}
