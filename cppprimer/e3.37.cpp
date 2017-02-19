// Exercise 3.27 (p115)
// illegal dimension value


int txt_size() { return 3; }

/* These two are illegal:
 */
unsigned buf_size = 1024;
int ia[buf_size];    // buf_size is not constexpr
int ib[txt_size()];  // the function call is not constexpr either

/* these two are legal:
 */
 int ic[4 * 7 - 14];         // constant expression
 char st[11] = "fundamenal"; // initializer is not exceeding the dimension

 int main() { return 0; }
