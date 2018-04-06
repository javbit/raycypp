#ifndef QUADRANGLE_H_
#define QUADRANGLE_H_

#include "ray.hpp"
#include "triangle.hpp"
#include <glm/vec3.hpp>

#include "hittable.hpp"

using namespace glm;

namespace geom {
class quadrangle : public hittable {
public:
  quadrangle();
  quadrangle(vec3 v1, vec3 v2, vec3 v3, vec3 v4, float normal = 1,
             bool onesided = false);
  quadrangle(vec3 corner, vec3 x, vec3 y, float normal = 1,
             bool onesided = false);
  void flip();
  virtual bool hit(const ray &ray, hitrecord &record, float t_min = 0.0f,
                   float t_max = INF) const;
  virtual bool bbox(util::aabb &box) const;

private:
  triangle t1_, t2_;
};
} // namespace geom

#endif
