#ifndef GUARD_Student_info_class_h
#define GUARD_Student_info_class_h

#include <string>
#include <vector>

class Student_info {
public:
  Student_info();  // empty constructor
  Student_info(std::istream&); // construct one by reading a stream

  std::string name() const { return n; }
  bool valid() const {return !homework.empty(); }
  double grade() const; // 'const': function will not change the obj data
  std::istream& read(std::istream&);
private:
  std::string n;
  double midterm, final;
  std::vector<double> homework;
};

// some function decleration
bool compare(const Student_info&, const Student_info&);

#endif
