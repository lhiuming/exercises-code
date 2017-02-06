// source file for Ptr.h
#include "Ptr.h"

template<class T>
Ptr<T>& Ptr<T>::operator=(const Ptr& rhs)
{
  // the right hand side is increased.
  // do it here to avoid self-assignment
  ++*rhs.refptr;

  if (--*refptr == 0) { // if object of lhr has no other reference
    delete refptr;
    delete p;
  }

  refptr = rhs.refptr; // points to the same counter
  p = rhs.p; // points to the same underlying object
  return *this;
}

template<class T>
Ptr<T>::~Ptr()
{
  if (--*refptr == 0) {
    delete refptr;
    delete p;
  }
}

// if T has clone() method
template<class T>
T* clone(const T* tp)
{
  return tp->clone();
}
