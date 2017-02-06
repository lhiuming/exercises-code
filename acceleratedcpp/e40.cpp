#include <algorithm>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "grade.h"
#include "Student_info.h"

using std::cin;
using std::cout;
using std::endl;
using std::domain_error;
using std::max;
using std::sort;
using std::string;
using std::vector;

int main()
{
  vector<Student_info> students;
  Student_info record;
  string::size_type maxlen = 0;

  // read and store all records
  cout << "Please input students name, midterm, final, and homework grades. "
          " After entering all records, enter a EOF:" << endl;
  while (read(cin, record)) {
    maxlen = max(maxlen, record.name.size());
    students.push_back(record);
  }

  // alphabetize the records
  sort(students.begin(), students.end(), compare);

  for (vector<Student_info>::size_type i = 0; i != students.size(); i++) {
    // write names
    cout << students[i].name
         << string(maxlen + 1 - students[i].name.size(), ' ');

    // write grades
    try {
      double final_grade = grade(students[i]);
      cout << "Your final grade is " << final_grade << endl;
    } catch (domain_error e) {
      cout << e.what();
    }
    cout << endl;
  }

  return 0;
}
