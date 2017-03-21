# Notes in cracking the bomb

## phase_1

The first phase (char string) is hard-coded in the phase_1() function, at address 0x402400. It actually appears in '$> strings bomb' output.

## phase_2

- read_six_numbers() reads 6 int from the input; if the reading fails
  (e.g. non-number appears in the first 6 char), it will explode the bomb.
  The result 6 integers (32-bit int) are returned by writing to a array
  allocated by the caller.I guess it is called as
  read_six_numbers(char* input, int ret[]).
- first number is 1 (  cmpl   $0x1,(%rsp)  )
- other numbers are checked by a loop (starting from +27):
  - n2 should equal to n1 + n1 (which is 2);
  - n3 should equal to n7???
