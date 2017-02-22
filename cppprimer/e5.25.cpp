// Exercise 5.25 (p198)
// practicing exceptions

#include <stdexcept>
#include <iostream>

using namespace std;

int main()
{
  int a, b;
  cin >> a >> b;
  redo: try {  // goto cannot bypass a try block 
    if (b == 0)
      throw domain_error("Denominator is zero!");
  } catch (domain_error e) {
    cout << e.what() << endl;
    cout << "Please input a new denominator: ";
    cin >> b;
    goto redo;
  }

  cout << "division of the above is: " << a / b << endl;
  return 0;
}
