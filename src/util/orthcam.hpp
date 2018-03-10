#ifndef ORTHCAM_H_
#define ORTHCAM_H_

#include "../geom/ray.hpp"
#include "camera.hpp"
#include <glm/vec3.hpp>

namespace util {
class orthcam : public camera {
public:
  orthcam(glm::vec3 direction, glm::vec3 framepos, glm::vec3 framehoriz,
          glm::vec3 framevert);
  virtual geom::ray getray(float u, float v);

private:
  glm::vec3 direction_, framepos_, framehoriz_, framevert_;
};
} // namespace util

#endif
