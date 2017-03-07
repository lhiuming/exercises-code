// Exercise 16.12 (p668)
// writing the Blob and BlobPrt template classes

#include <vector>
#include <memory>
#include <exception>
#include <initializer_list>

/* define Blob */

template <typename V>
class Blob {
public:
  // type defs
  typedef V value_type;
  typedef typename std::vector<V>::size_type size_type;

  // constructors
  Blob() { };
  Blob(std::initializer_list<V> il);

  // number of elements
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }

  // element operation
  void push_back(const V &v) { data->push_back(v); }
  void pop_back();

  // element access
  V& back();
  V& operator[](size_type i);

private:
  std::shared_ptr< std::vector<V> > data;
  void check(size_type i, const std::string &msg) const ;
};

// outside member functions

template <typename V>
Blob<V>::Blob(std::initializer_list<V> il) : data(il) { }

template <typename V>
void Blob<V>::check(size_type i, const std::string &msg) const
{
  if (i >= data->size())
    throw std::out_of_range(msg);
}


/* define BlobPtr */

template <typename V>
class BlobPtr {};
