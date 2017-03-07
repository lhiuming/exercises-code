// Exercise 15.15 (p611)
// defining pure abstract class as interface

#include "e15.3_Quote.hpp"

#include <string>

// the interface / pure abstract class
class Disc_quote : public Quote {
public:
  // constructors; possbily only used full to dirived classes
  Disc_quote() = default;
  Disc_quote(const std::string &bookname, double price, std::size_t qty,
    double disc) :  Quote(bookname, price), quantity(qty), discount(disc) { }
  // pure virtual function
  double net_price(std::size_t)   const   = 0;
protected:  // possibly no private member for abstract classes?
  std::size_t quantity = 0;
  double discount = 0.0;
};

// a class use the interface
class Bulk_quote : public Disc_quote {
public:
  Bulk_quote() = default;
  Bulk_quote(const std::string &bookname, double price, std::size_t qty,
    double disc) : Disc_quote(bookname, price, qty, disc) { }
  // override the virtual function
  double net_price(std::size_t) const override;
private:
};

double Bulk_quote::net_price(std::size_t purchase) const
{
  if (purchase > quantity)
    return purchase * price * (1 - discount);
  else
    return purchase * price;
}
