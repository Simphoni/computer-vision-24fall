#include "image.h"
#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M_PI 3.14159265358979323846

// HW2 #2.1
// Image& im: image to L1-normalize
void l1_normalize(Image &im) {
  // DONE: Normalize each channel

  double sum = 0;
  for (int ch = 0; ch < im.c; ch++) {
    for (int y = 0; y < im.h; y++) {
      for (int x = 0; x < im.w; x++) {
        sum += im(x, y, ch);
      }
    }
  }
  for (int ch = 0; ch < im.c; ch++) {
    for (int y = 0; y < im.h; y++) {
      for (int x = 0; x < im.w; x++) {
        if (sum != 0) {
          im(x, y, ch) /= sum;
        } else {
          im(x, y, ch) = 1. / (im.w * im.h);
        }
      }
    }
  }
}

// HW2 #2.1
// int w: size of filter
// returns the filter Image of size WxW
Image make_box_filter(int w) {
  assert(w % 2); // w needs to be odd

  // DONE: Implement the filter
  float val = 1.0 / (w * w);
  Image ret(w, w, 1);
  for (int y = 0; y < w; y++) {
    for (int x = 0; x < w; x++) {
      ret(x, y) = val;
    }
  }
  return ret;
}

// HW2 #2.2
// const Image&im: input image
// const Image& filter: filter to convolve with
// bool preserve: whether to preserve number of channels
// returns the convolved image
Image convolve_image(const Image &im, const Image &filter, bool preserve) {
  assert(filter.c == 1);
  Image ret;
  // This is the case when we need to use the function clamped_pixel(x,y,c).
  // Otherwise you'll have to manually check whether the filter goes out of
  // bounds

  // DONE: Make sure you set the sizes of ret properly. Use ret=Image(w,h,c) to
  // reset ret
  ret = Image(im.w, im.h, preserve ? im.c : 1);
  // DONE: Do the convolution operator
  for (int ch = 0; ch < im.c; ch++) {
    for (int y = 0; y < im.h; y++) {
      for (int x = 0; x < im.w; x++) {
        float sum = 0;
        for (int fy = 0; fy < filter.h; fy++) {
          for (int fx = 0; fx < filter.w; fx++) {
            int ix = x - filter.w / 2 + fx;
            int iy = y - filter.h / 2 + fy;
            sum += im.clamped_pixel(ix, iy, ch) * filter(fx, fy);
          }
        }
        if (preserve) {
          ret(x, y, ch) = sum;
        } else {
          if (ch == 0) {
            ret(x, y) = sum;
          } else {
            ret(x, y) += sum;
          }
        }
      }
    }
  }

  return ret;
}

// HW2 #2.3
// returns basic 3x3 high-pass filter
Image make_highpass_filter() {
  // DONE: Implement the filter
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = 0;
  im(0, 1, 0) = -1;
  im(0, 2, 0) = 0;
  im(1, 0, 0) = -1;
  im(1, 1, 0) = 4;
  im(1, 2, 0) = -1;
  im(2, 0, 0) = 0;
  im(2, 1, 0) = -1;
  im(2, 2, 0) = 0;
  return im;
}

// HW2 #2.3
// returns basic 3x3 sharpen filter
Image make_sharpen_filter() {
  // DONE: Implement the filter
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = 0;
  im(0, 1, 0) = -1;
  im(0, 2, 0) = 0;
  im(1, 0, 0) = -1;
  im(1, 1, 0) = 5;
  im(1, 2, 0) = -1;
  im(2, 0, 0) = 0;
  im(2, 1, 0) = -1;
  im(2, 2, 0) = 0;
  return im;
}

// HW2 #2.3
// returns basic 3x3 emboss filter
Image make_emboss_filter() {
  // DONE: Implement the filter
  Image im = Image(3, 3, 1);
  im(0, 0, 0) = -2;
  im(0, 1, 0) = -1;
  im(0, 2, 0) = 0;
  im(1, 0, 0) = -1;
  im(1, 1, 0) = 1;
  im(1, 2, 0) = 1;
  im(2, 0, 0) = 0;
  im(2, 1, 0) = 1;
  im(2, 2, 0) = 2;
  return im;
}

// HW2 #2.4
// float sigma: sigma for the gaussian filter
// returns basic gaussian filter
Image make_gaussian_filter(float sigma) {
  // DONE: Implement the filter
  int dim = round(sigma * 6);
  if (dim % 2 == 0) {
    dim++;
  }
  Image im = Image(dim, dim, 1);

  double coef = 1. / (M_PI * 2 * sigma * sigma);
  for (int y = 0; y < dim; y++) {
    for (int x = 0; x < dim; x++) {
      int dx = x - dim / 2;
      int dy = y - dim / 2;
      im(x, y) = coef * exp(-(dx * dx + dy * dy) / (2 * sigma * sigma));
    }
  }
  return im;
}

// HW2 #3
// const Image& a: input image
// const Image& b: input image
// returns their sum
Image add_image(const Image &a, const Image &b) {
  assert(a.w == b.w && a.h == b.h &&
         a.c == b.c); // assure images are the same size

  // DONE: Implement addition
  Image im = Image(a.w, a.h, a.c);
  for (int c = 0; c < im.c; c++) {
    for (int w = 0; w < im.w; w++) {
      for (int h = 0; h < im.h; h++) {
        im(w, h, c) = a(w, h, c) + b(w, h, c);
      }
    }
  }
  return im;
}

// HW2 #3
// const Image& a: input image
// const Image& b: input image
// returns their difference res=a-b
Image sub_image(const Image &a, const Image &b) {
  assert(a.w == b.w && a.h == b.h &&
         a.c == b.c); // assure images are the same size

  // DONE: Implement subtraction
  Image im = Image(a.w, a.h, a.c);
  for (int c = 0; c < im.c; c++) {
    for (int w = 0; w < im.w; w++) {
      for (int h = 0; h < im.h; h++) {
        im(w, h, c) = a(w, h, c) - b(w, h, c);
      }
    }
  }
  return im;
}

// HW2 #4.1
// returns basic GX filter
Image make_gx_filter() {
  // DONE: Implement the filter
  Image im(3, 3, 1);
  im(0, 0, 0) = -1;
  im(1, 0, 0) = 0;
  im(2, 0, 0) = 1;
  im(0, 1, 0) = -2;
  im(1, 1, 0) = 0;
  im(2, 1, 0) = 2;
  im(0, 2, 0) = -1;
  im(1, 2, 0) = 0;
  im(2, 2, 0) = 1;
  return im;
}

// HW2 #4.1
// returns basic GY filter
Image make_gy_filter() {
  // DONE: Implement the filter
  Image im(3, 3, 1);
  im(0, 0, 0) = -1;
  im(1, 0, 0) = -2;
  im(2, 0, 0) = -1;
  im(0, 1, 0) = 0;
  im(1, 1, 0) = 0;
  im(2, 1, 0) = 0;
  im(0, 2, 0) = 1;
  im(1, 2, 0) = 2;
  im(2, 2, 0) = 1;
  return im;
}

// HW2 #4.2
// Image& im: input image
void feature_normalize(Image &im) {
  assert(im.w * im.h); // assure we have non-empty image

  // DONE: Normalize the features for each channel
  float _min = 2, _max = 0;
  for (int c = 0; c < im.c; c++) {
    for (int y = 0; y < im.h; y++) {
      for (int x = 0; x < im.w; x++) {
        _min = fmin(_min, im(x, y, c));
        _max = fmax(_max, im(x, y, c));
      }
    }
  }
  for (int c = 0; c < im.c; c++) {
    for (int y = 0; y < im.h; y++) {
      for (int x = 0; x < im.w; x++) {
        im(x, y, c) = (im(x, y, c) - _min) / (_max - _min);
      }
    }
  }
}

// Normalizes features across all channels
void feature_normalize_total(Image &im) {
  assert(im.w * im.h * im.c); // assure we have non-empty image

  int nc = im.c;
  im.c = 1;
  im.w *= nc;

  feature_normalize(im);

  im.w /= nc;
  im.c = nc;
}

// HW2 #4.3
// Image& im: input image
// return a pair of images of the same size
pair<Image, Image> sobel_image(const Image &im) {
  Image G(im.w, im.h, 1);
  Image theta(im.w, im.h, 1);
  Image gx = convolve_image(im, make_gx_filter(), false);
  Image gy = convolve_image(im, make_gy_filter(), false);
  for (int y = 0; y < im.h; y++) {
    for (int x = 0; x < im.w; x++) {
      float u = gx(x, y);
      float v = gy(x, y);
      G(x, y) = sqrt(u * u + v * v);
      theta(x, y) = atan2(v, u);
    }
  }
  return {G, theta};
}

// HW2 #4.4
// const Image& im: input image
// returns the colorized Sobel image of the same size
Image colorize_sobel(const Image &im) {
  Image smooth = convolve_image(im, make_gaussian_filter(4), true);
  std::pair<Image, Image> sobel = sobel_image(smooth);
  Image G = sobel.first;
  Image theta = sobel.second;
  feature_normalize(G);

  Image ret(im.w, im.h, 3);
  for (int y = 0; y < im.h; y++) {
    for (int x = 0; x < im.w; x++) {
      float S = G(x, y);
      float H = theta(x, y) / (2 * M_PI) + 0.5;
      ret(x, y, 0) = H;
      ret(x, y, 1) = S;
      ret(x, y, 2) = S;
    }
  }
  hsv_to_rgb(ret);
  return ret;
}

// HW2 #4.5
// const Image& im: input image
// float sigma1,sigma2: the two sigmas for bilateral filter
// returns the result of applying bilateral filtering to im
Image bilateral_filter(const Image &im, float sigma1, float sigma2) {
  Image bf = im;
  int k = 6 * sigma1;
  k /= 2;
  for (int c = 0; c < im.c; c++) {
    for (int y = 0; y < im.h; y++) {
      for (int x = 0; x < im.w; x++) {
        double sum = 0;
        double wsum = 0;
        for (int fy = -k; fy <= k; fy++) {
          for (int fx = -k; fx <= k; fx++) {
            int nx = x + fx;
            int ny = y + fy;
            double f = exp(-((fx * fx + fy * fy) / (2 * sigma1 * sigma1) +
                             pow(im.clamped_pixel(nx, ny, c) - im(x, y, c), 2) /
                                 (2 * sigma2 * sigma2)));
            sum += f * im.clamped_pixel(nx, ny, c);
            wsum += f;
          }
        }
        bf(x, y, c) = sum / wsum;
      }
    }
  }
  return bf;
}

// HELPER MEMBER FXNS

void Image::feature_normalize(void) { ::feature_normalize(*this); }
void Image::feature_normalize_total(void) { ::feature_normalize_total(*this); }
void Image::l1_normalize(void) { ::l1_normalize(*this); }

Image operator-(const Image &a, const Image &b) { return sub_image(a, b); }
Image operator+(const Image &a, const Image &b) { return add_image(a, b); }
