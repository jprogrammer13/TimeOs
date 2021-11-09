#ifndef __WATCHFACE_H__
#define __WATCHFACE_H__
#include <Arduino.h>
#include <gfx_extend.h>
#include <Navigation.h>
#include <TimeClock.h>

class WatchFace
{
public:
    WatchFace(){};
    WatchFace(Navigation *_navigation, Arduino_Canvas_EXT *_gfx, TimeCLock *_time)
    {
        this->navigation = _navigation;
        this->gfx = _gfx;
        this->time = _time;
    }
    // You must override
    virtual void draw() = 0;

    //
    Navigation *navigation;
    Arduino_Canvas_EXT *gfx;
    TimeCLock *time;
};

#endif