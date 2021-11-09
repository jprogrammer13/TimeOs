#include <Arduino.h>
#include <TimeClock.h>

TimeCLock::TimeCLock(){};
TimeCLock::TimeCLock(RtcDS3231<TwoWire> *_Rtc)
{
    this->Rtc = _Rtc;
};

void TimeCLock::begin()
{
    Wire.begin(SDA, SCL, 100000L);
    Rtc->Begin();
    Rtc->Enable32kHzPin(false);
    if (!Rtc->LastError())
    {
        Rtc->SetSquareWavePin(DS3231SquareWavePin_ModeNone);
        RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);

        if (!Rtc->IsDateTimeValid())
        {
            Rtc->SetDateTime(compiled);
        }
        if (!Rtc->GetIsRunning())
        {
            Rtc->SetIsRunning(true);
        }
    }
}

uint32_t TimeCLock::getTime()
{
    return Rtc->GetDateTime().Epoch32Time();
}

uint32_t TimeCLock::getHour()
{
    RtcDateTime d = RtcDateTime();
    d.InitWithEpoch32Time(getTime());
    return d.Hour();
}

uint32_t TimeCLock::getMinute()
{
    RtcDateTime d = RtcDateTime();
    d.InitWithEpoch32Time(getTime());
    return d.Minute();
}
uint32_t TimeCLock::getSecond()
{
    RtcDateTime d = RtcDateTime();
    d.InitWithEpoch32Time(getTime());
    return d.Second();
}