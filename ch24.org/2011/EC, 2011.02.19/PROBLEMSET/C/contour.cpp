#include "contour.h"

#include <sstream>
#include <iomanip>

namespace gl {

bool recursive_contour::in_contour(const point& p) {
  for (int i = size() - 1; i >= 0; i--)
    if (at(i) == p) return true;
  return false;
}

void recursive_contour::do_find_contour(const point& p) {
  if (image_->at(p) == 0) return;

  #ifdef CONTOUR_TRACE
  {
    static int i = 0;
    i += 1;
    if (!(i % 500)) {
      image io(image_->size_x, image_->size_y);
      io.draw_contour(*this, 0xff);
      std::ostringstream fmt;
      fmt << "current-" << std::setw(5) << std::setfill('0') << i << ".pgm";
      io.to_pgm(fmt.str());
    }
  }
  #endif

  if (blocked_points.at(p)) return;

  if (count_neibours(p) == 0)return;

  push_back(p);
   
  blocked_points.at(p) = 1;

  if (p.x > 1)
    do_find_contour(point(p.x - 1, p.y));

  if (p.y > 1)
    do_find_contour(point(p.x, p.y - 1));

  if (p.y < image_->size_y - 2)
    do_find_contour(point(p.x, p.y + 1));

  if (p.x < image_->size_x - 2)
    do_find_contour(point(p.x + 1, p.y));

  if (diagonal_mode) {
    if (p.y > 1 && p.x > 1)
      do_find_contour(point(p.x - 1, p.y - 1));

    if (p.y < image_->size_y - 2 && p.x > 1)
      do_find_contour(point(p.x - 1, p.y + 1));

    if (p.y < image_->size_y - 2 && p.x < image_->size_x - 2)
      do_find_contour(point(p.x + 1, p.y + 1));

    if (p.y > 1 && p.x < image_->size_x - 2)
      do_find_contour(point(p.x + 1, p.y - 1));
  }
}

void recursive_contour::search(point start, const image* a_image, bool thin_mode) {
  image_ = a_image;
   
  blocked_points.resize(image_->size_x, image_->size_y);

  diagonal_mode = thin_mode;
   
  int start_point_color = image_->at(start);
   
  while (image_->at(start) == start_point_color && start.y < image_->size_y - 1)
    start.y++;

  if (image_->at(start) == 0)
    start.y--;

  blocked_points.clear();
  if (thin_mode)
    for (int y = start.y - 1; y <= start.y + 1; y++)
      blocked_points.at(start.x + 1, y) = 1;

  clear();
  reserve(10000);

  do_find_contour(start);

  push_back(start);
}

void recursive_contour::to_pgm(const std::string& filename) {
  image i(image_->size_x, image_->size_y);
  i.draw_contour(*this, 0xFF);
  i.to_pgm(filename);
}

void linear_contour::search() {
  clear();
  reserve(30000);

  for (int y = 1; y < image_->size_y - 1; y++)
    for (int x = 1; x < image_->size_x - 1; x++) {
      int nc = image_->count_neibours(x, y);
      if (nc > 0 && nc < 8)
         push_back(point(x, y));
    }
}

void linear_contour::to_pgm(const std::string& filename) {
  image i(image_->size_x, image_->size_y);
  i.draw_contour(*this, 0xFF);
  i.to_pgm(filename);
}

}  // gl
