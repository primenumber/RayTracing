#include "aabb.hpp"

bool aabb::hit(const ray& r, double t_min, double t_max) const {
  for (size_t a = 0; a < 3; ++a) {
    auto invD = 1.0 / r.direction()[a];
    auto t0 = fmin((minimum[a] - r.origin()[a]) * invD, (maximum[a] - r.origin()[a]) * invD);
    auto t1 = fmax((minimum[a] - r.origin()[a]) * invD, (maximum[a] - r.origin()[a]) * invD);
    t_min = fmax(t0, t_min);
    t_max = fmin(t1, t_max);
    if (t_max <= t_min) return false;
  }
  return true;
}

aabb surrounding_box(const aabb& box0, const aabb& box1) {
  point3 small(fmin(box0.min().x(), box1.min().x()), fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));
  point3 big(fmax(box0.max().x(), box1.max().x()), fmax(box0.max().y(), box1.max().y()),
             fmax(box0.max().z(), box1.max().z()));
  return aabb(small, big);
}
