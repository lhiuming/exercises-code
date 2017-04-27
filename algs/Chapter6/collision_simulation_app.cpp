// Run a collision simulation of disks
#include <iostream>

#include "CollisionSystem.h"

using namespace std;

// the main funciton
int main(int argc, char** argv)
{
  // TODO: read it from argv
  int num = 3;

  // Set up the systems with random particles
  CollisionSystem cs{vector<Particle>(num)};
  cout << "Created the collision system" << endl;

  // Run the simulation for some time
  cs.simulate(10, 60.0);

  return 0;
}
