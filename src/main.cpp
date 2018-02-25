#include "main.hpp"

#include <iostream>

#include <png++/png.hpp>
#include <glm/glm.hpp>

#include "geom/ray.hpp"

const unsigned int WIDTH = 828, HEIGHT = 512;

png::rgb_pixel color(const geom::ray &ray) {
  float t = 0.5f * (ray.direction().y + 1.0f);
  glm::vec3 color = (1.0f - t)*glm::vec3(1.0, 1.0, 1.0)
    + t*glm::vec3(0.71, 0.49, 0.86);
  return png::rgb_pixel(png::byte(color.r * 0xFF),
                        png::byte(color.g * 0xFF),
                        png::byte(color.b * 0xFF));
}

int main() {
  std::cout << "Raycypp v0.0.0" << std::endl;

  const glm::vec3 origin(0.0, 0.0, 0.0);
  const glm::vec3 i(1.0, 0.0, 0.0);
  const glm::vec3 j(0.0, 1.0, 0.0);
  const glm::vec3 lower_left(-0.5, -0.5, -1.0);

  png::image<png::rgb_pixel> image(WIDTH, HEIGHT);
  for (unsigned int y = 0; y < image.get_height(); y++) {
    for (unsigned int x = 0; x < image.get_width(); x++) {
      float u = float(x) / float(WIDTH);
      float v = float(y) / float(HEIGHT);

      geom::ray ray(origin, lower_left + u*i + v*j);
      image[y][x] = color(ray);
    }
  }

  image.write("rgb.png");
}
