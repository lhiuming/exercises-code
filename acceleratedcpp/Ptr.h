#ifndef GUARD_Ptr_h
#define GUARD_Ptr_h

//#include <exception>
#include <stdexcept>
#include <cstddef>

template<class T> class Ptr {
public:
  // a member for conditionally copy
  void make_unique() {
    if (*refptr != 1) {
      --*refptr;
      refptr = new size_t(1);
      p = p ? clone(p): 0 ;
    }
  }

  Ptr(): refptr(new size_t(1)), p(0) {}
  Ptr(T* t): refptr(new size_t(1)), p(t) {}
  Ptr(const Ptr& h): refptr(h.refptr), p(h.p) { ++*refptr; }

  Ptr& operator=(const Ptr&);  // defined in source file
  ~Ptr(); // defined in source file

  operator bool() const { return p; }

  T& operator*() const
  {
    if (p)
      return *p;
    throw std::runtime_error("unbound Ptr");
  }

  T* operator->() const
  {
    if (p)
      return p;
    throw std::runtime_error("unboud Ptr");
  }

private:
  T* p;
  size_t* refptr;
};

#endif
