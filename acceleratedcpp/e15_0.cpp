// testing the Picture interface

#include <string>
#include <vector>
#include <iostream>
#include "Picture.h"

using std::vector;
using std::string;
using std::cin; using std::cout; using std::endl;

int main()
{
  const char* a[] = { "Hello, world!", "I'm miaomiao!!!" };
  vector<string> v(a, a+2);
  string sep(80, '-');

  Picture greet = v;
  cout << greet << sep << endl ;

  Picture fgreet = frame(greet);
  cout << fgreet << sep << endl;

  Picture hgreet = hcat(greet, fgreet);
  cout << hgreet << sep << endl;

  Picture trigreet = vcat(fgreet, hgreet);
  cout << trigreet << sep << endl;

  cout << frame(hcat(hgreet, vcat(trigreet, greet))) << endl;
}
