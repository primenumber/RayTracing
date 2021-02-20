#ifndef VEC3_HPP
#define VEC3_HPP

#include <cmath>
#include <iostream>

class vec3 {
 public:
  vec3() : e{0,0,0} {}
  vec3(double e0, double e1, double e2) : e{e0,e1,e2} {}

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

  vec3& operator/=(const double rhs) {
    return *this *= 1. / rhs;
  }

  double length() const {
    return std::sqrt(norm());
  }

  double norm() const {
    return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
  }
 public:
  double e[3];
};

using point3 = vec3; // 3D point
using color = vec3; // RGB color

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

inline vec3 operator*(const vec3& lhs, const double rhs) {
  return rhs * lhs;
}

inline vec3 operator/(const vec3& lhs, const double rhs) {
  return (1. / rhs) * lhs;
}

inline double dot(const vec3& lhs, const vec3& rhs) {
  return lhs.e[0] * rhs.e[0]
    + lhs.e[1] * rhs.e[1]
    + lhs.e[2] * rhs.e[2];
}

inline vec3 cross(const vec3& lhs, const vec3& rhs) {
  return vec3(
      lhs.e[1] * rhs.e[2] - lhs.e[2] * rhs.e[1],
      lhs.e[2] * rhs.e[0] - lhs.e[0] * rhs.e[2],
      lhs.e[0] * rhs.e[1] - lhs.e[1] * rhs.e[0]);
}

inline vec3 normalize(const vec3& v) {
  return v / v.length();
}

#endif // VEC3_HPP
