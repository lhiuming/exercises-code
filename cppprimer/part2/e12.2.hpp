// Exercise 12.1 (p458)
// Writing StrBlob (using smart pointer)

#include <vector>
#include <string>
#include <initializer_list>
#include <memory>
#include <exception>

class StrBlob {
public:
  typedef std::vector<std::string>::size_type size_type;
  // constructores; defined outside
  StrBlob();
  StrBlob(std::initializer_list<std::string> il);
  // useful operators
  size_type size() const { return data->size(); }
  bool empty() const { return data->empty(); }
  // element operation
  void push_back(const std::string &s) { data->push_back(s); }
  void pop_back(); // outside
  // element access
  std::string front() const;  // outside
  std::string back() const;  // outside
private:
  std::shared_ptr< std::vector<std::string> > data;
  // throw error if i is an invalid index
  void check(size_type i, const std::string &msd) const;
};

// constructors
StrBlob::StrBlob(): data( std::make_shared<std::vector<std::string>>() ) {}
StrBlob::StrBlob(std::initializer_list<std::string> il):
  data( std::make_shared<std::vector<std::string>>(il) ) {}

// elements operation and access
std::string StrBlob::front() const
{
  check(0, "front on empty blob");
  return data->front();
}
std::string StrBlob::back() const
{
  check(0, "back on empty blob");
  return data->back();
}

// private utility function
void StrBlob::check(size_type i, const std::string &msg) const
{
  if (i >= data->size())
    throw std::out_of_range(msg);
}


#include <iostream>

using namespace std;

int main()
{
  cout << "testing StrBlob: " << endl;

  StrBlob b1;
  {
    StrBlob b2 = {"a", "miaomiao", "that"};
    b1 = b2;
    b2.push_back("wang");
  }
  cout << b1.size() << endl;
  cout << b1.front() << endl;
  cout << b1.back() << endl;

  return 0;
}
