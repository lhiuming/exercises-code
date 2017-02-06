#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <exception>

#include "Student_info_class.h"

using std::vector;
using std::string;
using std::sort; using std::max;
using std::cout; using std::cin; using std::endl;
using std::domain_error;
using std::streamsize;
using std::setprecision;

int main()
{
  vector<Student_info> students;
  Student_info record;
  string::size_type maxlen = 0;

  while (record.read(cin)) {
    maxlen = max(maxlen, record.name().size());
    students.push_back(record);
  }

  sort(students.begin(), students.end(), compare);

  for (vector<Student_info>::size_type i = 0; i != students.size(); ++i) {
    cout << students[i].name()
      << string(maxlen + 1 - students[i].name().size(), ' ');
    try {
      double final_grade = students[i].grade();
      streamsize prec = cout.precision();
      cout << setprecision(3) << final_grade << setprecision(prec) << endl;
    } catch (domain_error e) {
      cout << e.what() << endl;
    }
  }

  return 0;

}
