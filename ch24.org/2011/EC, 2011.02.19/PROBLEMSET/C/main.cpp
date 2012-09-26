#include <string>

#include "grlib.h"
#include "contour.h"
#include "filters.h"

int main(int argc, char* argv[]) {
  gl::image img;
  img.from_pgm("data\\3.pgm");

  gl::image bw_img(img.size_x, img.size_y);
  threshold_filter(img, bw_img, 10);

  gl::recursive_contour center_circle;
  center_circle.search(gl::point(img.size_x / 2, img.size_y / 2), &bw_img);

  gl::point center = center_circle.mass_center();

  gl::point start = center;
  while (img.at(start) < 100) start.x += 1;

  for (int y = 0; y < img.size_y; ++y)
    for (int x = 0; x < img.size_x; ++x) {
      int c = img.at(x, y);
      assert(c >= 0);
      if (c < 60)
        img.at(x, y) = 0;
    }
      
  img.to_pgm("out.pgm");

  return 0;

  const double pi = 22.0 / 7.0;

  double rad_1 = 2 * pi / 360;  // ~0.017

  double angle = 0;
  double angle_delta = rad_1;
  
  double r = start.x - center.x;
  double r_delta = 0.032;

  int x = start.x, y = start.y;
  int last_x = x, last_y = y;
  while (x >= 0 && x < img.size_x && y >= 0 && y < img.size_y) {
    x = center.x + r * std::cos(angle);
    y = center.y + r * std::sin(angle);
    img.draw_line(gl::point(x, y), gl::point(last_x, last_y), 0);
    angle += angle_delta;
    r += r_delta;
    // angle_delta -= 0.005;
    // r_delta /= 1.05;
    last_x = x;
    last_y = y;
  }

  img.to_pgm("3-1.pgm");
  return 0;
}
