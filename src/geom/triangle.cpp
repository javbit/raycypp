#include "triangle.hpp"

#include <cmath>

#include "ray.hpp"
#include <glm/glm.hpp>

#include "hittable.hpp"

namespace geom {
const float EPSILON = 1.0e-6f;

triangle::triangle()
    : v1_(glm::vec3(1, 0, 0)), v2_(glm::vec3(0, 1, 0)), v3_(glm::vec3(0, 0, 1)),
      normal_(glm::normalize(glm::vec3(1, 1, 1))), onesided_(false) {}

triangle::triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, float normal,
                   bool onesided)
    : v1_(v1), v2_(v2), v3_(v3),
      normal_(glm::normalize(normal * glm::cross(v2 - v1, v3 - v1))),
      onesided_(onesided) {}

void triangle::flip() { normal_ *= -1.0; }

bool triangle::hit(const ray &ray, hitrecord &record, float t_min,
                   float t_max) const {
  // M Ö ller – Trumbore ray-triangle intersection algorithm
  glm::vec3 x, y, h, s, q;
  float a, f, u, v;

  // Triangle edges
  x = v2_ - v1_;
  y = v3_ - v1_;

  // Calculating the determinant (a) to see if the ray intersects the plane the
  // triangle is in
  h = glm::cross(ray.direction(), y);
  a = glm::dot(x, h);

  // If triangle is meant to be one-sided, then cull if on the wrong side.
  if (onesided_) {
    if (a < EPSILON)
      return false;
  } else {
    if (std::abs(a) < EPSILON)
      return false;
  }

  // Inverse of determinant
  f = 1.f / a;

  // Finding the uv-co-ordinates of the intersection
  s = ray.origin() - v1_;
  u = f * glm::dot(s, h);

  // Check if u is a valid barycentric co-ordinate
  if (u < 0 || 1 < u)
    return false;

  // Finding other barycentric co-ordinate
  q = glm::cross(s, x);
  v = f * glm::dot(ray.direction(), q);

  // Check if v is a valid barycentric co-ordinate
  if (v < 0 || 1 < u + v)
    return false;

  // At this point we can calculate t.
  float t = f * glm::dot(y, q);

  // Check if t in required range
  if (t < t_min || t_max < t)
    return false;

  // Set hit record
  record.t = t;
  record.normal = normal_;
  record.point = ray.pointat(t);

  // Signify hit
  return true;
}

bool triangle::bbox(util::aabb &box) const {
  glm::vec3 minp, maxp;
  for (glm::length_t d = 0; d < v1_.length(); ++d) {
    float min, max;
    min = max = v1_[d];
    min = v2_[d] < min ? v2_[d] : min;
    max = v2_[d] > max ? v2_[d] : max;
    min = v3_[d] < min ? v3_[d] : min;
    max = v3_[d] > max ? v3_[d] : max;
    minp[d] = min;
    maxp[d] = max;
  }
  box = util::aabb(minp, maxp);
  return true;
}
} // namespace geom
