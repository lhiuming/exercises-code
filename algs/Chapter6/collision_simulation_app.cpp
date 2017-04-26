// Run a collision simulation of disks
#include <iostream>

#include "CollisionSystem.h"

using namespace std;

// the main funciton
int main()
{
  int num = 3;

  // make some random particles
  vector<Particle> vp;
  for (int i = 0; i < num; ++i)
    vp.push_back(Particle());

  // set up the systems
  CollisionSystem cs(std::move(vp));
  cout << "Created the collision system" << endl;

  return 0;
}
