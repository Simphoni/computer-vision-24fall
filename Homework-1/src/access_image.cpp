#include <algorithm>
#include <cstring>

#include "image.h"

// HW0 #1
// const Image& im: input image
// int x,y: pixel coordinates
// int ch: channel of interest
// returns the 0-based location of the pixel value in the data array
int pixel_address(const Image &im, int x, int y, int ch) {
  // TODO: calculate and return the index
  // CHW format
  return ch * im.w * im.h + y * im.w + x;
}

// HW0 #1
// const Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
// returns the value of the clamped pixel at channel ch
float get_clamped_pixel(const Image &im, int x, int y, int ch) {
  // TODO: clamp the coordinates and return the correct pixel value

  int h = im.h;
  int w = im.w;
  int c = im.c;
  x = std::max(x, 0);
  x = std::min(x, w - 1);
  y = std::max(y, 0);
  y = std::min(y, h - 1);
  ch = std::max(ch, 0);
  ch = std::min(ch, c - 1);
  return im(x, y, ch);
}

// HW0 #1
// Image& im: input image
// int x,y,ch: pixel coordinates and channel of interest
void set_pixel(Image &im, int x, int y, int c, float value) {
  // TODO: Only set the pixel to the value if it's inside the image
  int h = im.h;
  int w = im.w;
  int ch = im.c;
  if (x >= 0 && x < w && y >= 0 && y < h && c >= 0 && c < ch) {
    im(x, y, c) = value;
  }
}

// HW0 #2
// Copies an image
// Image& to: destination image
// const Image& from: source image
void copy_image(Image &to, const Image &from) {
  // allocating data for the new image
  to.data = (float *)calloc(from.w * from.h * from.c, sizeof(float));
  to.c = from.c;
  to.h = from.h;
  to.w = from.w;

  memcpy(to.data, from.data, from.w * from.h * from.c * sizeof(float));
}
