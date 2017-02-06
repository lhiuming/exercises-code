#ifndef GUARD_Str_h
#define GURAD_Str_h

#include <iostream>
#include "Str.h"

using std::istream;
using std::ostream;

// **non-member** overloaded operators: no Srs:: prefix
ostream& operator<<(ostream& os, const Str& s) // output operators
{
  for (Str::size_type i = 0; i != s.size(); ++i)
    os << s[i];
  return os;
}

istream& operator>>(istream& is, Str& s)
{
  s.data.clear();

  char c;
  while(is.get(c) && isspace(s))
    ; // skip whitespace

  if (is) {
    do s.data.push_back(c);
    while (is.get(c) && !isspace(c));
  }

  if (is)
    is.unget(); // put back the last while space
}

Str operator+(const Stf& s, const Str& t) {
  Str r = s;
  r += s;
  return r;
}

#endif
