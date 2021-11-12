#include <Arduino.h>
#include <System/TimeOsSystem.h>

RtcDS3231<TwoWire> Rtc(Wire);

TimeOsSystem::TimeOsSystem()
{
    navigation = new Navigation(BTN_3, BTN_2, BTN_1);
    timeCLock = new TimeCLock(&Rtc);

    systemUi = new SystemUi();

    bus = new Arduino_ESP32SPI(T_TFT_DC, T_TFT_CS, T_TFT_SCK, T_TFT_MOSI, T_TFT_MISO, VSPI);
    tft = new Arduino_GC9A01(bus, T_TFT_RST, 0 /* rotation */, true /* IPS */);
    gfx = new Arduino_Canvas_EXT(240 /* width */, 240 /* height */, tft);
}

void TimeOsSystem::applicationRegistration()
{
    applications.insert(std::pair<String, App *>("HelloWord", new HelloWorld(navigation, gfx, timeCLock, systemUi)));
}

void TimeOsSystem::watchFacesRegistration()
{
    watchFaces.insert(std::pair<String, WatchFace *>("TimeOsDigital", new TimeOsDigital(navigation, gfx, timeCLock, systemUi)));
}

void TimeOsSystem::begin()
{
    navigation->begin();
    timeCLock->begin();
    gfx->begin();
    gfx->fillScreen(WHITE);
    systemUi->registerApplications(&applications);
    systemUi->registerWatchFaces(&watchFaces);
    systemUi->setWatchface("TimeOsDigital");
}

void TimeOsSystem::run()
{
    navigation->update();
    systemUi->pageRender();
}