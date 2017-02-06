#include <math>

namespace algs {

class Point2D {
public:
  Point2D(double x, double y);

  double x() { return x; }
  double y() { return y; }
  double r() { return sqrt(x*x + y*y); }
  double theta(); // define in source
  double distTo(const Point2D& that) {
    return sqrt( (x-that.x())*(x-that.x()) +
                 (y-that.y())*(y-that.y()) );
  }
private:
  int x, y;
}

}
