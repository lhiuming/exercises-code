#include <string>
#include <iostream>
#include <fstream> // ifstream, ofstream

using std::cout; using std::endl;
using std::cin;  using std::cerr;
using std::string;
using std::ifstream;

int main(int argc, char **argv)
{
  int fail_count = 0;
  for (int i = 1; i < argc; ++i) {
    ifstream in(argv[i]);

    if (in) {
      string s;
      while (getline(in, s))
        cout << s << endl;
    } else {
      cerr << "cannot open file " << argv[i] << endl;
      ++fail_count;
    }
  }
  return fail_count;
}
