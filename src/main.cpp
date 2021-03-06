#include "main.hpp"

#define PERSPECTIVEP true

#define SPHERES 10000

const unsigned int WIDTH = 1024, HEIGHT = 512;
const unsigned int ITERATIONS = 128;

int main(int argc, char **argv) {
  // Version information
  std::cout << "Raycypp v0.5.0" << std::endl;

  // Random setup
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis;
  std::uniform_real_distribution<float> loc(-5.f, 5.f);
  std::uniform_real_distribution<float> rad(0.01f, 0.1f);

  // Camera information
  const glm::vec3 origin(0.0, 0.0, 0.0);
  const glm::vec3 i(4.0, 0.0, 0.0);
  const glm::vec3 j(0.0, 2.0, 0.0);
  const glm::vec3 framepos(-2.0, -1, -1.0);

  // Camera pointer
  util::camera *cam = NULL;

  if (PERSPECTIVEP)
    cam = new util::perscam(origin, framepos, i, j);
  else
    cam = new util::orthcam(glm::vec3(0, 0, -1), framepos, i, j);

  /* Model reading */
  std::vector<geom::hittable *> list;
  std::string filename = argc < 2 ? "models/teapot.obj" : argv[1];
  std::cout << "Rendering " << filename << std::endl;
  std::ifstream model(filename);
  char type;
  float a, b, c;
  std::vector<glm::vec3> vertices;
  vertices.push_back(glm::vec3()); // Dummy
  while (model >> type >> a >> b >> c) {
    if (type == 'v')
      vertices.push_back(glm::vec3(a, b, c - 1.5f));
    else if (type == 'f') {
      int i = int(a), j = int(b), k = int(c);
      list.push_back(
          new geom::triangle(vertices.at(i), vertices.at(j), vertices.at(k)));
    }
  }

  geom::scene world(&list);

  // Ray tracing
  png::image<png::rgb_pixel> image(WIDTH, HEIGHT);
#pragma omp parallel for
  for (unsigned int y = 0; y < image.get_height(); y++) {
#pragma omp parallel for
    for (unsigned int x = 0; x < image.get_width(); x++) {
      glm::vec3 col(0, 0, 0);
      for (unsigned int n = 0; n < ITERATIONS; n++) {
        float u = (float(x) + dis(gen)) / float(WIDTH);
        float v = (float(y) + dis(gen)) / float(HEIGHT);
        geom::ray ray = cam->getray(u, v);
        col = col + color(ray, world);
      }
      image[image.get_height() - y - 1][x] = glm2png(col / float(ITERATIONS));
      // std::cout << "\33[2K"
      //           << "Progress: " << std::setw(3)
      //           << int(float(x + y * WIDTH) / float(WIDTH * HEIGHT) * 100)
      //           << "%\r" << std::flush;
    }
  }

  // Clean up
  // for (std::vector<geom::hittable *>::iterator it = list.begin();
  //      it != list.end(); ++it) {
  //   delete *it;
  // }
  // if (cam)
  //   delete cam;

  // std::cout << "\33[2K"
  //           << "Done" << std::endl;
  // Write image
  image.write("render.png");
}

glm::vec3 color(const geom::ray &ray, const geom::scene &world, int iter) {
  geom::hitrecord rec;
  if (world.hit(ray, rec) && iter < 5) {
    glm::vec3 target = rec.point + rec.normal + random_in_unit_sphere();
    return glm::sqrt(0.33f * color(geom::ray(rec.point, target - rec.point),
                                   world, iter + 1));
    // return (rec.normal + 1.f) / 2.0f;
  }
  // Background if there are no intersections.
  float t = 0.5f * (ray.direction().y + 1.0f);
  return (1.0f - t) * glm::vec3(1.0, 1.0, 1.0) +
         t * glm::vec3(0.71, 0.49, 0.86);
}

png::rgb_pixel glm2png(glm::vec3 color) {
  return png::rgb_pixel(png::byte(color.r * 0xFF), png::byte(color.g * 0xFF),
                        png::byte(color.b * 0xFF));
}

glm::vec3 random_in_unit_sphere() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<float> dis;

  glm::vec3 p;
  do {
    p = 2.f * glm::vec3(dis(gen), dis(gen), dis(gen)) -
        glm::vec3(1.f, 1.f, 1.f);
  } while (glm::dot(p, p) >= 1);
  return p;
}
//  LocalWords:  Raycypp
