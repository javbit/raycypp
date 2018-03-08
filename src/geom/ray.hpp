#ifndef RAY_H_
#define RAY_H_

#include <glm/glm.hpp>

namespace geom {
class ray {
public:
  ray();
  ray(const glm::vec3 origin_, const glm::vec3 direction_);
  glm::vec3 origin() const;
  glm::vec3 direction() const;
  glm::vec3 pointat(float t) const;

private:
  glm::vec3 origin_, direction_;
};
} // namespace geom

#endif
