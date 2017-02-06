#ifndef GUARD_Ref_handle_h
#define GUARD_Ref_handle_h

#include <exception>

template<class T> class Ref_handle {
public:
  Ref_handle(): refptr(new size_t(1)), p(0) {}
  Ref_handle(T* t): refptr(new size_t(1)), p(t) {}
  Ref_handle(const Ref_handle& h): refptr(h.refptr), p(h.p)
  {
    ++*refptr;
  }

  Ref_handle& operator=(const Ref_handle&);
  ~Ref_handle();

  // as in Handle.h
  operator bool() const { return p; }
  T& operator*() const
  {
    if (p)
      return *p;
    throw std::runtime_error("unbound Ref_handle");
  }

  T* operator->() const {
    if (p)
      return p;
    throw std::runtime_error("unbound Ref_handle");
  }

private:
  T* p;
  size_t* refptr;  // the counter
};

#endif
