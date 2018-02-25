#ifndef MAIN_H_
#define MAIN_H_

#include <png++/rgb_pixel.hpp>
#include <glm/vec3.hpp>

#include "geom/ray.hpp"

png::rgb_pixel color(const geom::ray &ray);

#endif
