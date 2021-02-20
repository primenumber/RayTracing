#include <iostream>

#include "rtweekend.hpp"

#include "color.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "camera.hpp"
#include "material.hpp"

color ray_color(const ray& r, const hittable& world, int32_t depth) {
  hit_record rec;

  if (depth <= 0) {
    return color(0,0,0);
  }

  if (world.hit(r, 0.001, infinity, rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth-1);
    return color(0,0,0);
  }
  vec3 unit_direction = normalize(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0-t) * color(1.0, 1.0, 1.0) + t*color(0.5, 0.7, 1.0);
}

int main() {
  // Image

  const auto aspect_ratio = 16.0 / 9.0;
  const ptrdiff_t image_width = 400;
  const ptrdiff_t image_height = static_cast<ptrdiff_t>(image_width / aspect_ratio);
  const size_t samples_per_pixel = 100;
  const int32_t max_depth = 50;

  // World

  hittable_list world;

  auto material_ground = std::make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = std::make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left   = std::make_shared<dielectric>(1.5);
  auto material_right  = std::make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);

  world.add(std::make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(std::make_shared<sphere>(point3( 0.0,    0.0, -1.0),   0.5, material_center));
  world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
  world.add(std::make_shared<sphere>(point3(-1.0,    0.0, -1.0), -0.45, material_left));
  world.add(std::make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

  // Camera
  
  camera cam(point3(-2,2,1), point3(0,0,-1), vec3(0,1,0), 20.0, aspect_ratio);

  // Render

  std::cout<<"P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (ptrdiff_t j = image_height-1; j >= 0; --j) {
    std::cerr << "\rScanlines ramaining: " << j << ' ' << std::flush;
    for (ptrdiff_t i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (size_t s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width-1);
        auto v = (j + random_double()) / (image_height-1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      write_color(std::cout, pixel_color, samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
