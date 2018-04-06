#include "aabb.hpp"

#include <glm/vec3.hpp>

#include "../geom/ray.hpp"

namespace util {
aabb::aabb() {}
aabb::aabb(const glm::vec3 &min, const glm::vec3 &max) : min_(min), max_(max) {}

glm::vec3 aabb::getMin() const { return min_; }
glm::vec3 aabb::getMax() const { return max_; }

bool aabb::hit(const geom::ray &ray, float t_min, float t_max) const {
  for (glm::length_t a = 0; a < min_.length(); ++a) {
    float invDir = 1.f / ray.direction()[a];
    float t0 = (min_[a] - ray.origin()[a]) * invDir;
    float t1 = (max_[a] - ray.origin()[a]) * invDir;
    if (invDir < 0.f)
      std::swap(t0, t1);
    t_min = t0 > t_min ? t0 : t_min;
    t_max = t1 < t_max ? t1 : t_max;
    if (t_max <= t_min)
      return false;
  }
  return true;
}

aabb aabbMerge(aabb const &lhs, aabb const &rhs) {
  glm::vec3 minp, maxp;
  for (glm::length_t d = 0; d < 3; ++d) {
    minp[d] =
        lhs.getMin()[d] < rhs.getMin()[d] ? lhs.getMin()[d] : rhs.getMin()[d];
    maxp[d] =
        lhs.getMax()[d] > rhs.getMax()[d] ? lhs.getMax()[d] : rhs.getMax()[d];
  }
  return aabb(minp, maxp);
}
} // namespace util
