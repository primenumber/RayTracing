#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

#include "utils.hpp"

class vec3 {
 public:
  vec3() : e{0, 0, 0, 0} {}
  vec3(double e0, double e1, double e2) : e{e0, e1, e2, 0} {}
  vec3(double e0, double e1, double e2, double e3) : e{e0, e1, e2, e3} {}

  double x() const { return e[0]; }
  double y() const { return e[1]; }
  double z() const { return e[2]; }

  vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  double operator[](size_t i) const { return e[i]; }
  double& operator[](size_t i) { return e[i]; }

  vec3& operator+=(const vec3& rhs) {
    e[0] += rhs.e[0];
    e[1] += rhs.e[1];
    e[2] += rhs.e[2];
    return *this;
  }

  vec3& operator*=(const double rhs) {
    e[0] *= rhs;
    e[1] *= rhs;
    e[2] *= rhs;
    return *this;
  }

  vec3& operator/=(const double rhs) { return *this *= 1. / rhs; }

  double length() const { return std::sqrt(norm()); }

  double norm() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }

  bool near_zero() const {
    constexpr auto s = 1e-8;
    return fabs(e[0]) < s && fabs(e[1]) < s && fabs(e[2]) < s;
  }

  static vec3 random() { return vec3(random_double(), random_double(), random_double()); }

  static vec3 random(double min, double max) {
    return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
  }

 public:
  double e[4];
};

using point3 = vec3;  // 3D point
using color = vec3;   // RGB color

inline std::ostream& operator<<(std::ostream& os, const vec3& v) {
  return os << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

inline vec3 operator+(const vec3& lhs, const vec3& rhs) {
  return vec3(lhs.e[0] + rhs.e[0], lhs.e[1] + rhs.e[1], lhs.e[2] + rhs.e[2]);
}

inline vec3 operator-(const vec3& lhs, const vec3& rhs) {
  return vec3(lhs.e[0] - rhs.e[0], lhs.e[1] - rhs.e[1], lhs.e[2] - rhs.e[2]);
}

inline vec3 operator*(const vec3& lhs, const vec3& rhs) {
  return vec3(lhs.e[0] * rhs.e[0], lhs.e[1] * rhs.e[1], lhs.e[2] * rhs.e[2]);
}

inline vec3 operator*(const double lhs, const vec3& rhs) {
  return vec3(lhs * rhs.e[0], lhs * rhs.e[1], lhs * rhs.e[2]);
}

inline vec3 operator*(const vec3& lhs, const double rhs) { return rhs * lhs; }

inline vec3 operator/(const vec3& lhs, const double rhs) { return (1. / rhs) * lhs; }

inline vec3 operator/(const double lhs, const vec3& rhs) {
  return vec3(lhs / rhs.e[0], lhs / rhs.e[1], lhs / rhs.e[2]);
}

inline double dot(const vec3& lhs, const vec3& rhs) {
  return lhs.e[0] * rhs.e[0] + lhs.e[1] * rhs.e[1] + lhs.e[2] * rhs.e[2];
}

inline vec3 cross(const vec3& lhs, const vec3& rhs) {
  return vec3(lhs.e[1] * rhs.e[2] - lhs.e[2] * rhs.e[1], lhs.e[2] * rhs.e[0] - lhs.e[0] * rhs.e[2],
              lhs.e[0] * rhs.e[1] - lhs.e[1] * rhs.e[0]);
}

inline vec3 normalize(const vec3& v) { return v / v.length(); }

inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1, 1);
    if (p.norm() >= 1) continue;
    return p;
  }
}

inline vec3 random_unit_vector() {
  static double tau = 2.0 * std::acos(-1.0);
  auto y = random_double(-1, 1);
  auto r = std::sqrt(1.0 - y*y);
  auto theta = random_double(0, tau);
  return vec3(r * cos(theta), y, r * sin(theta));
}

inline vec3 random_in_hemisphere(const vec3& normal) {
  vec3 in_unit_sphere = random_in_unit_sphere();
  if (dot(in_unit_sphere, normal) > 0.0)  // In the same hemisphere as the normal
    return in_unit_sphere;
  else
    return -in_unit_sphere;
}

inline vec3 reflect(const vec3& v, const vec3& n) { return v - 2 * dot(v, n) * n; }

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
  auto cos_theta = std::fmin(dot(-uv, n), 1.0);
  auto r_out_perp = etai_over_etat * (uv + cos_theta * n);
  auto r_out_parallel = -std::sqrt(std::abs(1.0 - r_out_perp.norm())) * n;
  return r_out_perp + r_out_parallel;
}

inline vec3 random_in_unit_disk() {
  while (true) {
    auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.norm() >= 1) continue;
    return p;
  }
}

#endif  // VEC3_HPP
