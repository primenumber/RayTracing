#ifndef COLOR_HPP
#define COLOR_HPP

#include "vec3.hpp"

#include <algorithm>
#include <iostream>

void write_color(std::ostream& os, const color& pixel_color, size_t samples_per_pixel) {
  auto r = pixel_color.x();
  auto g = pixel_color.y();
  auto b = pixel_color.z();

  auto scale = 1.0 / samples_per_pixel;
  r = std::sqrt(r * scale);
  g = std::sqrt(g * scale);
  b = std::sqrt(b * scale);

  os << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
     << static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
     << static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << '\n';
}

#endif // COLOR_HPP
