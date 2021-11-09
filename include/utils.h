#ifndef __GFX_ANGLES_H__
#define __GFX_ANGLES_H__
#include <Arduino.h>

// THIS IMPLEMENTATION IS From Paul Smith https://github.com/Open-Smartwatch/lib-open-smartwatch

// rotate a point around a center (cy,cy), with a radius r, 0 degrees ist 12 o'clock
float rpx(float cx, float r, float d);
float rpy(float cy, float r, float d);

// rotate a point around a point
int32_t rotateX(int32_t x, int32_t y, int32_t rx, int32_t ry, float cosA, float sinA);
int32_t rotateY(int32_t x, int32_t y, int32_t rx, int32_t ry, float cosA, float sinA);

int32_t rotateX(int32_t x, int32_t y, int32_t rx, int32_t ry, float a);
int32_t rotateY(int32_t x, int32_t y, int32_t rx, int32_t ry, float a);

uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue);

#endif