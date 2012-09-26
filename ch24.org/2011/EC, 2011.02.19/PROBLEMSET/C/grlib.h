#ifndef _GRLIB_H
#define _GRLIB_H

#include <string>
#include <vector>
#include <fstream>

#include <cstdlib>
#include <cmath>
#include <cassert>

#include "bwcolor.h"

namespace gl {

class point {
 public:
  int x, y;
   
  point(int ax = 0, int ay = 0) : x(ax), y(ay) {}
  point(const point& p) : x(p.x), y(p.y) {}
   
  inline bool operator== (const point& p) const { return x == p.x && y == p.y; }
  inline bool operator!= (const point& p) const { return x != p.x || y != p.y; }
  inline point operator- (const point& p) const { return point(x - p.x, y - p.y); }

  void rotate(float angle, const point& c);
};

class line {
 private:
  point _p1, _p2;
 public:
  line() : _p1(), _p2() {}
  line(const point& p1, const point& p2) : _p1(p1), _p2(p2) {}
  line(const line& _line) : _p1( _line._p1), _p2(_line._p2) {}
  line(int x1, int y1, int x2, int y2) : _p1(x1, y1), _p2(x2, y2) {}

  inline point& p1() { return _p1; }
  inline point& p2() { return _p2; }

  inline const point& p1() const { return _p1; }
  inline const point& p2() const { return _p2; }

  inline int sqr_length() const {
    return (_p1.x - _p2.x) * (_p1.x - _p2.x) + (_p1.y - _p2.y) * (_p1.y - _p2.y);
  }

  inline double length() const {
    return std::sqrt((double)sqr_length());
  }

  inline point center() const {
    return point((_p1.x + _p2.x) / 2, (_p1.y + _p2.y) / 2);
  }
};

class contour: public std::vector<point> {
 public:
  contour() {}
  contour(int size) { resize(size); }

  void rotate(float angle, const point& c);
  point mass_center() const;
};

class circle {
 public:
  point center;
  int radius;

  circle() : center(point()), radius(0) {}
  circle(const point& _center, int _radius) : center(_center), radius(_radius) {}
};

class canvas {
 public:

  virtual inline int get(int x, int y) = 0;
  virtual inline void put(int x, int y, int value) = 0;
  virtual inline int get_size_x() = 0;
  virtual inline int get_size_y() = 0;

  inline void put(const point& p, int value) { put(p.x, p.y, value); }
  inline int get(const point& p) { return get(p.x, p.y); }

  void draw_line(int start_x, int start_y, int end_x, int end_y, int color);
  inline void draw_line(const point& p1, const point& p2, int color) { draw_line(p1.x, p1.y, p2.x, p2.y, color); }
  inline void draw_line(const line& l, int color) { draw_line(l.p1(), l.p2(), color); }

  inline void draw_point(int x, int y, int color) { put(x, y, color); }
  inline void draw_point(const point& p, int color) { draw_point(p.x, p.y, color); }

  inline void draw_point_bold(const point& p, int color) {
    draw_point(p.x, p.y, color);
    draw_point(p.x+1, p.y+1, color);
    draw_point(p.x+1, p.y-1, color);
    draw_point(p.x-1, p.y+1, color);
    draw_point(p.x-1, p.y-1, color);
  }

  void draw_cross(int x, int y, int size, int color);
  inline void draw_cross(const point& p, int size, int color) { draw_cross(p.x, p.y, size, color); }

  void draw_x_cross(int x, int y, int size, int color);
  inline void draw_x_cross(const point& p, int size, int color) { draw_x_cross(p.x, p.y, size, color); }

  void draw_rect(int x1, int y1, int x2, int y2, int color);
  inline void draw_rect(const point& p1, const point& p2, int color) { draw_rect(p1.x, p1.y, p2.x, p2.y, color); }
  inline void draw_rect(const line& l, int color) { draw_rect(l.p1(), l.p2(), color); }

  void draw_circle(int cx, int cy, int radius, int color);
  void draw_circle_part(int x, int y, int x_center, int y_center, int color_code, float asp_ratio);
  inline void draw_circle(const point& c, int radius, int color) { draw_circle(c.x, c.y, radius, color); }
  inline void draw_circle(const circle& c, int color) { draw_circle(c.center, c.radius, color); }

  void rotate(float angle, const point& c);

  void draw_contour(const contour& cnt, int color);
  void draw_contour_spline(const contour& cnt, int step, int color);

  void flood_fill(point p, int current_color, int fill_color);
};

class image: public canvas {
 public:
  int size_x, size_y;
 private:
  typedef int pixel;
    
  pixel* buf;

  inline int raw_length() { return size_x * size_y * sizeof *buf; }

  void init() { buf = 0; }

 public:
  void clear() { std::memset(buf, 0, raw_length()); }
  void resize(int _size_x, int _size_y);
  void resize(const image& img) { resize(img.size_x, img.size_y); }
  void assign(const image& img);

  image() { init(); }
  image(int _size_x, int _size_y) { init(); resize(_size_x, _size_y); }
  image(const image& image) { init(); assign(image); }

  virtual ~image() { if(buf) delete[] buf; }

  inline pixel& at(int x, int y) {
    assert(!(x < 0 || x >= size_x || y < 0 || y >= size_y));
    return buf[ y * size_x + x ];
  }

  inline pixel& at(const point& p) { return at(p.x, p.y); }

  inline const pixel& at(int x, int y) const {
    assert(!(x < 0 || x >= size_x || y < 0 || y >= size_y));
    return buf[ y * size_x + x ];
  }

  inline const pixel& at(const point& p) const { return at(p.x, p.y); }

  virtual inline int get(int x, int y) {
    if (x < 0 || x >= size_x || y < 0 || y >= size_y) return -1;
    return buf[ y * size_x + x ];
  }

  virtual inline void put(int x, int y, int value) {
    if (x < 0 || x >= size_x || y < 0 || y >= size_y) return;
    buf[y * size_x + x] = value;
  }

  virtual inline int get_size_x() { return size_x; }
  virtual inline int get_size_y() { return size_y; }

  inline int count_neibours(int x, int y) const {
    return
        (at(x - 1, y - 1) & 1) +
        (at(x    , y - 1) & 1) +
        (at(x + 1, y - 1) & 1) +
        (at(x - 1, y    ) & 1) +
        (at(x + 1, y    ) & 1) +
        (at(x - 1, y + 1) & 1) +
        (at(x    , y + 1) & 1) +
        (at(x + 1, y + 1) & 1);
   }

   inline int count_neibours(const point& p) { return count_neibours(p.x, p.y); }

   inline image& operator= (const image& img) { assign(img); return *this; }

   void to_pgm(const std::string& filename);
   bool from_pgm(const std::string& filename);

   point center() { return line(0, 0, size_x + 1, size_y + 1).center(); }
};

class allocated_image: public canvas {
 private:
  unsigned char* buf_;

  int size_x_;
  int size_y_;
  int bytes_per_pixel_;
  int bits_per_pixel_;

  int scanline_length_;
  bool lower_left_corner_;
  
 public:
  allocated_image(int size_x, int size_y, int bits_per_pixel, int bytes_per_pixel, void* data);

  int size_x() { return size_x_; }
  int size_y() { return size_y_; }
  int bits_per_pixel() { return bits_per_pixel_; }
  int bytes_per_pixel() { return bytes_per_pixel_; }

  virtual inline int get(int x, int y);
  virtual inline void put(int x, int y, int value);

  virtual inline int get_size_x() { return size_x_; }
  virtual inline int get_size_y() { return size_y_; }
};

typedef std::vector<point> points;
typedef std::vector<line> lines;
typedef std::vector<int> indexes;

} // end of gl

#endif
