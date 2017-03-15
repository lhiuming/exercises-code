// Trying to reproduce some strange behaviors in the assignment code

#include <stdio.h>
#include <limits.h>
#include "bits.h"

int fitsBits_db(int x, int n) {
  int TMin = -(1 << (n-1));
  int TMax = (1 << (n-1)) - 1;
  return TMin <= x && x <= TMax;
}

int main() {
  printf("test_fitsBits(%i, 32): %d\n", 0, test_fitsBits(0, 32));
  printf("test_fitsBits(%i, 32): %d\n", INT_MAX, test_fitsBits(INT_MAX, 32));
  printf("test_fitsBits(%i, 32): %d\n", INT_MIN, test_fitsBits(INT_MIN, 32));

  return 0;
}
