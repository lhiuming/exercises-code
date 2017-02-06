#include <iostream>
#include <string>

namespace algs {

class StdDraw {
public:
  // basic methods
  static void line(double x0, double y0, double x1, double y1) {}
  static void point(double x, double y) {}
  static void text(double x, double y, std::string) {}
  static void circle(double x, double y, std::string s) {}
  static void filledCircle(double x, double y, double r) {}
  static void ellipse(double x, double y, double rw, double rh) {}
  static void filledEllipse(double x, double y, double rw,
    double rh) {}
  static void square(double x, double y, double r) {}
  static void filledSquare(double x, double y, double r) {}
  static void rectangle(double x, double y, double rw, double rh)
    {}
  static void filledRectangle(double x, double y, double rw,
    double rh) {}
  static void polygon(double[] x, double[] y) {}
  static void filledPolygon(double[] x, double[] y) {}

  // control methods: left
}

}
