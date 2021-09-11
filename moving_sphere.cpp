#include <cmath>

#include "moving_sphere.hpp"

bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  vec3 oc = r.origin() - center(r.time());
  auto a = r.direction().norm();
  auto half_b = dot(oc, r.direction());
  auto c = oc.norm() - radius * radius;

  auto discriminant = half_b * half_b - a * c;
  if (discriminant < 0) return false;
  auto sqrtd = sqrt(discriminant);

  auto root = (-half_b - sqrtd) / a;
  if (root < t_min || t_max < root) {
    root = (-half_b + sqrtd) / a;
    if (root < t_min || t_max < root) return false;
  }

  rec.t = root;
  rec.p = r.at(rec.t);
  vec3 outward_normal = (rec.p - center(r.time())) / radius;
  rec.set_face_normal(r, outward_normal);
  rec.mat_ptr = mat_ptr;

  return true;
}

point3 moving_sphere::center(double time) const {
  return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}
