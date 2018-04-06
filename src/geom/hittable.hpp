#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <limits>

#include "../util/aabb.hpp"
#include "ray.hpp"
#include <glm/vec3.hpp>

namespace geom {
const float INF = std::numeric_limits<float>::infinity();

struct hitrecord {
  float t;
  glm::vec3 point;
  glm::vec3 normal;
};

class hittable {
public:
  virtual bool hit(const ray &ray, hitrecord &record, float t_min = 0.0f,
                   float t_max = INF) const = 0;
  virtual bool bbox(util::aabb &box) const = 0;
};
} // namespace geom

#endif
