#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <exception>
#include "CoreGrad.h"
#include "Handel.h"

using std::vector;
using std::string;
using std::max;
using std::cout; using std::endl; using std::cin;
using std::streamsize; using std::setprecision;
using std::domain_error;

int main()
{
  vector< Handle<Core> > students;
  Handle<Core> record;
  char ch;
  string::size_type maxlen = 0;

  while (cin >> ch) {
    if (ch == 'U')
      record = new Core;
    else
      record = new Grad;
    record->read(cin);
    maxlen = max(maxlen, record->name().size());
    students.push_back(record);
  }
  /*
  while (record.read(cin)) {
    maxlen = max( maxlen, record.name().size() );
    students.push_back(record);
  }
  */

  //sort(students.begin(), students.end(), Student_info::compare);
  sort(students.begin(), students.end(), compare_Core_handles);

  for (vector< Handle<Core> >::size_type i = 0; i != students.size(); i++) {
    cout << students[i]->name()
    << string(maxlen + 1 - students[i]->name().size(), ' ');
    try {
      double final_grade = students[i]->grade();
      streamsize prec = cout.precision();
      cout << setprecision(3) << final_grade << setprecision(prec) << endl;
    } catch (domain_error e) {
      cout << e.what() <<endl;
    }
  }
  return 0;
}
