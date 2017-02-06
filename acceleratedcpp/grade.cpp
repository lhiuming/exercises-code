#include <stdexcept>
#include <vector>
#include "grade.h"
#include "median.h"
#include "Student_info.h"

using std::domain_error;
using std::vector;

// reload for the record structure
double grade(const Student_info& s)
{
  return grade(s.midterm, s.fn, s.homework);
}

// reload with homework grade vector
double grade(double midterm, double fn, const vector<double>& hw)
{
  if (hw.size() == 0)
    throw domain_error("student has done no homework");
  return grade(midterm, fn, median(hw));
}

// compute the overall grade
double grade(double midterm, double fn, double hw)
{
  return 0.2 * midterm + 0.4 * fn + 0.4 * hw;
}
