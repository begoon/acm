#ifndef _CONTOUR_H
#define _CONTOUR_H

#include "grlib.h"

namespace gl {

class recursive_contour: public contour {
 private:
  const image* image_;

  bool diagonal_mode;

  inline int count_neibours(const point& p) {
    int c =
      (image_->at(p.x - 1, p.y - 1) & 1) +
      (image_->at(p.x    , p.y - 1) & 1) +
      (image_->at(p.x + 1, p.y - 1) & 1) +
      (image_->at(p.x - 1, p.y    ) & 1) +
      (image_->at(p.x + 1, p.y    ) & 1) +
      (image_->at(p.x - 1, p.y + 1) & 1) +
      (image_->at(p.x    , p.y + 1) & 1) +
      (image_->at(p.x + 1, p.y + 1) & 1);
    return 8 - c;
  }

  bool in_contour(const point& p);
  void do_find_contour(const point& p);

  image blocked_points;
   
 public:
  recursive_contour() {}

  void search(point start, const image* a_image, bool thin_mode = false);

  void to_pgm(const std::string& filename);
};

class linear_contour : public contour {
 private:
  image* image_;

  bool diagonal_mode;

  inline int count_neibours(const point& p) {
    int c =
      (image_->at(p.x - 1, p.y - 1) & 1) +
      (image_->at(p.x    , p.y - 1) & 1) +
      (image_->at(p.x + 1, p.y - 1) & 1) +
      (image_->at(p.x - 1, p.y    ) & 1) +
      (image_->at(p.x + 1, p.y    ) & 1) +
      (image_->at(p.x - 1, p.y + 1) & 1) +
      (image_->at(p.x    , p.y + 1) & 1) +
      (image_->at(p.x + 1, p.y + 1) & 1);
    return 8 - c;
  }

  bool in_contour(const point& p);
  void do_find_contour(const point& p);

 public:
  linear_contour(image* a_image) : image_(a_image) {}

  void search();
   
  void to_pgm(const std::string& filename);
};

}  // gl

#endif
