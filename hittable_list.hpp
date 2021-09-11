#ifndef HITTABLE_LIST_HPP
#define HITTABLE_LIST_HPP

#include <memory>
#include <vector>

#include "hittable.hpp"

class hittable_list : public hittable {
 public:
  hittable_list() {}
  explicit hittable_list(std::shared_ptr<hittable> object) { add(object); }

  void clear() { objects.clear(); }
  void add(std::shared_ptr<hittable> object) { objects.push_back(object); }
  const std::vector<std::shared_ptr<hittable>>& get_objects() const { return objects; }

  virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;
  virtual std::optional<aabb> bounding_box(double time0, double time1) const override;

 private:
  std::vector<std::shared_ptr<hittable>> objects;
};

#endif  // HITTABLE_LIST_HPP
