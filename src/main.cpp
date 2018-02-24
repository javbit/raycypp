#include <iostream>

#include <png++/png.hpp>

int main() {
  std::cout << "Raycypp v0.0.0" << std::endl;

  png::image<png::rgb_pixel> image(128, 128);
  for (unsigned char y = 0; y < image.get_height(); y++)
    for (unsigned char x = 0; x < image.get_width(); x++)
      image[y][x] = png::rgb_pixel(x, y, x + y);

  image.write("rgb.png");
}
