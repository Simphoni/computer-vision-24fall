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
      // tmp = std::max(tmp, 0.0f);
      // tmp = std::min(tmp, 1.0f);
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

  // DONE: scale all the pixels at the specified channel
  int w = im.w;
  int h = im.h;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      im(x, y, c) *= v;
    }
  }
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
      float V = max(r, g, b);
      float m = min(r, g, b);
      float C = V - m;
      float H, S;
      if (C == 0) {
        H = 0;
      } else if (V == r) {
        H = (g - b) / C;
      } else if (V == g) {
        H = (b - r) / C + 2;
      } else {
        H = (r - g) / C + 4;
      }
      if (H < 0) {
        H = H / 6 + 1;
      } else {
        H /= 6;
      }
      if (V == 0) {
        S = 0;
      } else {
        S = C / V;
      }
      im(x, y, 0) = H;
      im(x, y, 1) = S;
      im(x, y, 2) = V;
    }
  }
}

// HW0 #7
// Image& im: input image to be modified in-place
void hsv_to_rgb(Image &im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // DONE: Convert all pixels from HSV format to RGB format

  int ch = im.c;
  int h = im.h;
  int w = im.w;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      float H = im(x, y, 0);
      float S = im(x, y, 1);
      float V = im(x, y, 2);
      float C = V * S;
      float X = (1 - fabs(fmod(6 * H, 2) - 1)) * C;
      float m = V - C;
      float R = 0, G = 0, B = 0;
      if (H < 1.0 / 6) {
        R = C;
        G = X;
      } else if (H < 2.0 / 6) {
        R = X;
        G = C;
      } else if (H < 3.0 / 6) {
        G = C;
        B = X;
      } else if (H < 4.0 / 6) {
        G = X;
        B = C;
      } else if (H < 5.0 / 6) {
        R = X;
        B = C;
      } else {
        R = C;
        B = X;
      }
      im(x, y, 0) = R + m;
      im(x, y, 1) = G + m;
      im(x, y, 2) = B + m;
    }
  }
}

void sRGB2Linear(float &R, float &G, float &B) {
  R = R > 0.04045 ? pow((R + 0.055) / 1.055, 2.4) : R / 12.92;
  G = G > 0.04045 ? pow((G + 0.055) / 1.055, 2.4) : G / 12.92;
  B = B > 0.04045 ? pow((B + 0.055) / 1.055, 2.4) : B / 12.92;
}

void Linear2sRGB(float &R, float &G, float &B) {
  R = R > 0.0031308 ? 1.055 * pow(R, 1 / 2.4) - 0.055 : 12.92 * R;
  G = G > 0.0031308 ? 1.055 * pow(G, 1 / 2.4) - 0.055 : 12.92 * G;
  B = B > 0.0031308 ? 1.055 * pow(B, 1 / 2.4) - 0.055 : 12.92 * B;
}

// HW0 #9
// Image& im: input image to be modified in-place
void rgb_to_lch(Image &im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // DONE: Convert all pixels from RGB format to LCH format

  for (int y = 0; y < im.h; y++) {
    for (int x = 0; x < im.w; x++) {
      float R = im(x, y, 0);
      float G = im(x, y, 1);
      float B = im(x, y, 2);
      // PNG stores in sRGB, first convert to linear RGB
      sRGB2Linear(R, G, B);
      // convert to XYZ with D65 reference white, using matrix from
      // http://www.brucelindbloom.com/index.html?Eqn_RGB_XYZ_Matrix.html
      float X = 0.4124564 * R + 0.3575761 * G + 0.1804375 * B;
      float Y = 0.2126729 * R + 0.7151522 * G + 0.0721750 * B;
      float Z = 0.0193339 * R + 0.1191920 * G + 0.9503041 * B;
      // convert to L*u*v*
      float compare = pow(6.0 / 29, 3);
      // Yn for D65 is 1.0, Y/Yn=Y
      float Lstar =
          Y > compare ? 116 * pow(Y, 1.0 / 3) - 16 : Y * pow(29.0 / 3, 3);
      float ustar = 13 * Lstar * ((4 * X) / (X + 15 * Y + 3 * Z) - 0.2009);
      float vstar = 13 * Lstar * ((9 * Y) / (X + 15 * Y + 3 * Z) - 0.4610);
      float C = sqrt(ustar * ustar + vstar * vstar);
      float H = atan2(vstar, ustar);
      if (X == 0) { // Y and Z are also 0
        Lstar = C = H = 0;
      }
      im(x, y, 0) = Lstar;
      im(x, y, 1) = C;
      im(x, y, 2) = H;
    }
  }
}

// HW0 #9
// Image& im: input image to be modified in-place
void lch_to_rgb(Image &im) {
  assert(im.c == 3 && "only works for 3-channels images");

  // DONE: Convert all pixels from LCH format to RGB format

  for (int y = 0; y < im.h; y++) {
    for (int x = 0; x < im.w; x++) {
      float Lstar = im(x, y, 0);
      float C = im(x, y, 1);
      float H = im(x, y, 2);
      float ustar = C * cos(H);
      float vstar = C * sin(H);
      float u = ustar / (13 * Lstar) + 0.2009;
      float v = vstar / (13 * Lstar) + 0.4610;
      float Y =
          Lstar > 8 ? pow((Lstar + 16) / 116, 3) : Lstar * pow(3.0 / 29, 3);
      float X = Y * (9 * u) / (4 * v);
      float Z = Y * (12 - 3 * u - 20 * v) / (4 * v);
      // convert to linear RGB
      float R = 3.2404542 * X - 1.5371385 * Y - 0.4985314 * Z;
      float G = -0.9692660 * X + 1.8760108 * Y + 0.0415560 * Z;
      float B = 0.0556434 * X - 0.2040259 * Y + 1.0572252 * Z;
      // convert to sRGB
      Linear2sRGB(R, G, B);
      if (Lstar == 0) {
        R = G = B = 0;
      }
      im(x, y, 0) = R;
      im(x, y, 1) = G;
      im(x, y, 2) = B;
    }
  }
}

// Implementation of member functions
void Image::clamp(void) { clamp_image(*this); }
void Image::shift(int c, float v) { shift_image(*this, c, v); }
void Image::scale(int c, float v) { scale_image(*this, c, v); }

void Image::HSVtoRGB(void) { hsv_to_rgb(*this); }
void Image::RGBtoHSV(void) { rgb_to_hsv(*this); }
void Image::LCHtoRGB(void) { lch_to_rgb(*this); }
void Image::RGBtoLCH(void) { rgb_to_lch(*this); }
