#ifndef GUARD_Student_info
#define GUARD_Student_info

// Stduent_info.h
#include <iostream>
#include <string>
#include <vector>

// why here needs to define the struct??
struct Student_info {
  std::string name;
  double midterm, fn;
  std::vector<double> homework;
}; // note the semicolon

bool compare(const Student_info&, const Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif
