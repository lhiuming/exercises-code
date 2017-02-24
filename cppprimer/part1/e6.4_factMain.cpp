// Exercise 6.4 (p205)
// calling the fact(int) function defined in e6.3
// this code is used in e6.8 and e6.9

#include "e6.8_Chapter6.h"

#include <iostream>

using std::cin; using std::cout; using std::endl;

bool interactiveFact()
{
  int n;
  cout << "Input a integer argument for factorial function: ";
  if (cin >> n) {
    cout << "fact(" << n << ") = " << fact(n) << endl;
    return true;
  } else {
    cout << "Invalide input. " << endl;
    return false;
  }
}

int main() {
  while (interactiveFact())
    ;

  return 0;
}
