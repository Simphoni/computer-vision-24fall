#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstring>

#include "image.h"

using namespace std;

// HW0 #3
// const Image& im: input image
// return the corresponding grayscale image
Image rgb_to_grayscale(const Image &im) {
  assert(im.c == 3);         // only accept RGB images
  Image gray(im.w, im.h, 1); // create a new grayscale image (note: 1 channel)

  int h = im.h;
  int w = im.w;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float r = im(x, y, 0);
      float g = im(x, y, 1);
      float b = im(x, y, 2);
      gray(x, y, 0) = 0.299 * r + 0.587 * g + 0.114 * b;
    }
  }
  return gray;
}

// Example function that changes the color of a grayscale image
Image grayscale_to_rgb(const Image &im, float r, float g, float b) {
  assert(im.c == 1);
  Image rgb(im.w, im.h, 3);

  for (int q2 = 0; q2 < im.h; q2++)
    for (int q1 = 0; q1 < im.w; q1++) {
      rgb(q1, q2, 0) = r * im(q1, q2);
      rgb(q1, q2, 1) = g * im(q1, q2);
      rgb(q1, q2, 2) = b * im(q1, q2);
    }

  return rgb;
}

// HW0 #4
// Image& im: input image to be modified in-place
// int c: which channel to shift
// float v: how much to shift
void shift_image(Image &im, int c, float v) {
  assert(c >= 0 && c < im.c); // needs to be a valid channel
  int w = im.w;
  int h = im.h;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float tmp = im(x, y, c) + v;
      tmp = std::max(tmp, 0.0f);
      tmp = std::min(tmp, 1.0f);
      im(x, y, c) = tmp;
    }
  }
}

// HW0 #8
// Image& im: input image to be modified in-place
// int c: which channel to scale
// float v: how much to scale
void scale_image(Image &im, int c, float v) {
  assert(c >= 0 && c < im.c); // needs to be a valid channel

  // TODO: scale all the pixels at the specified channel

  NOT_IMPLEMENTED();
}

// HW0 #5
// Image& im: input image to be modified in-place
void clamp_image(Image &im) {
  int ch = im.c;
  int w = im.w;
  int h = im.h;
  for (int c = 0; c < ch; c++) {
    for (int y = 0; y < h; y++) {
      for (int x = 0; x < w; x++) {
        float tmp = im(x, y, c);
        tmp = std::max(tmp, 0.0f);
        tmp = std::min(tmp, 1.0f);
        im(x, y, c) = tmp;
      }
    }
  }
}

// These might be handy
float max(float a, float b, float c) { return max({a, b, c}); }

float min(float a, float b, float c) { return min({a, b, c}); }

// HW0 #6
// Image& im: input image to be modified in-place
void rgb_to_hsv(Image &im) {
  assert(im.c == 3 && "only works for 3-channels images");

  int ch = im.c;
  int h = im.h;
  int w = im.w;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float r = im(x, y, 0);
      float g = im(x, y, 1);
      float b = im(x, y, 2);
      float M = max(r, g, b);
      float m = min(r, g, b);
      float C = M - m;
      float H, S, V;
      V = M;
      if (C == 0) {
        H = 0;
      } else if (M == r) {
        H = fmod((g - b) / C, 6);
      } else if (M == g) {
        H = (b - r) / C + 2;
      } else {
        H = (r - g) / C + 4;
      }
      H *= 60;
      if (H < 0) {
        H += 360;
      }
      if (M == 0) {
        S = 0;
      } else {
        S = C / M;
      }
      im(x, y, 0) = H / 360;
      im(x, y, 1) = S;
      im(x, y, 2) = V;
    }
  }
}

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image &im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // TODO: Convert all pixels from HSV format to RGB format

  NOT_IMPLEMENTED();
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image &im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // TODO: Convert all pixels from RGB format to LCH format

  NOT_IMPLEMENTED();
}

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image &im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // TODO: Convert all pixels from LCH format to RGB format

  NOT_IMPLEMENTED();
}

// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this, c, v); }
void Image::scale(int c, float v) { scale_image(*this, c, v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
