#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "hittable.hpp"
#include "ray.hpp"

namespace geom {
  class scene : public hittable {
  public:
    scene();
    scene(std::vector<hittable *> *objects);
    virtual bool hit(const ray &ray,
                     hitrecord &record,
                     float t_min = 0,
                     float t_max = INF) const;
  private:
    std::vector<hittable *> *objects_;
  };
}

#endif
