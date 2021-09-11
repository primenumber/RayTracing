#ifndef HITTABLE_HPP
#define HITTABLE_HPP

#include "material.hpp"
#include "rtweekend.hpp"

struct hit_record {
  point3 p;
  vec3 normal;
  material_ptr mat_ptr;
  double t;
  bool front_face;

  void set_face_normal(const ray& r, const vec3& outword_normal) {
    front_face = dot(r.direction(), outword_normal) < 0;
    normal = front_face ? outword_normal : -outword_normal;
  }
};

class hittable {
 public:
  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

#endif  // HITTABLE_HPP
