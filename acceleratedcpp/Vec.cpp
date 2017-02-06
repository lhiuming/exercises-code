#include <memory> // allocator in here

using std::allocator;
using std::uninitialized_fill;
using std::uninitialized_copy;

template<class T> class Vec {
public:
  // types defines
  typedef T* iterator; // using pointer as iterator
  typedef const T* const_iterator;
  typedef size_t size_type;
  typedef T value_type;
  // constructors
  Vec() { create(); }
  explicit Vec(size_type n, const T& val = T()) { create(n, val); }
  // operations
  void clear() { uncreate(); }
  size_type size() const { return limit - data; }
  iterator begin() { return data; }
  const_iterator begin() const { return data; }
  iterator end() { return limit; }
  const_iterator end() const { return limit; }
  // append
  void push_back(const T& val) {
    if (avail == limit)
      grow();
    unchecked_append(val);
  }
  // overloaded operations
  T& operator[](size_type i) { return data[i]; }
  const T& operator[](size_type i) const { return data[i]; }
  Vec& operator=(const Vec&); // assign
  Vec(const Vec& v) { create(v.begin(), v.end()); } // copy
  ~Vec() { uncreate(); } // destroyter

private:
  iterator data; // first element
  iterator avail; // pointer to one past the last element
  iterator limit; // one past the last element

  // memory allocation
  allocator<T> alloc;
  void create();
  void create(size_type, const T&);
  void create(const_iterator, const_iterator);
  void uncreate();
  void grow();
  void unchecked_append(const T&);
};

// definition of the assignment opperator
template<class T>
Vec<T>& Vec<T>::operator=(const Vec& rhs)
{
  if (&rhs != this) {
    uncreate();
    create(rhs.begin(), rhs.end());
  }
  return *this;
}

// constructions

template<class T> void Vec<T>::create()
{
  data = avail = limit = 0;
}

template<class T> void Vec<T>::create(size_type n, const T& val)
{
  data = alloc.allocate(n);
  limit = avail = data + n;
  uninitialized_fill(data, limit, val);
}

template<class T>
void Vec<T>::create(const_iterator i, const_iterator j)
{
  data = alloc.allocate(j - i);
  limit = avail = uninitialized_copy(i, j, data);
}

// others

template<class T> void Vec<T>::uncreate()
{
  if(data) { // data should be non-zero, which deallocate() requires
    iterator it = avail;
    while (it != data)
      alloc.destroy(--it); // call the destroter of each obj, do what they do
    alloc.deallocate(data, limit - data);
  }
  data = limit = avail = 0;
}

template<class T> void Vec<T>::grow()
{
  size_type new_size = max(2 * (limit - data), ptrdiff_t(1)); // if empty
  iterator new_data = alloc.allocate(new_size);
  iterator new_avail = uninitialized_copy(data, avail, new_data);

  uncreate(); // data, avail, and limit are back to zero.
  data = new_data;
  avail = new_avail;
  limit = data + new_size;
}

template<class T> void Vec<T>::unchecked_append(const T& val)
{
  alloc.construct(avail++, val);
}

// test the program
#include "Student_info.h"
#include <iostream>
using std::cout; using std::endl;
int main_() // add underscore to make invalid
{
  // construction
  Vec<Student_info> vs;
  Vec<double> v(9);

  Vec<Student_info>::const_iterator b, e;
  Vec<Student_info>::size_type i = 0;

  for (i = 0; i != v.size(); ++i)
    cout << v[i] << endl;

    b = vs.begin();
    e = vs.end();

  return 0;
}
