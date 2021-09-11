#ifndef AABB_HPP
#define AABB_HPP

#include "rtweekend.hpp"

class aabb {
 public:
  aabb() {}
  aabb(const point3& a, const point3& b) {
    minimum = a;
    maximum = b;
  }
  point3 min() const { return minimum; }
  point3 max() const { return maximum; }

  bool hit(const ray& r, double t_min, double t_max) const;

  point3 minimum;
  point3 maximum;
};

aabb surrounding_box(const aabb& box0, const aabb& box1);

#endif  // AABB_HPP
