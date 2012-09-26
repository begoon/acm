#include "filters.h"

#include <algorithm>
#include <utility>
#include <numeric>
#include <vector>

void threshold_filter(const gl::image& from_img, gl::image& to_img, int threshold, const gl::circle& area) {
  int start_offset_x = std::max(area.center.x - area.radius, 0);
  int start_offset_y = std::max(area.center.y - area.radius, 0);

  int end_offset_x = std::min(area.center.x + area.radius, from_img.size_x);
  int end_offset_y = std::min(area.center.y + area.radius, from_img.size_y);

  if (!area.radius) {
    start_offset_x = start_offset_y = 0;
    end_offset_x = from_img.size_x;
    end_offset_y = from_img.size_y;
  }

  int radius_square = area.radius * area.radius;

  for (int y = start_offset_y; y < end_offset_y; y++) {
    int square_y = (y - area.center.y) * (y - area.center.y);

    for (int x = start_offset_x; x < end_offset_x; x++) {
      int square_x = (x - area.center.x) * (x - area.center.x);

      if (!area.radius || square_y + square_x < radius_square)
        to_img.at(x, y) = from_img.at(x, y) < threshold ? 0x00 : 0xFF;
      else
        to_img.at(x, y) = 0;
    }
  }
}
