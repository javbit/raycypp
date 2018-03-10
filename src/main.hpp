#ifndef MAIN_H_
#define MAIN_H_

#include <glm/vec3.hpp>
#include <png++/rgb_pixel.hpp>

#include "geom/ray.hpp"
#include "geom/scene.hpp"
#include "geom/sphere.hpp"

glm::vec3 color(const geom::ray &ray, const geom::scene &world, int iter = 0);
png::rgb_pixel glm2png(glm::vec3);
glm::vec3 random_in_unit_sphere();

#endif
