#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <gfx_extend.h>
#include <pin.h>
#include <Navigation.h>
#include <App/helloWorld.h>

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI);
Arduino_GC9A01 *tft = new Arduino_GC9A01(bus, TFT_RST, 0 /* rotation */, true /* IPS */);
Arduino_Canvas_EXT *gfx = new Arduino_Canvas_EXT(240 /* width */, 240 /* height */, tft);
Navigation navigation(BTN_3, BTN_2, BTN_1);
HelloWorld helloword(&navigation, gfx);

void setup()
{
    Serial.begin(115200);
    navigation.begin();
    gfx->begin();
    gfx->fillScreen(WHITE);
}

void loop()
{
    navigation.update();
    helloword.draw_main();
}