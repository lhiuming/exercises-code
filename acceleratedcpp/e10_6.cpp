#include <iostream>
#include <string>
#include <vector>

#include "e10_4_String_list.h"

using std::cout;
using std::cin;
using std::endl;

using std::string;
using std::vector;


String_list split(const string& s)
{
  String_list ret;
  typedef string::size_type string_size;
  string_size i = 0;

  while (i != s.size()) {
    while (i != s.size() && isspace(s[i]))
      ++i;

    string_size j = i;
    while (j != s.size() && !isspace(s[j]))
      j++;

    if (i != j) {
      ret.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return ret;
}


int main(int argc, char** argv)
{
  String_list sl(argc-1, argv+1);

  for (String_list::iterator it = sl.begin(); it != sl.end(); it++)
    cout << *it << endl;

  cout << sl.size() << endl;

  string r;
  while (getline(cin, r)) {
    sl = split(r);
    for (String_list::iterator it = sl.begin(); it != sl.end(); it++)
      cout << *it << endl;
  }
  return 0;
}
