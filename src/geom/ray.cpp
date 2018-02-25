#include "ray.hpp"

#include <glm/glm.hpp>

namespace geom {
  ray::ray()
    : origin_(glm::vec3(0, 0, 0))
    , direction_(glm::vec3(0, 0, 0)) {}

  ray::ray(glm::vec3 origin, glm::vec3 direction)
    : origin_(origin)
    , direction_(glm::normalize(direction)) {}

  glm::vec3 ray::origin() const {
    return origin_;
  }

  glm::vec3 ray::direction() const {
    return direction_;
  }

  glm::vec3 ray::pointat(float t) const {
    return origin_ + direction_ * t;
  }
}
