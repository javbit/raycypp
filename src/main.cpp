#include "main.hpp"

#include <iomanip>
#include <iostream>
#include <random>
#include <string>

#include <glm/glm.hpp>
#include <png++/png.hpp>

#include "geom/hittable.hpp"
#include "geom/ray.hpp"
#include "geom/scene.hpp"
#include "geom/sphere.hpp"
#include "geom/triangle.hpp"
#include "geom/quadrangle.hpp"

#include "util/camera.hpp"
#include "util/perscam.hpp"
#include "util/orthcam.hpp"

const unsigned int WIDTH = 1024, HEIGHT = 512;
const unsigned int ITERATIONS = 128;

int main(int argc, char **argv) {
  // Version information
  std::cout << "Raycypp v0.4.2" << std::endl;

  // Random setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis;

  // Camera information

  const glm::vec3 origin(0.0, 0.0, 0.0);
  const glm::vec3 i(4.0, 0.0, 0.0);
  const glm::vec3 j(0.0, 2.0, 0.0);
  const glm::vec3 framepos(-2.0, -1, -1.0);

  // Camera pointer
  util::camera *cam = NULL;

  bool persp;
  if (argc < 2)
    persp = true;
  else {
    if (argv[1] == "-O" || argv[1] == "--orthographic")
      persp = false;
    else if (argv[1] == "-P" || argv[1] == "--perspective")
      persp = true;
    else persp = true;
  }

  if (persp)
    cam = new util::perscam(origin, framepos, i, j);
  else
    cam = new util::orthcam(glm::vec3(0, 0, -1), framepos, i, j);

  // Scene building
  std::vector<geom::hittable *> list;
  // list.push_back(new geom::sphere(glm::vec3(0, 0, -1), 0.5));
  // list.push_back(new geom::sphere(glm::vec3(0, -100.5, -1), 100));
  list.push_back(new geom::sphere(glm::vec3(-0.5, 0, -1), 0.1));
  list.push_back(new geom::sphere(glm::vec3(0.5, 0, -1), 0.1));
  list.push_back(new geom::sphere(glm::vec3(0, 0.5, -1), 0.1));
  list.push_back(new geom::triangle(glm::vec3(0.5, 0, -1),
                                    glm::vec3(-0.5, 0, -1),
                                    glm::vec3(0, 0.5, -1), -1, false));
  list.push_back(new geom::quadrangle(glm::vec3(-0.5, 0, -1),
                                      glm::vec3(0.5, 0, 0),
                                      glm::vec3(0, -0.5, -0.5), -1, false));
  geom::scene world(&list);

  // Ray tracing
  png::image<png::rgb_pixel> image(WIDTH, HEIGHT);
  for (unsigned int y = 0; y < image.get_height(); y++) {
    for (unsigned int x = 0; x < image.get_width(); x++) {
      glm::vec3 col(0, 0, 0);
      for (unsigned int n = 0; n < ITERATIONS; n++) {
        float u = (float(x) + dis(gen)) / float(WIDTH);
        float v = (float(y) + dis(gen)) / float(HEIGHT);
        geom::ray ray = cam->getray(u, v);
        col = col + color(ray, world);
      }
      image[image.get_height() - y - 1][x] = glm2png(col / float(ITERATIONS));
      std::cout << "\33[2K"
                << "Progress: " << std::setw(3)
                << int(float(x + y * WIDTH) / float(WIDTH * HEIGHT) * 100)
                << "%\r" << std::flush;
    }
  }

  // Clean up
  for (std::vector<geom::hittable *>::iterator it = list.begin();
       it != list.end(); ++it) {
    delete *it;
  }
  if (cam)
    delete cam;

  std::cout << "\33[2K"
            << "Done" << std::endl;
  // Write image
  image.write("render.png");
}

glm::vec3 color(const geom::ray &ray, const geom::scene &world) {
  geom::hitrecord rec;
  if (world.hit(ray, rec)) {
    return (rec.normal + glm::vec3(1, 1, 1)) / 2.0f;
  }
  // Background if there are no intersections.
  float t = 0.5f * (ray.direction().y + 1.0f);
  glm::vec3 color =
      (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) + t * glm::vec3(0.71, 0.49, 0.86);
  return color;
}

png::rgb_pixel glm2png(glm::vec3 color) {
  return png::rgb_pixel(png::byte(color.r * 0xFF), png::byte(color.g * 0xFF),
                        png::byte(color.b * 0xFF));
}

//  LocalWords:  Raycypp
