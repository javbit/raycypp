#ifndef MAIN_H_
#define MAIN_H_

#include <png++/rgb_pixel.hpp>
#include <glm/vec3.hpp>

#include "geom/ray.hpp"
#include "geom/sphere.hpp"
#include "geom/scene.hpp"

glm::vec3 color(const geom::ray &ray, const geom::scene &world);
png::rgb_pixel glm2png(glm::vec3);

#endif
