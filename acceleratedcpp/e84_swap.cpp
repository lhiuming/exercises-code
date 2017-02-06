#include <iostream>
#include <string>
#include <vector>
#include "split.h"

using std::cout; using std::cin; using std::endl;
using std::string; using std::vector;

template<class V>
void swap(V& a, V& b)
{
  V tmp = *a;
  *a = *b;
  *b = tmp;
}

template<class Bi> void m_reverse(Bi begin, Bi end)
{
  while (begin != end) {
    --end;
    if (begin != end)
      swap(*begin++, *end);
  }
}

int main()
{
  vector<string> input;
  vector<string>::iterator it;

  string c;
  while (getline(cin, c)) {
    input = split(c);

    for (it = input.begin(); it != input.end(); it++)
      cout << *it << ' ';
    cout << endl;

    m_reverse(input.begin(), input.end());

    for (it = input.begin(); it != input.end(); it++)
      cout << *it << ' ';
    cout << endl;
  }
  return 0;
}
