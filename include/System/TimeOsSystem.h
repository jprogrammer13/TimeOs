#ifndef __TIMEOSSYSTEM_H__
#define __TIMEOSSYSTEM_H__

#include <Arduino.h>
#include <map>

#include <System/SystemUi.h>
#include <Arduino_GFX_Library.h>
#include <gfx_extend.h>
#include <pin.h>


#include <Navigation.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <TimeClock.h>


#include <App/applications.h>
#include <WatchFace/watchFaces.h>

class TimeOsSystem
{
public:
    TimeOsSystem();
    void applicationRegistration();
    void watchFacesRegistration();
    void begin();
    void run();

private:
    //System Utility
    SystemUi *systemUi;

    Navigation *navigation;

    TimeCLock *timeCLock;

    // DISPLAY
    Arduino_DataBus *bus;
    Arduino_GC9A01 *tft;
    Arduino_Canvas_EXT *gfx;

    std::map<String, Ui *> applications;
    std::map<String, Ui *> watchFaces;
};

#endif