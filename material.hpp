#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <algorithm>
#include <memory>

#include "rtweekend.hpp"

struct hit_record;

class material {
 public:
  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
  ) const = 0;
};

using material_ptr = std::shared_ptr<material>;

class lambertian : public material {
 public:
  lambertian(const color& a) : albedo(a) {}
  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
  ) const override;

 public:
  color albedo;
};

class metal : public material {
 public:
  metal(const color& a, double f) : albedo(a), fuzz(std::clamp(f, 0.0, 1.0)) {}
  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
  ) const override;

 public:
  color albedo;
  double fuzz;
};

class dielectric : public material {
 public:
  dielectric(double index_of_refraction) : ir(index_of_refraction) {}
  virtual bool scatter(
      const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered
  ) const override;

 public:
  double ir;
};

#endif // MATERIAL_HPP
