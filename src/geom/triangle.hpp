#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "ray.hpp"
#include <glm/vec3.hpp>

#include "hittable.hpp"

namespace geom {

class triangle : public hittable {
public:
  triangle();
  triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, float normal = 1,
           bool onesided = false);
  void flip();
  virtual bool hit(const ray &ray, hitrecord &record, float t_min = 0.0f,
                   float t_max = INF) const;
  virtual bool bbox(util::aabb &box) const;

private:
  glm::vec3 v1_, v2_, v3_, normal_;
  bool onesided_;
};
} // namespace geom

#endif
