#include "image.h"
#include <cmath>

using namespace std;

// HW2 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neighbor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)
  // DONE: Your code here

  return clamped_pixel((int)round(x), (int)round(y), c);
}

// HW2 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const {
  // Since you are inside class Image you can
  // use the member function pixel(a,b,c)

  // DONE: Your code here

  float xl = floor(x), xr = ceil(x);
  float yl = floor(y), yr = ceil(y);
  float ret = 0;
  ret += (xr - x) * (yr - y) * clamped_pixel((int)xl, (int)yl, c);
  ret += (x - xl) * (yr - y) * clamped_pixel((int)xr, (int)yl, c);
  ret += (xr - x) * (y - yl) * clamped_pixel((int)xl, (int)yr, c);
  ret += (x - xl) * (y - yl) * clamped_pixel((int)xr, (int)yr, c);
  return ret;
}

// HW2 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image &im, int w, int h) {
  Image ret(w, h, im.c);

  // DONE: Your code here

  for (int ch = 0; ch < im.c; ch++) {
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        ret.set_pixel(x, y, ch,
                      im.pixel_nearest((x + 0.5) * im.w / w - 0.5,
                                       (y + 0.5) * im.h / h - 0.5, ch));
      }
    }
  }

  return ret;
}

// HW2 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image &im, int w, int h) {
  Image ret(w, h, im.c);
  // DONE: Your code here

  for (int ch = 0; ch < im.c; ch++) {
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        ret.set_pixel(x, y, ch,
                      im.pixel_bilinear((x + 0.5) * im.w / w - 0.5,
                                        (y + 0.5) * im.h / h - 0.5, ch));
      }
    }
  }

  return ret;
}
