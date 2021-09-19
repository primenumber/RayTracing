#include "aabb.hpp"

bool aabb::hit(const ray& r, double t_min, double t_max) const {
  auto invD = 1.0 / r.direction();
  auto t0 = (min() - r.origin()) * invD;
  auto t1 = (max() - r.origin()) * invD;
  for (size_t a = 0; a < 3; ++a) {
    if (invD[a] < 0.0) {
      std::swap(t0[a], t1[a]);
    }
    t_min = std::max(t0[a], t_min);
    t_max = std::min(t1[a], t_max);
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
