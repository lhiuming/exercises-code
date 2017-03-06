// Exercise 15.7 (p601)
// define le related class

#include "e15.5_Bulk_quote.hpp"

class Bulk_quote_limited : public Bulk_quote {
public:
  // basic the same constroctor as the base
  Bulk_quote_limited() = default;
  Bulk_quote_limited(std::string &s, double price, std::size_t minQ,
    std::size_t maxQ, double dis) :
    Bulk_quote(s, price, minQ, dis), max_quantity(maxQ) {};
  // override the net_price method
  double net_price(std::size_t purchase) const override;
private:
  std::size_t max_quantity;
};

double
Bulk_quote_limited::net_price(std::size_t purchase) const
{
  if (purchase > min_quantity)
    if (purchase <= max_quantity)
      return purchase * price * disaccount;
    else
      return price * ( max_quantity * (1 - disaccount)  +  (purchase - max_quantity) );
  else
    return purchase * price;
}
