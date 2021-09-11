#ifndef UTILS_HPP
#define UTILS_HPP

#include <cmath>
#include <limits>
#include <random>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

inline double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

inline double random_double() {
  thread_local std::random_device rd;
  thread_local std::minstd_rand gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  return dis(gen);
}

inline double random_double(double min, double max) { return min + (max - min) * random_double(); }

#endif  // UTILS_HPP
