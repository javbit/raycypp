#ifndef SPHERE_H_
#define SPHERE_H_

#include "ray.hpp"
#include <glm/vec3.hpp>

#include "hittable.hpp"

namespace geom {
class sphere : public hittable {
public:
  sphere();
  sphere(glm::vec3 center, float radius);
  glm::vec3 center() const;
  float radius() const;
  virtual bool hit(const ray &ray, hitrecord &record, float t_min = 0.0f,
                   float t_max = INF) const;
  virtual bool bbox(util::aabb &box) const;

private:
  glm::vec3 center_;
  float radius_;
};
} // namespace geom

#endif
