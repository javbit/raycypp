#include "sphere.hpp"

#include <cmath>
#include <glm/glm.hpp>

#include "hittable.hpp"

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

  bool sphere::hit(const ray &ray,
                   hitrecord &record,
                   float t_min,
                   float t_max) const {
    // Quadratic equation.
    glm::vec3 oc = ray.origin() - center_;
    float a = glm::dot(ray.direction(), ray.direction());
    float b = glm::dot(oc, ray.direction());
    float c = glm::dot(oc, oc) - radius_ * radius_;
    float discriminant = b*b - a*c;
    if (discriminant < 0)
      return false;
    float sign[2] = {-1.0f, 1.0f};
    for (int i = 0; i < 2; i++) {
      float t = (-b + sign[i] * std::sqrt(discriminant)) / a;
      if (t_min < t && t < t_max) {
        record.t = t;
        record.point = ray.pointat(t);
        record.normal = glm::normalize(record.point - center_);
        return true;
      }
    }
    return false;
  }
}
