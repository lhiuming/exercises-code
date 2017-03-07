// Exercise 15.3 (p595)
// Defining base class

#include <string>

class Quote {
public:
  Quote() = default;
  Quote(const std::string &book, double sales_price) :
    bookNo(book), price(sales_price) {}
  std::string isbn() const { return bookNo; }

  // virtual function; derived class must redefine them
  virtual double net_price(std::size_t n) const { return n * price; }
  virtual ~Quote() = default;
private:
  std::string bookNo;
protected:
  double price = 0.0;
};
