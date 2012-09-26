#ifndef _FILTERS_H
#define _FILTERS_H

#include "grlib.h"

void threshold_filter(const gl::image& from_img, gl::image& to_img, int threshold, const gl::circle& area = gl::circle());

#endif
