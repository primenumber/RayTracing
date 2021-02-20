#include <iostream>

int main() {
  // Image

  const ptrdiff_t image_height = 256;
  const ptrdiff_t image_width = 256;

  // Render

  std::cout<<"P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (ptrdiff_t j = image_height-1; j >= 0; --j) {
    std::cerr << "\rScanlines ramaining: " << j << ' ' << std::flush;
    for (ptrdiff_t i = 0; i < image_width; ++i) {
      auto r = double(i) / (image_width-1);
      auto g = double(j) / (image_height-1);
      auto b = 0.25;

      uint32_t ir = static_cast<uint32_t>(255.999 * r);
      uint32_t ig = static_cast<uint32_t>(255.999 * g);
      uint32_t ib = static_cast<uint32_t>(255.999 * b);

      std::cout << ir << ' ' << ig << ' ' << ib << "\n";
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
