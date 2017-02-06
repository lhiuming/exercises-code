// source file for Student_info class
#include "Student_info_class.h"

#include <string>
#include <vector>
#include <exception>
#include <iostream>

#include "median.h"

using std::domain_error;
using std::istream;
using std::vector;
using std::string;

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

// compute the overall grade
double grade(double midterm, double fn, double hw)
{
  return 0.2 * midterm + 0.4 * fn + 0.4 * hw;
}

// reload with homework grade vector
double grade(double midterm, double fn, const vector<double>& hw)
{
  if (hw.size() == 0)
    throw domain_error("student has done no homework");
  return grade(midterm, fn, median(hw));
}


// external compare function

bool compare(const Student_info& x, const Student_info& y)
{ return x.name() < y.name(); }


// class member functions

istream& Student_info::read(istream& in)
{
  in >> n >> midterm >> final;
  read_hw(in, homework);
  return in;
}

double Student_info::grade() const
{
  return ::grade(midterm, final, homework);
}


// Constructors
Student_info::Student_info(): midterm(0), final(0) {}
Student_info::Student_info(istream& is) { read(is); }
