#ifndef __TIMECLOCK_H__
#define __TIMECLOCK_H__

#include <Arduino.h>
#include <Wire.h>
#include <RtcDS3231.h>
#include <time.h>
#include <pin.h>


class TimeCLock
{
public:
    TimeCLock();
    TimeCLock(RtcDS3231<TwoWire> *_Rtc);
    void begin();
    uint32_t getTime();
    uint32_t getHour();
    uint32_t getMinute();
    uint32_t getSecond();
    RtcDS3231<TwoWire> *Rtc;
};

#endif