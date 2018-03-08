#ifndef CAMERA_H_
#define CAMERA_H_

#include "../geom/ray.hpp"
#include <glm/vec3.hpp>

namespace util {
class camera {
public:
  virtual geom::ray getray(float u, float v) = 0;
};
} // namespace util

#endif
