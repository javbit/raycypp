#include "sphere.hpp"

#include <cmath>
#include <glm/glm.hpp>

namespace geom {
  sphere::sphere()
    : center_(glm::vec3(0.0, 0.0, 0.0))
    , radius_(0.0) {}

  sphere::sphere(glm::vec3 center, float radius)
    : center_(center)
    , radius_(radius) {}

  glm::vec3 sphere::center() const {
    return center_;
  }

  float sphere::radius() const {
    return radius_;
  }

  float sphere::intersect(const ray &ray) const {
    glm::vec3 oc = ray.origin() - center_;
    float a = glm::dot(ray.direction(), ray.direction());
    float b = 2.0f * glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - radius_ * radius_;
    float discriminant = b*b - 4*a*c;
    if (discriminant < 0)
      return -1.0f;
    return (-b - std::sqrt(discriminant)) / (2.0f * a);
  }
}
