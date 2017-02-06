// simpel stopwatch class working as timer
#ifndef ALGS_STOPWATCH_H
#define ALGS_STOPWATCH_H

#include <chrono>

namespace algs {

class Stopwatch {
public:
  // reocrd the time stamp at creation
  Stopwatch() {
    start = std::chrono::high_resolution_clock::now();
  }
  // return the time interval since creation, in seconds
  double elapsedTime() {
    using namespace std::chrono;
    milliseconds dtn = duration_cast<milliseconds> (
      high_resolution_clock::now() - start );
    return dtn.count() / 1000.0;
  }
private:
  std::chrono::high_resolution_clock::time_point start;
};

}

#endif
