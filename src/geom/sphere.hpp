#ifndef SPHERE_H_
#define SPHERE_H_

#include <glm/vec3.hpp>
#include "ray.hpp"

#include "hittable.hpp"

namespace geom {
  class sphere : public hittable {
  public:
    sphere();
    sphere(glm::vec3 center, float radius);
    glm::vec3 center() const;
    float radius() const;
    virtual bool hit(const ray &ray,
                     hitrecord &record,
                     float t_min = 0.0f,
                     float t_max = INF) const;
  private:
    glm::vec3 center_;
    float radius_;
  };
}

#endif
