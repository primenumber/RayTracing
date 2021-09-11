#ifndef SPHERE_HPP
#define SPHERE_HPP

#include "hittable.hpp"
#include "material.hpp"
#include "vec3.hpp"

class sphere : public hittable {
 public:
  sphere() {}
  sphere(point3 cen, double r, material_ptr m) : center(cen), radius(r), mat_ptr(m) {}
  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

 private:
  point3 center;
  double radius;
  material_ptr mat_ptr;
};

#endif  // SPHERE_HPP
