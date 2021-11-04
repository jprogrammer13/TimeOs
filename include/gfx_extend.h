
#ifndef __ARDUINO_CANVAS_EXT_H__
#define __ARDUINO_CANVAS_EXT_H__

#include <Arduino.h>
#include <Arduino_DataBus.h>
#include <Arduino_GFX.h>

class Arduino_Canvas_EXT : public Arduino_GFX
{
public:
    Arduino_Canvas_EXT(int16_t w, int16_t h, Arduino_G *output, int16_t output_x = 0, int16_t output_y = 0);

    void begin(int32_t speed = 0) override;
    void writePixelPreclipped(int16_t x, int16_t y, uint16_t color) override;
    void writeFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) override;
    void writeFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color) override;
    void flush(void) override;

    //   CUSTOM FUNCTION
    void drawThickLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t radius, uint16_t color, bool highQuality = false);
    void drawArc(int32_t cx, int32_t cy, float start, float stop, uint16_t radius, uint8_t lineRadius,uint16_t color,uint16_t steps = 100, bool highQuality = false);
    //

protected:
    uint16_t *_framebuffer;
    Arduino_G *_output;
    int16_t _output_x, _output_y;

private:
};

#endif // _ARDUINO_CANVAS_H_