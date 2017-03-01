// Exercise 13.13 (p504)
// Studying copy constructors and destructors

#include <iostream>

using namespace std;

struct X {
  X() { cout << "X(): X constructed." << endl; }
  X(const X &) { cout << "X(const X&): X copy-constructed." << endl; }

  ~X() { cout << "~X(): X destroyed." << endl; }
}; // end class

X func(X x) { return x; }

X &func_r(X &x) { return x; }

int main() {
  // creating
  cout << "> should be a contruction and a copy construction: " << endl;
  X a;
  X b(a);

  // copy calling
  cout << "> should be two copy constructions and two destructions: " << endl;
  func(a);

  // reference calling
  cout << "> should be nothing. " << endl;
  func_r(b);

  // end of main
  cout << "> should be two destructions: " << endl;
  return 0;
}
