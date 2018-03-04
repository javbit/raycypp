#include "main.hpp"

#include <iostream>

#include <png++/png.hpp>
#include <glm/glm.hpp>

#include "geom/ray.hpp"
#include "geom/hittable.hpp"
#include "geom/sphere.hpp"
#include "geom/scene.hpp"

const unsigned int WIDTH = 1024, HEIGHT = 512;

int main() {
  std::cout << "Raycypp v0.2.0" << std::endl;

  const glm::vec3 origin(0.0, 0.0, 0.0);
  const glm::vec3 i(4.0, 0.0, 0.0);
  const glm::vec3 j(0.0, 2.0, 0.0);
  const glm::vec3 lower_left(-2.0, -1, -1.0);

  std::vector<geom::hittable *> list;
  list.push_back(new geom::sphere(glm::vec3(0, 0, -1), 0.5));
  list.push_back(new geom::sphere(glm::vec3(0, -100.5, -1), 100));
  geom::scene world(&list);

  png::image<png::rgb_pixel> image(WIDTH, HEIGHT);
  for (unsigned int y = 0; y < image.get_height(); y++) {
    for (unsigned int x = 0; x < image.get_width(); x++) {
      float u = float(x) / float(WIDTH);
      float v = float(y) / float(HEIGHT);

      geom::ray ray(origin, lower_left + u*i + v*j);
      image[image.get_height() - y - 1][x] = color(ray, world);
    }
  }

  for (std::vector<geom::hittable *>::iterator it = list.begin(); it != list.end(); ++it) {
    delete *it;
  }
  image.write("render.png");
}

png::rgb_pixel color(const geom::ray &ray, const geom::scene &world) {
  geom::hitrecord rec;
  if (world.hit(ray, rec)) {
    return png::rgb_pixel(png::byte((rec.normal.x + 1.0f) * 0.5f * 0xFF),
                          png::byte((rec.normal.y + 1.0f) * 0.5f * 0xFF),
                          png::byte((rec.normal.z + 1.0f) * 0.5f * 0xFF));
  }
  // Background if there are no intersections.
  float t = 0.5f * (ray.direction().y + 1.0f);
  glm::vec3 color = (1.0f - t)*glm::vec3(1.0, 1.0, 1.0)
    + t*glm::vec3(0.71, 0.49, 0.86);
  return png::rgb_pixel(png::byte(color.r * 0xFF),
                        png::byte(color.g * 0xFF),
                        png::byte(color.b * 0xFF));
}
