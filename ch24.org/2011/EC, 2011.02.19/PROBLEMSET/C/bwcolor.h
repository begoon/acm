#ifndef _BWCOLOR_H
#define _BWCOLOR_H

inline int toRGB(int color) {
  return (color << 16) | (color << 8) | color;
}

inline int fromRGB(int rgb) {
  return ((rgb & 0xff) * 77 + ((rgb >> 8 ) & 0xff) * 150 + ((rgb >> 16) & 0xff) * 28) >> 8;
}

inline int greyRGB(int rgb) {
  return toRGB(fromRGB(rgb));
}

#endif
