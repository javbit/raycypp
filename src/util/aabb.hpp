#ifndef AABB_H_
#define AABB_H_

#include <glm/vec3.hpp>

#include "../geom/ray.hpp"

namespace util {
const float INF = std::numeric_limits<float>::infinity();
class aabb {
public:
  aabb();
  aabb(const glm::vec3 &min, const glm::vec3 &max);

  glm::vec3 getMin() const;
  glm::vec3 getMax() const;

  bool hit(const geom::ray &ray, float t_min = 0.f, float t_max = INF) const;

private:
  glm::vec3 min_, max_;
};

aabb aabbMerge(aabb const &lhs, aabb const &rhs);
} // namespace util

#endif
