// Some class declaration of CollisionSystem

#include <sort.h>
#include <utils.h>

using namespace algs;

struct Particle {
  double x, y;     // Position
  double vx, vy;   // Velocity
  double r;        // Radius
  double mass;     // Mass

  Particle() = delete;
  Particle(double x, double y, double vx, double vy, double r, double mass) :
    x(x), y(y), vx(vx), vy(vy), r(r), mass(mass) {};

};
