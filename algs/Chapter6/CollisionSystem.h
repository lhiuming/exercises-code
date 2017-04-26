// Some class declaration of CollisionSystem

#include <vector>

#include <sort.h>
#include <utils.h>

// Particle class
struct Particle {
  double x, y;     // Position
  double vx, vy;   // Velocity
  double r;        // Radius
  double mass;     // Mass

  // simple constructor
  Particle(); // rondom configuration
  Particle(double x, double y, double vx, double vy, double r, double mass) :
    x(x), y(y), vx(vx), vy(vy), r(r), mass(mass) {};

  // operations
  void draw() const;
  void move(double t);
  int count() const { return collision_count; }  // number of collisions
  double timeToHit(Particle b) const ; // predicted time to collide with b
  double timeToHitHorizontalWall() const;
  double timeToHitVerticalWall() const;
  void bounceOff(Particle b); // actuall collision with b
  void bounceOffHorizontalWall();
  void bounceOffVerticalWall();

private:
  int collision_count = 0;

};

// CollisionSystem
class CollisionSystem {

  // a private Event class
  class Event {
    double time;
    const Particle *a, *b;
    int countA, countB;
  public:
    Event() = default;
    Event(double t, const Particle* a, const Particle* b)
     : time(t), a(a), b(b) {
      if (a != nullptr) countA = a->count(); else countA = -1;
      if (b != nullptr) countB = b->count(); else countB = -1;
    }
    bool valid() {
      if (a != nullptr && a->count() != countA) return false;
      if (b != nullptr && b->count() != countB) return false;
      return true;
    }
    friend bool operator<(const Event& lhs, const Event& rhs) {
      return lhs.time < rhs.time; }
  }; // end Event

public:

  // Constructors
  CollisionSystem(std::vector<Particle>& particles) : particles(particles) {};
  CollisionSystem(std::vector<Particle>&& particles) : particles(particles) {};

  // Deconstructor
  ~CollisionSystem() = default;

  // Operations
  void redraw(double t_limit, double Hz); // redraw all particles
  void simulate(double t_limit, double Hz); // run simulation

private:

  algs::MinPQ<Event> pq; // event priority queue
  double t = 0.0; // current simulation time
  std::vector<Particle> particles; // all particles

  // helpers
  void predict_collisions(Particle& a, double t_limit);

};
