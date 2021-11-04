#ifndef __APP_H__
#define __APP_H__
#include <Arduino.h>
#include <gfx_extend.h>
#include <Navigation.h>

class App
{
public:
    App(){};
    App(Navigation *_navigation, Arduino_Canvas_EXT *_gfx)
    {
        this->navigation = _navigation;
        this->gfx = _gfx;
    }
    // You must override
    virtual void draw_main() = 0;
    // Optional
    virtual void draw_widget();
    virtual void background();

    // 
    Navigation *navigation;
    Arduino_Canvas_EXT *gfx;
};

#endif