// source of CollisionSystem.h
#include "CollisionSystem.h"

#include <iostream>
#include <limits>

#include <utils/random.hpp>

using namespace std;
using namespace algs;

const double D_MAX = numeric_limits<double>::max();

// Particle methods

Particle::Particle()
{
  x = Random::uniform();
  y = Random::uniform();
  vx = Random::uniform();
  vy = Random::uniform();
  r = Random::uniform() * 0.1;
  mass = Random::uniform() * 10;
}

void Particle::draw() const
{
  // TODO: use algs::Draw
  cout << (*this) << endl;
}

void Particle::move(double t) {
  x += t * vx;
  y += t * vy;
};

double Particle::timeToHit(Particle& b) const
{
  // return 0 if already overlap ?
  const Particle& a = *this;
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  double r2 = a.r + b.r;
  if (dx*dx + dy*dy < r2*r2) return 0;

  return D_MAX;


}

double Particle::timeToHitHorizontalWall() const
{
  // TODO
  return 0;
}

double Particle::timeToHitVerticalWall() const
{
  // TODO
  return 0;
}

void Particle::bounceOff(Particle& b)
{
  // TODO
  cout << " particle bounces particle" << endl;
}

void Particle::bounceOffHorizontalWall()
{
  // TODO
  cout << "particle bounces horizontal wall" << endl;
}

void Particle::bounceOffVerticalWall()
{
  // TODO
  cout << "particle bounce horizontal wall" << endl;
}

std::ostream& operator<<(std::ostream& os, const Particle& p)
{
  os << "Particle[";
  os << "pos(" << p.x << "," << p.y << "), ";
  os << "vel(" << p.vx << "," << p.vy << "), ";
  os << "count: " << p.count();
  os << "]";
  return os;
}


// CollisionSystem methods

void CollisionSystem::predict_collisions(Particle *ap, double t_limit)
{
  if (ap == nullptr) return;
  Particle& a = *ap;

  // hit particles
  for (int i = 0; i < particles.size(); ++i) {
    double dt = a.timeToHit(particles[i]);
    if (t + dt <= t_limit)
      pq.insert(Event(t + dt, &a, &particles[i]));
  }

  // hit verical wall
  double dtX = a.timeToHitVerticalWall();
  if (t + dtX <= t_limit)
    pq.insert(Event(t + dtX, &a, nullptr));

  // hit horiztontal wall
  double dtY = a.timeToHitHorizontalWall();
  if (t + dtY <= t_limit)
    pq.insert(Event(t + dtY, nullptr, &a));

} // end predict_collisions

void CollisionSystem::redraw(double t_limit, double Hz)
{
  // TODO: implement algs::Draw singleton first
  for (const Particle& p : particles)
    p.draw();
  if (t < t_limit) // add next redraw
    pq.insert(Event(t + 1.0 / Hz, nullptr, nullptr));
  cout << "finished redraw" << endl;
}

void CollisionSystem::simulate(double t_limit, double Hz)
{
  // predict initial event
  for (int i = 0; i < particles.size(); ++i)
    predict_collisions(&particles[i], t_limit);
  cout << "Predicted initial events" << endl;
  pq.insert(Event(0, nullptr, nullptr)); // initial draw

  // the simulation loop
  while (!pq.empty())
  {
    cout << "get an event " << endl;
    Event e = pq.pop();
    if (!e.valid()) {
      cout << "invalid event" << endl;
      continue; }
    for (Particle& p : particles)
      p.move(e.time - t);
    t = e.time;
    // let the event happen
    if ( (e.a != nullptr) && (e.b != nullptr) ) e.a->bounceOff(*(e.b));
    if ( (e.a != nullptr) && (e.b == nullptr) ) e.a->bounceOffVerticalWall();
    if ( (e.a == nullptr) && (e.b != nullptr) ) e.b->bounceOffHorizontalWall();
    if ( (e.a == nullptr) && (e.b == nullptr) ) redraw(t_limit, Hz);
    // make new event from here
    predict_collisions(e.a, t_limit);
    predict_collisions(e.b, t_limit);
    cout << "finishe an evnet" << endl;
  }
} // end simulate
