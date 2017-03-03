// Exercise 14.33 (p572)
// how many operands can a overloaded function-call operator take ?
// In order to prevent confusion with construction, at least one;
// to prevent confusion with conversion, at least two?


#include<iostream>

using namespace std;

class Func {
public:
  void operator() (int i, int j, int k, int l, int m) {
    cout << i << j << k << l << m << endl;
  }
};

int main()
{
  Func f;
  f(1, 2, 3, 4, 5);
  return 0;
}
