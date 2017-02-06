// source file for Ref_handle.h
#include "Ref_handle.h"

template<class T>
Ref_handle<T>& Ref_handle<T>::operator=(const Ref_handle& rhs)
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

template<class T> Ref_handle<T>::~Ref_handle()
{
  if (--*refptr == 0) {
    delete refptr;
    delete p;
  }
}
