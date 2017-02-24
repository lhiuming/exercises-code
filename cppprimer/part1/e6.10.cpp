// Exercise 6.10 (p210)
// practicei using pointer parameters

#include <iostream>

using namespace std;

void swap(int *a, int *b)
{
  int tmp = *a;
  *a = *b;
  *b = tmp;
}

int main()
{
  int a = 1, b = 2;
  cout << "before: " << a << ", " << b << endl;
  swap(&a, &b);
  cout << "after:  " << a << ", " << b << endl;

  return 0;
}
