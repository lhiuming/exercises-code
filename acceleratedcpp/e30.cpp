#include <algorithm> // sort
#include <iomanip> // setprecision
#include <ios> // streamsize
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::setprecision;
using std::sort;
using std::streamsize;
using std::string;
using std::vector;

int main()
{
  cout << "あなたの名前を入力ください：";
  string name;
  cin >> name;
  cout << "こんにちは、" << name << "さん！" << endl;

  cout << "Please enter your midterm and final exam grades:";
  double midterm, final;
  cin >> midterm >> final;

  cout << "Enter all your homework grades, "
    "followed by end-of-file:";

  vector<double> homework;
  double x;
  // invariant: homework contains all the homework grades read so far
  while (cin >> x)
    homework.push_back(x);

  // check
  typedef vector<double>::size_type vec_sz;
  vec_sz size = homework.size();
  if(size == 0) {
    cout << endl << "成績を必ず入力してください。"
      "もう一度試してください。" << endl;
    return 1;
  }

  sort(homework.begin(), homework.end());

  vec_sz mid = size/2;
  double median = size % 2 == 0 ? (homework[mid] + homework[mid-1]) / 2
    :homework[mid];

  streamsize prec = cout.precision();
  cout << "あなたの最終的な成績は" << setprecision(3) << 0.2*midterm +
    0.4*final + 0.4*median << setprecision(prec) << "点です。" << endl;

  return 0;
}
