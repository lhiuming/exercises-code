#include <iostream>

#include "Vec.cpp"
#include "Str.h"

class Str {
    // friend methods: private prop are available to friends
    friend std::istream& operator>>(std::istream&, Str&);
public:
  typedef Vec<char>::size_type size_type;

  // constructor
  Str() {}; // empty constructor
  Str(size_type n, char c): data(n, c) {}; // n copy construction
  Str(const char* cp) {
    std::copy(cp, cp + std::strlen(cp), std::back_inserter(data));
  } // construction from array of char
  template<class In> Std(In b, In e) {
    std::copy(b, e, std::back_inserter(data));
  } // construction from any iterator

  // overloaded operators
  char& operator[](size_type i) { return data[i]; }
  const char& operator[](size_type i) const { return data[i]; }
  Str& operator+=(const Str& s) {
    std::copy(s.data.begin(), s.data.end(), std::back_inserter(data));
    return *this;
  }

  // operations
  size_type size() const { return data.size(); }

private:
  Vec<char> data;
}

// non-member overloaded operators
std::istream& operator>>(std::istream&, Str&);
std::ostream& operator<<(std::ostream&, const Str&);
Str operator+(const Str&, const Str&);
