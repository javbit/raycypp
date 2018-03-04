#ifndef HITTABLE_H_
#define HITTABLE_H_

#include <limits>


#include <glm/vec3.hpp>
#include "ray.hpp"

namespace geom {
  const float INF = std::numeric_limits<float>::infinity();

  struct hitrecord {
    float t;
    glm::vec3 point;
    glm::vec3 normal;
  };

  class hittable {
  public:
    virtual bool hit(const ray &ray,
                     hitrecord &record,
                     float t_min = 0.0f,
                     float t_max = INF) const = 0;
  };
}

#endif
