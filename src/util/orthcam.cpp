#include "orthcam.hpp"
#include "../geom/ray.hpp"
#include "camera.hpp"
#include <glm/vec3.hpp>

namespace util {
orthcam::orthcam(glm::vec3 direction, glm::vec3 framepos, glm::vec3 framehoriz,
                 glm::vec3 framevert)
    : direction_(glm::normalize(direction)), framepos_(framepos),
      framehoriz_(framehoriz), framevert_(framevert) {}

geom::ray orthcam::getray(float u, float v) {
  return geom::ray(framepos_ + u * framehoriz_ + v * framevert_, direction_);
}
} // namespace util
