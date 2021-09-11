#include "bvh.hpp"

#include <algorithm>

bvh_node::bvh_node(const std::vector<std::shared_ptr<hittable>>& src_objects, size_t start, size_t end, double time0,
                   double time1) {
  using std::begin;
  auto objects = src_objects;

  size_t axis = random_int(0, 2);
  auto comparator = [axis](const std::shared_ptr<hittable> a, const std::shared_ptr<hittable> b) {
    auto box_a_opt = a->bounding_box(0, 0);
    auto box_b_opt = b->bounding_box(0, 0);
    if (!box_a_opt || !box_b_opt) std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a_opt->min().e[axis] < box_b_opt->min().e[axis];
  };

  size_t object_span = end - start;
  if (object_span == 1) {
    left = right = objects[start];
  } else if (object_span == 2) {
    if (comparator(objects[start], objects[start + 1])) {
      left = objects[start];
      right = objects[start + 1];
    } else {
      left = objects[start + 1];
      right = objects[start];
    }
  } else {
    std::sort(begin(objects) + start, begin(objects) + end, comparator);

    auto mid = start + object_span / 2;
    left = std::make_shared<bvh_node>(objects, start, mid, time0, time1);
    right = std::make_shared<bvh_node>(objects, mid, end, time0, time1);
  }

  auto box_left_opt = left->bounding_box(time0, time1);
  auto box_right_opt = right->bounding_box(time0, time1);
  if (!box_left_opt || !box_right_opt) std::cerr << "No bounding box in bvh_node constructor.\n";

  box = surrounding_box(*box_left_opt, *box_right_opt);
}

bool bvh_node::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
  if (!box.hit(r, t_min, t_max)) return false;

  bool hit_left = left->hit(r, t_min, t_max, rec);
  bool hit_right = right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

  return hit_left || hit_right;
}

std::optional<aabb> bvh_node::bounding_box(double, double) const { return box; }
