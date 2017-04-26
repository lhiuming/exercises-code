// source of CollisionSystem.h
#include "CollisionSystem.h"

#include <iostream>

#include <utils/random.hpp>

using namespace std;
using namespace algs;

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
  cout << "Im a particle" << endl;
}

void Particle::move(double t) {};

double Particle::timeToHit(Particle b) const
{
  // TODO
  return 0;
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

void Particle::bounceOff(Particle b)
{
  // TODO
}

void Particle::bounceOffHorizontalWall()
{
  // TODO
}

void Particle::bounceOffVerticalWall()
{
  // TODO
}

// CollisionSystem methods

void CollisionSystem::predict_collisions(Particle& a, double t_limit)
{
  // hit particles
  for (int i = 0; i < particles.size(); ++i) {
    double dt = a.timeToHit(particles[i]);
    if (t + dt <= t_limit)
      pq.insert(Event(t + dt, &a, &particles[i]));
  } // end for

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
  if (t < t_limit) // for smooth display
    pq.insert(Event(t + 1.0 / Hz, nullptr, nullptr));
}

void CollisionSystem::simulate(double t_limit, double Hz)
{
  // TODO
}
