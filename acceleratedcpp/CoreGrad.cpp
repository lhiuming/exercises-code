// source coede for "CoreGrad.h"
#include "CoreGrad.h"

#include <string>
#include <vector>
#include <iostream>
#include <algorithm> // min()
#include <exception>

using std::endl; using std::cout;
using std::string;
using std::vector;
using std::istream;
using std::min;
using std::domain_error;

// functionalities

// median function
double median(vector<double> vec)
{
  typedef vector<double>::size_type vec_sz;
  vec_sz size = vec.size();
  if (size==0)
    throw domain_error("median of an empty vector");

  sort(vec.begin(), vec.end());
  vec_sz mid = size / 2;

  return size%2 == 0 ? (vec[mid] + vec[mid+1])/2 : vec[mid];
}
// compute the overall grade
double grade(double midterm, double fn, double hw)
{
  return 0.2 * midterm + 0.4 * fn + 0.4 * hw;
}
// reload with homework grade vector
double grade(double midterm, double fn, const vector<double>& hw)
{
  if (hw.size() == 0)
    //throw domain_error("student has done no homework");
    return 0;
  return grade(midterm, fn, median(hw));
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

// end functionality

// operations for Core
string Core::name() const {
  cout << "Core::name()" << endl;
  return n;
}

double Core::grade() const
{
  cout << "Core::grade()" << endl;
  return ::grade(midterm, final, homework);
}

istream& Core::read_common(istream& in)
{
  in >> n >> midterm >> final; // name and exam grades
  return in;
}

istream& Core::read(istream& in)
{
  read_common(in);
  read_hw(in, homework);
  return in;
}

// operations for Grad
istream& Grad::read(istream& in)
{
  read_common(in);
  in >> thesis;
  read_hw(in, homework);
  return in;
}

double Grad::grade() const
{
  cout << "Grad::grade()" << endl;
  return min(Core::grade(), thesis); // grade is the lesser of them
}

// non-member functions
bool compare(const Core& c1, const Core& c2)
{
  return c1.name() < c2.name();
}
bool compare_grades(const Core& c1, const Core& c2)
{
  return c1.grade() < c2.grade();
}

// operations for Student_info
istream& Student_info::read(istream& is) {
  delete cp; // make sure the handel is free

  char ch;
  is >> ch;
  if (ch == 'U') {
    cp = new Core(is);
  } else {
    cp = new Grad(is);
  }

  return is;
}

Student_info::Student_info(const Student_info& s): cp(0)
{
  if (s.cp) cp = s.cp->clone();
}

Student_info& Student_info::operator=(const Student_info& s)
{
  if (&s != this) { // avoid self-assignment
    delete cp;
    if (s.cp)
      cp = s.cp->clone();
    else
      cp = 0;
  }
  return *this;
}
