#include <Arduino.h>
#include <TimeClock.h>

TimeCLock::TimeCLock(){};
TimeCLock::TimeCLock(RtcDS3231<TwoWire> *_Rtc)
{
    this->Rtc = _Rtc;
    dateTime = RtcDateTime();
};

void TimeCLock::begin()
{
    Wire.begin(SDA, SCL, 100000L);
    Rtc->Begin();
    Rtc->Enable32kHzPin(false);
    Rtc->SetSquareWavePin(DS3231SquareWavePin_ModeNone);
    RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
    Rtc->SetDateTime(compiled);
    Rtc->SetIsRunning(true);
}

uint32_t TimeCLock::getTime()
{
    return Rtc->GetDateTime().Epoch32Time();
}

uint32_t TimeCLock::getHour()
{
    dateTime.InitWithEpoch32Time(getTime());
    return dateTime.Hour();
}

uint32_t TimeCLock::getMinute()
{
    dateTime.InitWithEpoch32Time(getTime());
    return dateTime.Minute();
}

uint32_t TimeCLock::getSecond()
{
    dateTime.InitWithEpoch32Time(getTime());
    return dateTime.Second();
}

uint32_t TimeCLock::getDay()
{
    dateTime.InitWithEpoch32Time(getTime());
    return dateTime.Day();
}

uint32_t TimeCLock::getMonth()
{
    dateTime.InitWithEpoch32Time(getTime());
    return dateTime.Month();
}

uint32_t TimeCLock::getYear()
{
    dateTime.InitWithEpoch32Time(getTime());
    return dateTime.Year();
}

uint32_t TimeCLock::getWeekDay()
{
    dateTime.InitWithEpoch32Time(getTime());
    return dateTime.DayOfWeek();
}

String TimeCLock::getWeekDayStr()
{
    String day[] = {"SUNDAY", "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY"};
    return day[this->getWeekDay()];
}