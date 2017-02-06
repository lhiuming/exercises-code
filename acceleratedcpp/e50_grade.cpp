#include <iostream>
#include <vector>
#include "Student_info.h"



// return a new vector; replace the old vector
vector<Student_info> extract_fails(vector<Student_info>& students)
{
  vector<Student_info> pass, fail;

  for (vector<Student_info>::size_type i = 0; i != student.size(); i++)
    if (fgrade(students[i]))
      fail.push_back(student[i]);
    else
      pass.push_back(students[i]);

  students = pass;
  return fail;
}

// use lisk instead of vector
list<Student_info> extract_fails(list<Student_info>& students)
{
  list<Student_info> fail;
  list<Student_info>::iterator iter = students.begin();

  while (iter != students.end()) {
    if (fgrade(*iter)) {
      fail.push_back(*iter);
      iter = students.erase(iter);
    } else
      ++iter;
  }
  return fail;
}



// predicate to determine whether a student failed
bool fgrade(const Student_info& s)
{
  return grade(s) < 60;
}
