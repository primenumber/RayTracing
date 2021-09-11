#include <iostream>

#include "bvh.hpp"
#include "camera.hpp"
#include "color.hpp"
#include "hittable_list.hpp"
#include "material.hpp"
#include "moving_sphere.hpp"
#include "rtweekend.hpp"
#include "sphere.hpp"

color ray_color(const ray& r, const hittable& world, int32_t depth) {
  hit_record rec;

  if (depth <= 0) {
    return color(0, 0, 0);
  }

  if (world.hit(r, 0.001, infinity, rec)) {
    ray scattered;
    color attenuation;
    if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
      return attenuation * ray_color(scattered, world, depth - 1);
    return color(0, 0, 0);
  }
  vec3 unit_direction = normalize(r.direction());
  auto t = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
  hittable_list world;

  auto ground_material = std::make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(std::make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  hittable_list objects;

  for (int32_t a = -11; a < 11; ++a) {
    for (int32_t b = -11; b < 11; ++b) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        material_ptr sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = std::make_shared<lambertian>(albedo);
          auto center2 = center + vec3(0, random_double(0, 0.5), 0);
          objects.add(std::make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = std::make_shared<metal>(albedo, fuzz);
          objects.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = std::make_shared<dielectric>(1.5);
          objects.add(std::make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = std::make_shared<dielectric>(1.5);
  objects.add(std::make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = std::make_shared<lambertian>(color(0.4, 0.2, 0.1));
  objects.add(std::make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = std::make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  objects.add(std::make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  world.add(std::make_shared<bvh_node>(objects, 0.0, 1.0));

  return world;
}

int main() {
  // Image

  const auto aspect_ratio = 16.0 / 9.0;
  const ptrdiff_t image_width = 400;
  const ptrdiff_t image_height = static_cast<ptrdiff_t>(image_width / aspect_ratio);
  const size_t samples_per_pixel = 100;
  const int32_t max_depth = 50;

  // World

  auto world = random_scene();

  // Camera

  point3 lookfrom(13, 2, 3);
  point3 lookat(0, 0, 0);
  vec3 vup(0, 1, 0);
  auto dist_to_focus = 10.0;
  auto aperture = 0.1;

  camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (ptrdiff_t j = image_height - 1; j >= 0; --j) {
    std::cerr << "\rScanlines ramaining: " << j << ' ' << std::flush;
    std::vector<color> output_pixels(image_width);
#pragma omp parallel for schedule(guided)
    for (ptrdiff_t i = 0; i < image_width; ++i) {
      color pixel_color(0, 0, 0);
      for (size_t s = 0; s < samples_per_pixel; ++s) {
        auto u = (i + random_double()) / (image_width - 1);
        auto v = (j + random_double()) / (image_height - 1);
        ray r = cam.get_ray(u, v);
        pixel_color += ray_color(r, world, max_depth);
      }
      output_pixels[i] = pixel_color;
    }
    for (ptrdiff_t i = 0; i < image_width; ++i) {
      write_color(std::cout, output_pixels[i], samples_per_pixel);
    }
  }

  std::cerr << "\nDone.\n";
  return 0;
}
