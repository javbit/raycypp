#include "scene.hpp"

#include <vector>

#include "hittable.hpp"
#include "ray.hpp"

namespace geom {
  scene::scene() : objects_(NULL) {}
  scene::scene(std::vector<hittable *> *objects) : objects_(objects) {}

  bool scene::hit(const ray &ray, hitrecord &record, float t_min, float t_max) const {
    hitrecord tmprec;
    bool hitp = false;
    float closest = t_max;
    for (std::vector<hittable *>::iterator it = objects_->begin(); it != objects_->end(); ++it) {
      if ((*it)->hit(ray, tmprec, t_min, closest)) {
        hitp = true;
        closest = tmprec.t;
        record = tmprec;
      }
    }
    return hitp;
  }
}
