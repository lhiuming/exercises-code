// Exercise 5.19 (p190)
// practice using do while loop

#include <string>
#include <iostream>

using namespace std;

int main ()
{
  do {
    cout << "Please input two strings: ";
    string a, b;
    cin >> a >> b;
    if (a < b)
      cout << a << " is less. " << endl;
    else if (a > b)
      cout << b << " is less. " << endl;
    else
      cout << "equal. " << endl;
  } while (true);

  return 0;
}
