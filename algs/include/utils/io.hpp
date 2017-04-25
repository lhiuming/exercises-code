/*
 * io.hpp
 * Provides some common input/output functions.
 */

#include <vector>
#include <istream>
#include <ostream>

namespace algs {

// Read and Print vectors

template<typename Arith>
std::istream& operator>>(std::istream& is, std::vector<Arith>& v)
{
  Arith t;
  while (is >> t) {
    v.push_back(t);
  }
  return is;
} // end operator>>

template<typename Arith>
std::ostream& operator<<(std::ostream& os, const std::vector<Arith>& v)
{
  os << "Vector[";
  if (!v.empty()) os << v[0];
  for (typename std::vector<Arith>::size_type i = 1; i < v.size(); ++i)
    os << ", " << v[i];
  os << "]";
  return os;
}

}
