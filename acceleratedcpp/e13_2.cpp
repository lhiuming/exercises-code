#include "CoreGrad.h"
#include <iostream>

using std::cout; using std::endl;

int main()
{
  Core* p1 = new Core;
  Core* p2 = new Grad;
  Core s1;
  Grad s2;

  p1->grade();
  p1->name();
  cout << endl;

  p2->grade();
  p2->name();
  cout << endl;

  s1.grade();
  s1.name();
  cout << endl;

  s2.name();
  s2.grade();

  return 0;
}
