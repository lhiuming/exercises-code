#ifndef GUARD_median_h
#define GUARD_median_h

// median.h, with GUARD to protect mulitpble including
#include <vector>
double median(std::vector<double>); // use std:: rather than 'using'
template<class Iter, class V>
V median_gr(Iter, Iter);

#endif
