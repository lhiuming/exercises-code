// Exercise 8.4 (p319)
// pratice reading files

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int  main(int argc, char **argv) {
  // check the argument number
  if (argc < 1) {
    cout << "Please inpu a file name. " << endl;
    return -1;
  }

  // open the file
  ifstream in(argv[1]);
  if (!in) {
    cout << "Invalid filename: " << argv[1] << endl;
    return -1;
  }

  // read the file
  string s;
  vector<string> v;
  while (getline(in, s))
    v.push_back(s);

  cout << "Total line number is " << v.size() << endl;
  return 0;
}
