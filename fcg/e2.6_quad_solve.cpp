// solve quadratic equation Ax^2 + Bx + C = 0

#include <cmath>
#include <iostream>

using namespace std;

int quad_solve(double a, double b, double c,
  double& x1, double& x2){

  double d = b * b - 4 * a * c; // discriminant
  if (b > 0.0) { // to take care of precision problem
    x1 = 2 * c / (-b - sqrt(d));
    x2 = (-b - sqrt(d)) / (2 * a);
  } else {
    x1 = (-b + sqrt(d)) / (2 * a);
    x2 = 2 * c / (-b + sqrt(d));
  }

  if (x1 > x2) { // fill the smaller solution to x1
    double tmp = x1;
    x1 = x2;
    x2 = tmp;
  }

  // return the number of valid solution 
  if (d == 0.0) return 1;
  else if (d > 0.0) return 2;
  else return 0;
}

int main(int argn, char** argv) {
  if (argn < 3) cout << "Not enough arguments." << endl;
  double a = atof(argv[1]);
  double b = atof(argv[2]);
  double c = atof(argv[3]);
  cout << "The solution(s) to " << a << "x^2 + " << b << "x + "
       << c << " is: " << endl;
  double x1, x2;
  int sus = quad_solve(a, b, c, x1, x2);
  if (sus == 0) {
    cout << "none." << endl;
  } else if (sus == 1) {
    cout << "x = " << x1 << endl;
  } else {
    cout << "x1 = " << x1 << ", x2 = " << x2 << endl;
  }

  return 0;
}
