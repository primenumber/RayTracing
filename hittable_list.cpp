#include "hittable_list.hpp"

bool hittable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  hit_record temp_rec;
  bool hit_anything = false;
  auto closest_so_far = t_max;
  for (const auto& object : objects) {
    if (object->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      rec = temp_rec;
    }
  }

  return hit_anything;
}

std::optional<aabb> hittable_list::bounding_box(double time0, double time1) const {
  if (objects.empty()) return std::nullopt;

  std::optional<aabb> output_box;

  for (const auto& object : objects) {
    if (auto temp_box = object->bounding_box(time0, time1); temp_box) {
      if (!output_box)
        output_box = temp_box;
      else
        output_box = surrounding_box(*output_box, *temp_box);
    } else {
      return std::nullopt;
    }
  }

  return output_box;
}
