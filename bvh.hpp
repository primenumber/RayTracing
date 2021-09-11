#ifndef BVH_HPP
#define BVH_HPP
#include <memory>

#include "hittable.hpp"
#include "hittable_list.hpp"
#include "rtweekend.hpp"

class bvh_node : public hittable {
 public:
  bvh_node();
  bvh_node(const hittable_list& list, double time0, double time1)
      : bvh_node(list.get_objects(), 0, list.get_objects().size(), time0, time1) {}
  bvh_node(const std::vector<std::shared_ptr<hittable>>& src_objects, size_t start, size_t end, double time0,
           double time1);
  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
  virtual std::optional<aabb> bounding_box(double time0, double time1) const override;

 private:
  std::shared_ptr<hittable> left;
  std::shared_ptr<hittable> right;
  aabb box;
};

#endif  // BVH_HPP
