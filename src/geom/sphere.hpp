#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/vec3.hpp>
#include "ray.hpp"

namespace geom {
  class sphere {
  public:
    sphere();
    sphere(glm::vec3 center, float radius);
    glm::vec3 center() const;
    float radius() const;
    float intersect(const ray &ray) const;
  private:
    glm::vec3 center_;
    float radius_;
  };
}

#endif
