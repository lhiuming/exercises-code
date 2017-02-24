// Ecerciese 6.3 (p205)
// compute factorials
// this code is used in e6.4, e6.8 and e6.9

#include "e6.8_Chapter6.h" // include for verification

int fact(int n)
{
  int ret = 1;
  while (n > 0)
    ret *= n--;
  return ret;
}
