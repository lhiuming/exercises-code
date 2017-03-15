/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting an integer by more
     than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implent floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operators (! ~ & ^ | + << >>)
     that you are allowed to use for your implementation of the function.
     The max operator count is checked by dlc. Note that '=' is not
     counted; you may use as many of these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/*
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  /* just use a simple logical equivalent: A and B = not ( not A or not B) */
  return ~ ((~x) | (~y));
}
/*
 * getByte - Extract byte n from word x
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: getByte(0x12345678,1) = 0x56
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int getByte(int x, int n) {
  /* shift the desire byte to right-most position, and extract it by &(0xff)
   * if n = 1, we need to right-shift 8 = n * 8 = n * 2^3 bits.
   */
  int shift_num = n << 3;
  return (x >> shift_num) & 0x000000ff;

}
/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int logicalShift(int x, int n) {
  /* right-shift using default arithmetic shift, than filled the new bits
   * by zeros (by using, like, 0x00ffffff to fill the 8 MSB).
   * Note thatn n is within 5 bits.
   */
  int fills = ( (1 << 31) >> n ) << 1;
  return (x >> n) & ~fills;
}
/*
 * bitCount - returns count of number of 1's in word
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 4
 */
int bitCount(int x) {
  /* Count in grids to save operation numbers. Adds each grid to the left.
   * Notices the total count won't exceed 32 -> at most 6 bits.
   */
  int grid_16 = 0xff + (0xff << 8);       // 00000000000000001111111111111111
  int grid_8 = grid_16 ^ (grid_16 << 8);  // 00000000111111110000000011111111
  int grid_4 = grid_8  ^ (grid_8  << 4);  // 00001111000011110...
  int grid_2 = grid_4  ^ (grid_4  << 2);  // 0011001100110...
  int grid_1 = grid_2  ^ (grid_2  << 1);  // 010101010...

  int count_1 = x;
  int count_2  = (count_1  >> 1  & grid_1 ) + (count_1  & grid_1 );
  int count_4  = (count_2  >> 2  & grid_2 ) + (count_2  & grid_2 );
  int count_8  = (count_4  >> 4  & grid_4 ) + (count_4  & grid_4 );
  int count_16 = (count_8  >> 8  & grid_8 ) + (count_8  & grid_8 );
  int count_32 = (count_16 >> 16 & grid_16) + (count_16 & grid_16);
  return count_32;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  /* taking | on each byte; using grids to same operations */
  int x_16 = x | (x >> 16);
  int x_8 = x_16 | (x_16 >> 8);
  int x_4 = x_8 | (x_8 >> 4);
  int x_2 = x_4 | (x_4 >> 2);
  int x_1 = x_2 | (x_2 >> 1);
  return ( ~x_1 ) & 1;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // using the standard 2's complement definition in 32-bits.
  return 1 << 31;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  /* truncated the input by setting the (32-n+1) MSBs to the sign bit.
   * if the turncated result is equal to x, then it fits n-bit-integer.
   */

  int allones = 1 << 31 >> 31;  // used as all-ones-bits and -1 value
  int m = n + allones;  // m = n - 1;
  int mask = allones << m;
  int MSBs = x >> 31 << 31 >> 31 << m;
  int truncated = (x & ~mask) | MSBs;
  return !(truncated ^ x);
}
/*
 * divpwr2 - Compute x/(2^n), for 0 <= n <= 30
 *  Round toward zero
 *   Examples: divpwr2(15,1) = 7, divpwr2(-33,4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int divpwr2(int x, int n) {
  /* increase lowest n bits to allow "round toward zero" for negative numbers.
   */
  int MSBs = x >> 31 << 31 >> 31;
  int nmask = ~(~0 << n);
  int nbits = MSBs & nmask;
  return (x + nbits) >> n;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  return ~x + 1;
}
/*
 * isPositive - return 1 if x > 0, return 0 otherwise
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 3
 */
int isPositive(int x) {
  /* x is positive when the MSB of x and x-1 are both 0.
   * In other words, non-positive when eigher x and x-1 is 1.
   */
  int minus_one = ~0;
  int MSB1 = (~x >> 31) & 1;
  int MSB2 = (~(x + minus_one) >> 31) & 1;
  return MSB1 & MSB2;
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  /* When x and y have the same sign, checking the sign of y-x is valid;
   * when x and y have different sign, return 1 only when y is non-negative.
   */
  int signx = (x >> 31) & 1;
  int signy = (y >> 31) & 1;
  int is_same_sign = !(signx ^ signy);
  int y_min_x = y + (~x + 1);
  int neg_diff = (y_min_x >> 31) & 1;

  return (is_same_sign & !neg_diff) | (!is_same_sign & !signy);
}
/*
 * ilog2 - return floor(log base 2 of x), where x > 0
 *   Example: ilog2(16) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 90
 *   Rating: 4
 */
int ilog2(int x) {
 /* @TODO: no idea how to do this!
  */
  return 1 | 1111;
}
/*
 * float_neg - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned float_neg(unsigned uf) {
 unsigned frac_bits = uf & 0x007fffff;
 unsigned exp_bits = (uf >> 23) & 0x000000ff;
 if (frac_bits != 0 && exp_bits == 0x000000ff)
   return uf;
 return uf ^ (1 << 31);
}
/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_i2f(int x) {
  /* @TODO: some how difficult; not comfortable with this many free operations!
   */
  int sign = x & 0x80000000;
  if (x < 0) x = -x;
  return 2;
}
/*
 * float_twice - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned float_twice(unsigned uf) {
  /* @TODO: some how difficult
   */
  unsigned frac_bits = uf & 0x007fffff;
  unsigned exp_bits = (uf >> 23) & 0x000000ff;

  // if NaN or infinite
  if (exp_bits == 0x000000ff) {
    printf("special\n");
    return uf; }

  // if non normalized and don't need to be turned normlaized
  if (exp_bits == 0 && !(frac_bits >> 22)) {
    printf("don't need to be normalized\n");
    return (uf & ~0x007fffff) + (frac_bits << 1);
  }

  // if has space in the exponent bits
  if (exp_bits < 254u) {
    printf("have space in expo\n");
    return uf + 0x00800000;
  }

  // if no space in the exponents, return infinite
  printf("overflow to inf\n");
  return (uf + 0x00800000) & ~0x007fffff;

}
