#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <gfx_extend.h>
#include <pin.h>
#include <Navigation.h>
#include <Wire.h>
#include <RtcDS3231.h>

#include <TimeClock.h>

RtcDS3231<TwoWire> Rtc(Wire);
// #include <App/helloWorld.h>
#include <WatchFace/TimeOsDigital.h>

Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO, VSPI);
Arduino_GC9A01 *tft = new Arduino_GC9A01(bus, TFT_RST, 0 /* rotation */, true /* IPS */);
Arduino_Canvas_EXT *gfx = new Arduino_Canvas_EXT(240 /* width */, 240 /* height */, tft);

TimeCLock c_time(&Rtc);
Navigation navigation(BTN_3, BTN_2, BTN_1);
TimeOsDigital timeOs(&navigation, gfx,&c_time);

void setup()
{
    Serial.begin(115200);
    c_time.begin();
    navigation.begin();

    gfx->begin();
    gfx->fillScreen(WHITE);
}

void loop()
{
    navigation.update();
    timeOs.draw();
}