#ifndef ALGS_ARRAY_H
#define ALGS_ARRAY_H

#include <cstddef>
#include <ostream>

namespace algs {

/*
 * We try to implement a Java-stype Array that can be dynamically created and
 * release the resourse automatically.
 *
 * This class is used in almost all examples and exercises, as a alternative to
 * the more (or too) flexible std::vector.
 */

template<typename T>
class Array {
public:

  // Define some usefull typenames
  typedef T value_type;
  typedef size_t size_type;

  // Constructors
  Array() = delete; // dont allow empty array
  // convert from a c-stype array
  template<size_type N>
  explicit Array(value_type (&arr)[N]) : data(arr), _size(N), allocated(false) {}
  // create an Array with size n. possibly the most useful one.
  explicit Array(size_type n) : _size(n), allocated(true) {
    data = new value_type[n]; }

  // Destructor. Basically just release allocated resources
  ~Array() { if (allocated) delete data; }

  // Get size
  size_type size() const { return _size; }

  // random access operator
  value_type& operator[](size_type i) { return data[i]; }
  const value_type& operator[](size_type i) const { return data[i]; }

private:

  value_type* data; // internal storage is a c-style array
  const size_type _size;
  const bool allocated;  // whether we own/allocated the data

  // Print the Array. You have to define it here. Wired.
  friend std::ostream& operator<<(std::ostream& os, const Array& arr){
    os << "[" << arr.data[0];
    for (size_t i = 1; i < arr._size; ++i)
      os << ", " << arr.data[i];
    os << "]";
    return os;
  }

};



} // end namespace

#endif
