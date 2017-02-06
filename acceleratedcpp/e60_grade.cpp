#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <exception>

#include "Student_info.h"
#include "median.h"
#include "grade.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::domain_error;
using std::ostream;

/* FUnctions
   too lazy to organize */

bool did_all_hw(const Student_info& s)
{
  return ( (find(s.homework.begin(), s.homework.end(), 0))
           == s.homework.end() );
}


// print the report
void write_analysis(ostream& out, const string& name,
                    double analysis_fun(const vector<Student_info>&),
                    const vector<Student_info>& did,
                    const vector<Student_info>& didnt)
{
  out << name << ": median(did) = " << analysis_fun(did)
              << ", median(didnt) = " << analysis_fun(didnt) << endl;
}

// used in median_analysis, below
double grade_aux(const Student_info& s)
{
  try {
    return grade(s);
  } catch (domain_error) {
    return grade(s.midterm, s.fn, 0);
  }
}

double average(const vector<double>& v)
{ return accumulate(v.begin(), v.end(), 0.0) / v.size(); }

// used in average_analysis
double average_grade(const Student_info& s)
{
  return grade(s.midterm, s.fn, average(s.homework));
}

// used in optimistic_median_analysis
double optimistic_median(const Student_info& s)
{
  vector<double> nonzero;
  remove_copy(s.homework.begin(), s.homework.end(),
    back_inserter(nonzero), 0);

  if (nonzero.empty())
    return grade(s.midterm, s.fn, 0);
  else
    return grade(s.midterm, s.fn, median(nonzero));
}

// prototype FUnction
double analysis(const vector<Student_info>& students,
                double grade_function(const Student_info&))
{
  vector<double> grades;
  transform(students.begin(), students.end(), back_inserter(grades),
    grade_function);
  return median(grades);
}

// 1. alternative analysis
double average_analysis(const vector<Student_info>& students)
{ return analysis(students, average_grade); }

// 2. old fashion analysis
double median_analysis(const vector<Student_info>& students)
{ return analysis(students, grade_aux); }

// 3. higher grade methiod
double optimistic_median_analysis(const vector<Student_info>& students)
{ return analysis(students, optimistic_median); }


// more compact implmentation, from Chapter 8
template <class GradeFuncType>
void write_analysis_T(ostream& out, const string& name,
                    GradeFuncType grad_func,
                    const vector<Student_info>& did,
                    const vector<Student_info>& didnt)
{
  out << name << ": median(did) = " << analysis(did, grad_func)
              << ", median(didnt) = " << analysis(didnt, grad_func) << endl;
}


// too lazy to organize

int main()
{
  vector<Student_info> did, didnt;
  Student_info student;

  // read and seperate all records
  while (read(cin, student)) {
    if (did_all_hw(student))
      did.push_back(student);
    else
      didnt.push_back(student);
  }

  // check that both groups cotaint data
  if (did.empty()) {
    cout << "No Student did all the homework!" << endl;
    return 1;
  }
  if (didnt.empty()) {
    cout << "Every student did all the homework!" << endl;
    return 1;
  }

  // do the analysis here
  cout << "\tOld fashion: " << endl;
  write_analysis(cout, "median", median_analysis, did, didnt);
  write_analysis(cout, "average", average_analysis, did, didnt);
  write_analysis(cout, "median of hw turned in", optimistic_median_analysis,
                 did, didnt);

  cout << endl << "\tTemplate fashion: " << endl;

  write_analysis_T(cout, "median", grade_aux, did, didnt);
  write_analysis_T(cout, "average", average_grade, did, didnt);
  write_analysis_T(cout, "median of hw turned in", optimistic_median,
                                did, didnt);


  return 0;
}
