// Excercise 5.24 (p198)
// Throw exceptions

#include <iostream>
#include <exception> // exception
#include <stdexcept> // runtime_error ...

using namespace std;

int main()
{
  int d, n;
  cin >> n >> d;
  if (d == 0) throw runtime_error("Devide by zero !");
  cout << d << "/" << n << " = " << d / d << endl;

  return 0;
}
