#pragma once

#include <cmath>

struct RGB { double r, g, b; };

struct XYZ { double x, y, z; };

struct LAB { double l, a, b; };


inline void RgbToXyz(RGB& rgb, XYZ& xyz)
{
  double r = rgb.r;
  double g = rgb.g;
  double b = rgb.b;

  r /= 255;
  g /= 255;
  b /= 255;

  if (r > 0.04045) { r = pow((r + 0.055) / 1.055, 2.4); }
  else { r /= 12.92; }

  if (g > 0.04045) { g = pow((g + 0.055) / 1.055, 2.4); }
  else { g /= 12.92; }

  if (b > 0.04045) { b = pow((b + 0.055) / 1.055, 2.4); }
  else { b /= 12.92; }

  r *= 100;
  g *= 100;
  b *= 100;

  xyz.x = r * 0.4124 + g * 0.3576 + b * 0.1805;
  xyz.y = r * 0.2126 + g * 0.7152 + b * 0.0722;
  xyz.z = r * 0.0193 + g * 0.1192 + b * 0.9505;
}


inline void XyzToLab(XYZ& xyz, LAB& lab)
{
  double x = xyz.x;
  double y = xyz.y;
  double z = xyz.z;

  x /= 95.047;
  y /= 100.0;
  z /= 108.883;

  if (x > 0.008856) { x = pow(x, (1.0 / 3.0)); }
  else { x = (7.787 * x) + (16.0 / 116.0); }

  if (y > 0.008856) { y = pow(y, (1.0 / 3.0)); }
  else { y = (7.787 * y) + (16.0 / 116.0); }

  if (z > 0.008856) { z = pow(z, (1.0 / 3.0)); }
  else { z = (7.787 * z) + (16.0 / 116.0); }

  lab.l = (116 * y) - 16;
  lab.a = 500 * (x - y);
  lab.b = 200 * (y - z);
}
