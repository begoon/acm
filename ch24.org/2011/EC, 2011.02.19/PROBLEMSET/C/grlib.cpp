#include "grlib.h"

#include <stack>
#include <vector>
#include <sstream>

namespace gl {

void point::rotate(float angle, const point& c) {
  float c_cos = std::cos(angle);
  float c_sin = std::sin(angle);

  int rx = (x - c.x) * c_cos - (y - c.y) * c_sin;
  int ry = (x - c.x) * c_sin + (y - c.y) * c_cos;
  x = rx + c.x;
  y = ry + c.y;
}

void contour::rotate(float angle, const point& c) {
  float c_cos = std::cos(angle);
  float c_sin = std::sin(angle);

  for (iterator i = begin(); i != end(); i++) {
    int rx = (i->x - c.x) * c_cos - (i->y - c.y) * c_sin;
    int ry = (i->x - c.x) * c_sin + (i->y - c.y) * c_cos;
    i->x = rx + c.x;
    i->y = ry + c.y;
  }
}

point contour::mass_center() const {
  double cx = 0, cy = 0;
  for (int i = 0; i < size(); ++i) {
    cx = (cx * i + at(i).x) / (i + 1);
    cy = (cy * i + at(i).y) / (i + 1);
  }
  return point(cx, cy);
}

void image::to_pgm(const std::string& filename) {
  std::ofstream os(filename.c_str(), std::ios_base::binary);
  os << "P5" << std::endl << size_x << " " << size_y << std::endl << "255" << std::endl;

  std::string pgm(size_x * size_y, 0);
  for (int i = 0; i < pgm.size(); ++i)
    pgm[i] = buf[i] & 0xFF;

  os.write(pgm.data(), pgm.size());
}

bool image::from_pgm(const std::string& filename) {
  std::ifstream is(filename.c_str(), std::ios_base::binary);

  std::string header;
  int colors;

  is >> header >> size_x >> size_y >> colors >> std::ws;

  if (header != "P5") return false;

  std::vector<char> raw(size_x * size_y, 0);
  is.read(&raw[0], raw.size());

  resize(size_x, size_y);
  for (int i = 0; i < size_x * size_y; ++i) {
    buf[i] = raw[i] & 0xff;
    assert(buf[i] >= 0);
  }

  return true;
}

void image::resize(int _size_x, int _size_y) {
  if (buf) delete[] buf;

  size_x = _size_x;
  size_y = _size_y;

  buf = new pixel[ size_x * size_y ];

  clear();
}

void image::assign(const image& img) {
  resize(img.size_x, img.size_y);
  std::memcpy(buf, img.buf, raw_length());
}

void canvas::draw_line(int start_x, int start_y, int end_x, int end_y, int color) {
  int x = start_x;
  int y = start_y;

  int delta_x = x - end_x;
  int delta_y = y - end_y;

  int inc_x = delta_x > 0 ? -1 : (delta_x == 0 ? 0 : 1);
  int inc_y = delta_y > 0 ? -1 : (delta_y == 0 ? 0 : 1);

  delta_x = std::abs(delta_x);
  delta_y = std::abs(delta_y);

  int x_err = 0, y_err = 0;

  int distance = delta_x > delta_y ? delta_x : delta_y;

  for (int i = 0; i <= distance + 1; i++) {
    put(x, y, color);

    x_err += delta_x;
    y_err += delta_y;

    if (x_err > distance) {
      x_err -= distance;
      x += inc_x;
    }

    if (y_err > distance) {
      y_err -= distance;
      y += inc_y;
    }
  }
}

void canvas::draw_cross(int x, int y, int size, int color) {
  draw_line(x - size, y, x + size, y, color);
  draw_line(x, y - size, x, y + size, color);
}

void canvas::draw_x_cross(int x, int y, int size, int color) {
  draw_line(x - size, y - size, x + size, y + size, color);
  draw_line(x - size, y + size, x + size, y - size, color);
}

void canvas::draw_rect(int x1, int y1, int x2, int y2, int color) {
  draw_line(x1, y1, x2, y1, color);
  draw_line(x2, y1, x2, y2, color);
  draw_line(x2, y2, x1, y2, color);
  draw_line(x1, y2, x1, y1, color);
}

void canvas::draw_circle(int x_center, int y_center, int radius, int color_code) {
  int x, y, delta;
  float asp_ratio = 1.0;
  y = radius;
  delta = 3 - 2 * radius;

  for (x = 0; x < y;)  {
    draw_circle_part(x, y, x_center, y_center, color_code, asp_ratio);
    if (delta < 0)
      delta += 4 * x + 6;
    else {
      delta += 4 * (x - y) + 10;
      y--;
    }
    x++;
  }

  x = y;
  if (y)
    draw_circle_part(x, y, x_center, y_center, color_code, asp_ratio);
}

void canvas::draw_circle_part(int x, int y, int x_center, int y_center, int color_code, float asp_ratio) {
  int start_y = y * asp_ratio;
  int end_y = (y + 1) * asp_ratio;
  int start_x = x * asp_ratio;
  int end_x = (x + 1) * asp_ratio;

  for (int x1 = start_x; x1 < end_x; ++x1) {
    put(x1 + x_center, y + y_center, color_code);
    put(x1 + x_center, y_center - y, color_code);
    put(x_center - x1, y + y_center, color_code);
    put(x_center - x1, y_center - y, color_code);
  }

  for (int y1 = start_y; y1 < end_y; ++y1) {
    put(y1 + x_center, x + y_center, color_code);
    put(y1 + x_center, y_center - x, color_code);
    put(x_center - y1, x + y_center, color_code);
    put(x_center - y1, y_center - x, color_code);
  }
}

void canvas::rotate(float angle, const point& c) {
  float c_cos = std::cos(angle);
  float c_sin = std::sin(angle);

  int size_x = get_size_x();
  int size_y = get_size_y();

  for (int y = 0; y < size_y; y++)
    for (int x = 0; x < size_x; x++) {
      if (get(x, y) == 0) continue;
      int rx = (x - c.x) * c_cos - (y - c.y) * c_sin;
      int ry = (x - c.x) * c_sin + (y - c.y) * c_cos;
      if (rx < 0 || rx >= size_x || ry < 0 || ry >= size_y) continue;
      put(rx + c.x, ry + c.y, 0xFF);
    }
}

void canvas::draw_contour(const contour& cnt, int color) {
  for (contour::const_iterator i = cnt.begin(); i != cnt.end(); i++)
    draw_point(*i, color);
}

void canvas::draw_contour_spline(const contour& cnt, int step, int color) {
  int i;
  for (i = 0; i < (int)cnt.size() - step; i += step)
    draw_line(cnt[i], cnt[i+step], color);
  draw_line(cnt[i], cnt[ cnt.size() - 1 ], color);
}

void canvas::flood_fill(point p, int current_color, int fill_color) {
  if (current_color == fill_color) return;

  std::stack<point> points;

  int span_y;
  bool span_left, span_right;

  points.push(p);

  int size_x = get_size_x();
  int size_y = get_size_y();

  while (!points.empty()) {
    p = points.top();
    points.pop();

    span_y = p.y;

    while (get(p.x, span_y) == current_color && span_y >= 0) span_y--;

    span_y++;

    span_left = span_right = false;

    while (get(p.x, span_y) == current_color && span_y < size_y){
      put(p.x, span_y, fill_color);

      if (!span_left && p.x > 0 && get(p.x - 1, span_y) == current_color) {
        points.push(gl::point(p.x - 1, span_y));
        span_left = true;
      } else if (span_left && p.x > 0 && get(p.x - 1, span_y) != current_color)
        span_left = false;

      if (!span_right && p.x < size_x - 1 && get(p.x + 1, span_y) == current_color) {
        points.push(gl::point(p.x + 1, span_y));
        span_right = true;
      } else if (span_right && p.x < size_x - 1 && get(p.x + 1,span_y) != current_color)
        span_right = false;

      span_y++;
    }
  }
}

allocated_image::allocated_image(int size_x, int size_y, int bits_per_pixel, int bytes_per_pixel, void* data) :
    size_x_(size_x), size_y_(size_y), bits_per_pixel_(bits_per_pixel), bytes_per_pixel_(bytes_per_pixel),
    buf_((unsigned char*) data) 
{
  scanline_length_ = size_x * bytes_per_pixel;
  if (scanline_length_ & 0x3)
    scanline_length_ = (scanline_length_ + 4) & ~0x03;

  lower_left_corner_ = size_y > 0;

  if (size_y < 0)
    size_y = -size_y;
}

inline int allocated_image::get(int x, int y) {
  if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) return -1;

  if (lower_left_corner_)
    y = size_y_ - y;

  unsigned char* point = buf_ + y * scanline_length_ + x * bytes_per_pixel_;

  switch (bits_per_pixel_ / 8) {
    case 1:
      return point[0];
    case 2:
      return (point[0] << 8) | point[1];
    case 3:
      return (point[0] << 16) | (point[1] << 8) | point[2];
    case 4:
      return (point[0] << 24) | (point[1] << 16) |(point[2] << 8) | point[3];
  }

  return -1;
}

inline void allocated_image::put(int x, int y, int value) {
  if (x < 0 || x >= size_x_ || y < 0 || y >= size_y_) return;

  if (lower_left_corner_)
    y = size_y_ - y;

  unsigned char* point = buf_ + y * scanline_length_ + x * bytes_per_pixel_;

  switch (bits_per_pixel_ / 8) {
    case 1:
       *point = value;
         break;
      case 2:
         *point++ = (value >> 8) & 0xff;
         *point++ = value & 0xff;
         break;
      case 3:
         *point++ = (value >> 16) & 0xff;
         *point++ = (value >> 8) & 0xff;
         *point = value & 0xff;
         break;
      case 4:
         *point++ = (value >> 16) & 0xff;
         *point++ = (value >> 8) & 0xff;
         *point++ = value & 0xff;
         *point = 0;
         break;
   }
}

} // of namespace gl

