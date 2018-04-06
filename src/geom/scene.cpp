#include "scene.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

#include "../util/aabb.hpp"
#include "../util/aabbdimcomp.hpp"
#include "hittable.hpp"
#include "ray.hpp"

namespace geom {
scene::scene() : root_(NULL) {}
scene::scene(std::vector<hittable *> *objects)
    : root_(genbvh(*objects, objects->begin(), objects->end())) {}

bool scene::hit(const ray &ray, hitrecord &record, float t_min,
                float t_max) const {
  return root_ ? root_->hit(ray, record, t_min, t_max) : false;
}

bool scene::bbox(util::aabb &box) const {
  if (!root_)
    return false;
  root_->bbox(box);
  return true;
}

hittable *scene::genbvh(std::vector<hittable *> &objects,
                        std::vector<hittable *>::iterator left,
                        std::vector<hittable *>::iterator right,
                        glm::length_t dim) {
  if (left == right)
    return *left;
  util::aabbDimComp comp(dim);
  std::sort(left, right, comp);
  bvhnode *node = new bvhnode();
  node->left = genbvh(objects, left, left + (right - left) / 2, (dim + 1) % 3);
  node->right =
      genbvh(objects, left + (right - left) / 2 + 1, right, (dim + 1) % 3);
  if (!(node->left || node->right)) {
    std::cerr << "Failed to create sub-hittables!" << std::endl;
    return NULL;
  }
  util::aabb lbox, rbox;
  bool lboxp = node->left && node->left->bbox(lbox);
  bool rboxp = node->right && node->right->bbox(rbox);
  if (lboxp && rboxp)
    node->box = util::aabbMerge(lbox, rbox);
  else
    node->box = lboxp ? lbox : rbox;
  return node;
}

scene::bvhnode::bvhnode() : box(), left(NULL), right(NULL) {}

bool scene::bvhnode::hit(const ray &ray, hitrecord &record, float t_min,
                         float t_max) const {
  if (!box.hit(ray, t_min, t_max))
    return false;

  hitrecord lrec, rrec;
  bool lhitp = left ? left->hit(ray, record, t_min, t_max) : false;
  bool rhitp = right ? right->hit(ray, record, t_min, t_max) : false;

  if (lhitp && rhitp) {
    record = lrec.t < rrec.t ? lrec : rrec;
    return true;
  } else if (lhitp) {
    record = lrec;
    return true;
  } else if (rhitp) {
    record = rrec;
    return true;
  } else {
    return false;
  }
}

bool scene::bvhnode::bbox(util::aabb &box) const {
  box = this->box;
  return true;
}
} // namespace geom
