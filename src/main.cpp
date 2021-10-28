#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include "gfx_extend.h"
#include "pin.h"

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI);
Arduino_GC9A01 *tft = new Arduino_GC9A01(bus, TFT_RST, 0 /* rotation */, true /* IPS */);
Arduino_Canvas_EXT *gfx = new Arduino_Canvas_EXT(240 /* width */, 240 /* height */, tft);

void setup()
{
    gfx->begin();
    gfx->fillScreen(WHITE);
}

void loop()
{
    gfx->drawCircle(120, 120, 30, GREEN);
    gfx->drawThickLine(50,50,100,100,10,PURPLE,true);
    gfx->drawArc(120,120,50,60,0,180,ORANGE);
    gfx->flush();
    delay(2000);

}