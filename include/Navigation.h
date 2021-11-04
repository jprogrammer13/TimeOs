#ifndef __NAVIGATION_H__
#define __NAVIGATION_H__
#include <Arduino.h>
#include <pin.h>
#include <actions.h>
#include <Button.h>

class Navigation
{
public:
    Navigation(){};
    Navigation(uint8_t _B_UP, uint8_t _B_DOWN, uint8_t _B_SLC);
    void begin();
    void update();
    Action get_action();

private:
    Action action;
    Button B_UP;
    Button B_DOWN;
    Button B_SLC;
    int states[3];
};

#endif