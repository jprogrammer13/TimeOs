#ifndef __APP_H__
#define __APP_H__
#include <Arduino.h>
#include <Ui.h>
#include <gfx_extend.h>
#include <pin.h>
#include <Navigation.h>
#include <TimeClock.h>
#include <System/SystemUi.h>

class App : public Ui
{
public:
    App(){};
    App(Navigation *_navigation, Arduino_Canvas_EXT *_gfx, TimeCLock *_time, SystemUi *_sysUi)
    {
        this->navigation = _navigation;
        this->gfx = _gfx;
        this->time = _time;
        this->sysUi = _sysUi;
    }
    // You must override
    virtual void draw() = 0;
    // Optional
    virtual void draw_widget();
    virtual void background();

    //
    Navigation *navigation;
    Arduino_Canvas_EXT *gfx;
    TimeCLock *time;
    SystemUi *sysUi;
};

#endif