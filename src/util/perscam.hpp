#ifndef PERSCAM_H_
#define PERSCAM_H_

#include "../geom/ray.hpp"
#include "camera.hpp"
#include <glm/vec3.hpp>

namespace util {
class perscam : public camera {
public:
  perscam(glm::vec3 origin, glm::vec3 framepos, glm::vec3 framehoriz,
          glm::vec3 framevert);
  virtual geom::ray getray(float u, float v);

private:
  glm::vec3 origin_, framepos_, framehoriz_, framevert_;
};
} // namespace util

#endif
