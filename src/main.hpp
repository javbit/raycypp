#ifndef MAIN_H_
#define MAIN_H_

#include <glm/vec3.hpp>
#include <png++/rgb_pixel.hpp>

#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#include <glm/glm.hpp>
#include <png++/png.hpp>

#include "geom/hittable.hpp"
#include "geom/quadrangle.hpp"
#include "geom/ray.hpp"
#include "geom/scene.hpp"
#include "geom/sphere.hpp"
#include "geom/triangle.hpp"

#include "util/camera.hpp"
#include "util/orthcam.hpp"
#include "util/perscam.hpp"

glm::vec3 color(const geom::ray &ray, const geom::scene &world, int iter = 0);
png::rgb_pixel glm2png(glm::vec3);
glm::vec3 random_in_unit_sphere();

#endif
