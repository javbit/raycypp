#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "hittable.hpp"
#include "ray.hpp"

namespace geom {
class scene : public hittable {
public:
  scene();
  scene(std::vector<hittable *> *objects);
  virtual bool hit(const ray &ray, hitrecord &record, float t_min = 0,
                   float t_max = INF) const;
  virtual bool bbox(util::aabb &box) const;

private:
  hittable *root_;

  hittable *genbvh(std::vector<hittable *> &objects,
                   std::vector<hittable *>::iterator left,
                   std::vector<hittable *>::iterator right,
                   glm::length_t dim = 0);

  class bvhnode : public hittable {
  public:
    bvhnode();
    virtual bool hit(const ray &ray, hitrecord &record, float t_min = 0,
                     float t_max = INF) const;
    virtual bool bbox(util::aabb &box) const;

    util::aabb box;
    hittable *left, *right;
  };
};
} // namespace geom

#endif
