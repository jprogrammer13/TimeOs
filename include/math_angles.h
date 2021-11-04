#ifndef __GFX_ANGLES_H__
#define __GFX_ANGLES_H__
#include <Arduino.h>

// THIS IMPLEMENTATION IS From Paul Smith https://github.com/Open-Smartwatch/lib-open-smartwatch

// rotate a point around a center (cy,cy), with a radius r, 0 degrees ist 12 o'clock
float rpx(float cx, float r, float d) { return cx + r * cos((d - 90) * 1000.0 / 57296.0); }
float rpy(float cy, float r, float d) { return cy + r * sin((d - 90) * 1000.0 / 57296.0); }

// rotate a point around a point
int32_t rotateX(int32_t x, int32_t y, int32_t rx, int32_t ry, float cosA, float sinA) {
  return (x - rx) * cosA + (y - ry) * sinA;
}
int32_t rotateY(int32_t x, int32_t y, int32_t rx, int32_t ry, float cosA, float sinA) {
  return (y - ry) * cosA - (x - rx) * sinA;
}

int32_t rotateX(int32_t x, int32_t y, int32_t rx, int32_t ry, float a) {
  return (x - rx) * cos(a) + (y - ry) * sin(a);
}
int32_t rotateY(int32_t x, int32_t y, int32_t rx, int32_t ry, float a) {
  return (y - ry) * cos(a) - (x - rx) * sin(a);
}

#endif