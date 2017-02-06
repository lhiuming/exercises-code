// source file for Handle.h
#include "Handle.h"
#include <exception>

using std::runtime_error;

template<class T>
Handle<T>& Handle<T>::operator=(const Handle& rhs)
{
  if (&rhs != this) { // check: avoid self-assignment
    delete p;
    p = rhs.p ? rhs.p->clone() : 0;
  }
  return *this;
}

// pointer like behaviours
template<class T>
T& Handle<T>::operator*() const
{
  if (p)
    return *p;
  throw runtime_error("unboud Handle");
}

template<class T>
T* Handle<T>::operator->() const
{
  if (p)
    return p;
  throw runtime_error("unhound Handle");
}
