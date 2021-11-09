#include <Arduino.h>
#include <utils.h>

float rpx(float cx, float r, float d) { return cx + r * cos((d - 90) * 1000.0 / 57296.0); }
float rpy(float cy, float r, float d) { return cy + r * sin((d - 90) * 1000.0 / 57296.0); }

// rotate a point around a point
int32_t rotateX(int32_t x, int32_t y, int32_t rx, int32_t ry, float cosA, float sinA)
{
    return (x - rx) * cosA + (y - ry) * sinA;
}
int32_t rotateY(int32_t x, int32_t y, int32_t rx, int32_t ry, float cosA, float sinA)
{
    return (y - ry) * cosA - (x - rx) * sinA;
}

int32_t rotateX(int32_t x, int32_t y, int32_t rx, int32_t ry, float a)
{
    return (x - rx) * cos(a) + (y - ry) * sin(a);
}
int32_t rotateY(int32_t x, int32_t y, int32_t rx, int32_t ry, float a)
{
    return (y - ry) * cos(a) - (x - rx) * sin(a);
}

uint16_t rgb565(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((red & 0b00011111000) << 8) | ((green & 0b00011111100) << 3) | (blue >> 3);
}