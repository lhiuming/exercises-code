// Exercise 6.26 (p220)
// reading option arguments

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
  bool d = false;
  string ofile, ifile;

  // read the options
  size_t iter = 1;
  while (iter < argc) {
    if (*argv[iter] == '-') { // specific option field
      switch (argv[iter][1]) {
        case 'd':
          d = true;
          cout << "d: true" << endl;
          break;
        case 'o':
          ofile = argv[++iter];
          cout << "ofile: " << ofile << endl;
          break;
      }
    } else if (iter == argc - 1) {
      // the last argument is inputfile
      ifile = argv[iter];
      cout << "ifile: " << ifile << endl;
    }
    else {
      cout << "unknow options: " << string(argv[iter]) << endl;
    }
    ++iter; // for next string
  }

  // have a look at the last pointer
  cout << "argv[" << argc << "] : ";
  cout << reinterpret_cast<long>(argv[argc]) << endl; // should be zero

  return 0;
}
