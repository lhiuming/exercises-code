// Exercise 15.27 (p629)
// redefine this class, using inherited constructors

#include "e15.3_Quote.hpp"

#include <string>

class Bulk_quote : public Quote {
public:
  // inherited the base constructors;
  // default constructor is synthesized automatically in this derived class
  using Quote::Quote;
  Bulk_quote(const std::string &s, double price, std::size_t mq, double disc);

  // overide
  double net_price(std::size_t putchase) const override;

  // copy and move clone; see e15.30
  Bulk_quote* clone() const & { return new Bulk_quote(*this); }
  Bulk_quote* clone() && { return new Bulk_quote(std::move(*this)); }
protected:
  std::size_t min_quantity;
  double disccount;
};

Bulk_quote::Bulk_quote(const std::string &s, double price, std::size_t mq, double disc) :
Quote(s, price), min_quantity(mq), disccount(disc) { }

double
Bulk_quote::net_price(std::size_t purchase) const
{
  if (purchase > min_quantity)
    return purchase * price;
  else
    return purchase * price * ( 1 - disccount);
}
