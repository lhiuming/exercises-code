//source file for Student_info
#include "Student_info.h"

using std::istream; using std::vector;

bool compare(const Student_info& x, const Student_info& y)
{
  return x.name < y.name;
}

istream& read(istream& is, Student_info& s)
{
  // read name, midterm, and final grade
  is >> s.name >> s.midterm >> s.fn;
  // read homework
  read_hw(is, s.homework);
  return is;
}

// read homework grades from input stream
istream& read_hw(istream& in, vector<double>& hw) {
  if (in) {
    // get rid of previous contnets
    hw.clear();
    // read grades
    double x;
    while(in >> x) // stop if input cannot be double
      hw.push_back(x);
    // clear the stream
    in.clear(); // reset error indications
  }
  return in;
}
