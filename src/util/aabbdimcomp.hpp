#ifndef AABBDIMCOMP_H_
#define AABBDIMCOMP_H_

#include <iostream>

#include "../geom/hittable.hpp"

namespace util {
class aabbDimComp {
public:
  aabbDimComp(glm::length_t dim) : dim_(dim) {}
  bool operator()(const geom::hittable *lhs, const geom::hittable *rhs) const {
    aabb left, right;
    if (!lhs->bbox(left) || !rhs->bbox(right)) {
      std::cerr << "Failed to get bounding box!" << std::endl;
      return false;
    }
    return left.getMin()[dim_] < right.getMin()[dim_];
  }

private:
  glm::length_t dim_;
};
} // namespace util

#endif
