#include <iostream>
#include <string>
#include <algorithm>

using std::string;
using std::ostream_iterator;
using std::cout; using std::cin;

bool space(const char s)
{ return s == ' '; }
bool not_space(const char s)
{ return !space(s); }

template <class Out> void split(const string& str, Out os)
{
  typedef string::const_iterator iter;

  iter i = str.begin();
  while (i != str.end()) {
    i = find_if(i, str.end(), not_space);

  iter j = find_if(i, str.end(), space);
  if (i != str.end())
    *os++ = string(i, j);

  i = j;
  }
}

int main()
{
  string s;
  while (getline(cin, s))
    split(s, ostream_iterator<string>(cout, "\n"));
  return 0;
}
