#include "projcam.hpp"
#include "../geom/ray.hpp"
#include "camera.hpp"
#include <glm/vec3.hpp>

namespace util {
projcam::projcam(glm::vec3 origin, glm::vec3 framepos, glm::vec3 framehoriz,
                 glm::vec3 framevert)
    : origin_(origin), framepos_(framepos), framehoriz_(framehoriz),
      framevert_(framevert) {}

geom::ray projcam::getray(float u, float v) {
  return geom::ray(origin_,
                   framepos_ + u * framehoriz_ + v * framevert_ - origin_);
}
} // namespace util
