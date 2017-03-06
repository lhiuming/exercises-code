// Exercise 15.5 (p601)
// Define a derived class

#include "e15.3_Quote.hpp"

class Bulk_quote : public Quote {
public:
  Bulk_quote() = default;
  Bulk_quote(std::string &s, double prive, std::size_t mq, double disaccount);

  // overide
  double net_price(std::size_t putchase) const override;
protected:
  std::size_t min_quantity;
  double disaccount;
};

Bulk_quote::Bulk_quote(std::string  &s, double price, std::size_t mq, double dis) :
Quote(s, price), min_quantity(mq), disaccount(dis) { }

double
Bulk_quote::net_price(std::size_t purchase) const
{
  if (purchase > min_quantity)
    return purchase * price;
  else
    return purchase * price * ( 1 - disaccount);
}
