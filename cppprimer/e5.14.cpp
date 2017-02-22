// Exercise 5.14 (p185)
// looking for duplicated words in input stream

#include <string>
#include <iostream>

using namespace std;

int main()
{
  int count = 0, max_count = 0;;
  string prev = "", curr;
  while (cin >> curr) {
    if (curr == prev) // if duplicate happens
      ++count;
    else { // no duplicates; start a new counting
      prev = curr;
      count = 1;
    }

    if (count > max_count)
      max_count = count;
  }

  if (max_count > 1)
    cout << "The maximum duplicate number is " << max_count << endl;
  else
    cout << "No duplicates detected. " << endl;

  return 0;
}
