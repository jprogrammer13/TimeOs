#include <Arduino.h>
#include <Arduino_DataBus.h>
#include <Arduino_GFX.h>
#include <gfx_extend.h>

Arduino_Canvas_EXT::Arduino_Canvas_EXT(int16_t w, int16_t h, Arduino_G *output, int16_t output_x, int16_t output_y)
    : Arduino_GFX(w, h), _output(output), _output_x(output_x), _output_y(output_y)
{
}

void Arduino_Canvas_EXT::begin(int32_t speed)
{
    size_t s = _width * _height * 2;
#if defined(ESP32)
    if (psramFound())
    {
        _framebuffer = (uint16_t *)ps_malloc(s);
    }
    else
    {
        // _framebuffer = (uint16_t *)malloc(s);
        // hack for allocate memory over 63,360 pixels
        s /= 2;
        _framebuffer = (uint16_t *)malloc(s);
        uint16_t *tmp = (uint16_t *)malloc(s);
        UNUSED(tmp);
        log_v("_framebuffer delta: %d", tmp - _framebuffer);
    }
#else
    _framebuffer = (uint16_t *)malloc(s);
#endif
    if (!_framebuffer)
    {
        Serial.println(F("_framebuffer allocation failed."));
    }
    _output->begin(speed);
}

void Arduino_Canvas_EXT::writePixelPreclipped(int16_t x, int16_t y, uint16_t color)
{
    _framebuffer[((int32_t)y * _width) + x] = color;
}

void Arduino_Canvas_EXT::writeFastVLine(int16_t x, int16_t y,
                                        int16_t h, uint16_t color)
{
    if (_ordered_in_range(x, 0, _max_x) && h)
    { // X on screen, nonzero height
        if (h < 0)
        {               // If negative height...
            y += h + 1; //   Move Y to top edge
            h = -h;     //   Use positive height
        }
        if (y <= _max_y)
        { // Not off bottom
            int16_t y2 = y + h - 1;
            if (y2 >= 0)
            { // Not off top
                // Line partly or fully overlaps screen
                if (y < 0)
                {
                    y = 0;
                    h = y2 + 1;
                } // Clip top
                if (y2 > _max_y)
                {
                    h = _max_y - y + 1;
                } // Clip bottom

                uint16_t *fb = _framebuffer + ((int32_t)y * _width) + x;
                while (h--)
                {
                    *fb = color;
                    fb += _width;
                }
            }
        }
    }
}

void Arduino_Canvas_EXT::writeFastHLine(int16_t x, int16_t y,
                                        int16_t w, uint16_t color)
{
    if (_ordered_in_range(y, 0, _max_y) && w)
    { // Y on screen, nonzero width
        if (w < 0)
        {               // If negative width...
            x += w + 1; //   Move X to left edge
            w = -w;     //   Use positive width
        }
        if (x <= _max_x)
        { // Not off right
            int16_t x2 = x + w - 1;
            if (x2 >= 0)
            { // Not off left
                // Line partly or fully overlaps screen
                if (x < 0)
                {
                    x = 0;
                    w = x2 + 1;
                } // Clip left
                if (x2 > _max_x)
                {
                    w = _max_x - x + 1;
                } // Clip right

                uint16_t *fb = _framebuffer + ((int32_t)y * _width) + x;
                while (w--)
                {
                    *(fb++) = color;
                }
            }
        }
    }
}

void Arduino_Canvas_EXT::flush()
{
    _output->draw16bitRGBBitmap(_output_x, _output_y, _framebuffer, _width, _height);
}

// CUSTOM FUNCTIONS

void Arduino_Canvas_EXT::drawThickLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t radius, uint16_t color, bool highQuality)
{ // see p3dt_gfx_2d_license.txt

    // see p3dt_gfx_2d_license.txt
    int32_t tmp;
    int32_t x, y;
    int32_t dx, dy;
    int32_t err;
    int32_t ystep;

    uint8_t swapxy = 0;

    /* no intersection check at the moment, should be added... */

    if (x1 > x2)
        dx = x1 - x2;
    else
        dx = x2 - x1;
    if (y1 > y2)
        dy = y1 - y2;
    else
        dy = y2 - y1;

    if (dy > dx)
    {
        swapxy = 1;
        tmp = dx;
        dx = dy;
        dy = tmp;
        tmp = x1;
        x1 = y1;
        y1 = tmp;
        tmp = x2;
        x2 = y2;
        y2 = tmp;
    }
    if (x1 > x2)
    {
        tmp = x1;
        x1 = x2;
        x2 = tmp;
        tmp = y1;
        y1 = y2;
        y2 = tmp;
    }
    err = dx >> 1;
    if (y2 > y1)
        ystep = 1;
    else
        ystep = -1;
    y = y1;

    if (x2 == 0xffff)
        x2--;

    for (x = x1; x <= x2; x++)
    {
        if (swapxy == 0)
        {
            if (highQuality)
            {
                fillCircle(x, y, radius, color);
            }
            else
            {
                drawCircle(x, y, radius, color);
                if (radius > 2)
                {
                    drawCircle(x, y, radius - 1, color);
                }
                if (radius > 3)
                {
                    drawCircle(x, y, radius - 2, color);
                }
            }
        }
        else
        {
            if (highQuality)
            {
                fillCircle(y, x, radius, color);
            }
            else
            {
                drawCircle(y, x, radius, color);
                if (radius > 2)
                {
                    drawCircle(y, x, radius - 1, color);
                }
                if (radius > 3)
                {
                    drawCircle(y, x, radius - 2, color);
                }
            }
        }

        err -= (uint8_t)dy;
        if (err < 0)
        {
            y += (uint16_t)ystep;
            err += (uint16_t)dx;
        }
    }
}

void Arduino_Canvas_EXT::drawArc(int32_t cx, int32_t cy, float start, float stop, uint16_t radius, uint8_t lineRadius, uint16_t color, uint16_t steps, bool highQuality)
{
    int32_t x1 = rpx(cx, radius, start);
    int32_t y1 = rpy(cy, radius, start);
    // printf("\ndraw from %f,%f in %d steps", start, stop, steps);

    float arcLength = stop - start;

    for (uint16_t i = 1; i <= steps; i++)
    {
        float segmentLength = i * (arcLength / steps);
        // printf("\n rpx(%d, %d, %f +  %f)", cx, radius, start, segmentLength);

        int32_t x2 = rpx(cx, radius, start + segmentLength);
        int32_t y2 = rpy(cy, radius, start + segmentLength);
        // printf("\n gfx2d.drawLine(%d, %d, %d, %d, color);", x1, y1, x2, y2);
        drawThickLine(x1, y1, x2, y2, lineRadius, color, highQuality);
        x1 = x2;
        y1 = y2;
    }
}