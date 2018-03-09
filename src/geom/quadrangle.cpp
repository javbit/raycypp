#include "quadrangle.hpp"

#include "ray.hpp"
#include "triangle.hpp"
#include <glm/glm.hpp>

#include "hittable.hpp"

using namespace glm;

namespace geom {
quadrangle::quadrangle() : t1_(), t2_() {}
quadrangle::quadrangle(vec3 v1, vec3 v2, vec3 v3, vec3 v4, float normal,
                       bool onesided)
    : t1_(v1, v2, v3, normal, onesided), t2_(v3, v2, v4, normal, onesided) {}
quadrangle::quadrangle(vec3 corner, vec3 x, vec3 y, float normal, bool onesided)
    : t1_(corner, corner + x, corner + y, normal, onesided),
      t2_(corner + y, corner + x, corner + x + y, normal, onesided) {}

void quadrangle::flip() {
  t1_.flip();
  t2_.flip();
}

bool quadrangle::hit(const ray &ray, hitrecord &record, float t_min,
                     float t_max) const {
  hitrecord rec1, rec2;
  bool hit1, hit2;
  hit1 = t1_.hit(ray, rec1, t_min, t_max);
  hit2 = t2_.hit(ray, rec2, t_min, t_max);
  if (hit1 && hit2) {
    if (rec1.t < rec2.t)
      record = rec1;
    else
      record = rec2;
  } else if (hit1)
    record = rec1;
  else if (hit2)
    record = rec2;
  else
    return false;

  return true;
}
} // namespace geom
