#include <iostream>

#include "color.hpp"
#include "vec3.hpp"

int main() {
  // Image

  const ptrdiff_t image_height = 256;
  const ptrdiff_t image_width = 256;

  // Render

  std::cout<<"P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (ptrdiff_t j = image_height-1; j >= 0; --j) {
    std::cerr << "\rScanlines ramaining: " << j << ' ' << std::flush;
    for (ptrdiff_t i = 0; i < image_width; ++i) {
      color pixel_color(double(i) / (image_width-1), double(j) / (image_height-1), 0.25);
      write_color(std::cout, pixel_color);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
