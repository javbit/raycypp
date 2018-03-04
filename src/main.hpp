#ifndef MAIN_H_
#define MAIN_H_

#include <png++/rgb_pixel.hpp>
#include <glm/vec3.hpp>

#include "geom/ray.hpp"
#include "geom/sphere.hpp"
#include "geom/scene.hpp"

png::rgb_pixel color(const geom::ray &ray, const geom::scene &world);

#endif
