#include <Arduino.h>
#include <WatchFace.h>
#include <WatchFace/TimeOsDigital.h>
#define step 3

TimeOsDigital::TimeOsDigital(Navigation *_navigation, Arduino_Canvas_EXT *_gfx, TimeCLock *_time, SystemUi *_sysUi) : WatchFace(_navigation, _gfx, _time, _sysUi)
{
    gfx->setFont(&Poppins_Medium50pt7b);
};

void TimeOsDigital::draw()
{

    uint32_t m1 = time->getMinute() / 10;
    uint32_t m2 = time->getMinute() % 10;
    uint32_t hour = time->getHour();
    uint32_t day = time->getDay();

    gfx->fillScreen(BLACK);
    // INITIAL TICK
    gfx->drawThickLine(rpx(120, 120, 30), rpy(120, 120, 30), rpx(120, 120, 180 + 30), rpy(120, 120, 180 + 30), 2, RED);
    gfx->drawThickLine(rpx(120, 120, 360 - 30), rpy(120, 120, 360 - 30), rpx(120, 120, 180 - 30), rpy(120, 120, 180 - 30), 2, RED);
    gfx->drawThickLine(rpx(120, 120, 360 - 90), rpy(120, 120, 360 - 90), rpx(120, 120, 180 - 90), rpy(120, 120, 180 - 90), 2, RED);

    // custom black
    gfx->fillCircle(120, 120, 100, BLACK);

    // TIME

    // Minute
    gfx->setFont(&Poppins_Medium50pt7b);
    gfx->setTextColor(rgb565(212, 212, 212));

    if (m1 == 1)
    {
        gfx->setCursor(71, 155); // for one
    }
    else
    {
        gfx->setCursor(55, 155); // for normal
    }
    gfx->println(m1);

    if (m2 == 1)
    {
        gfx->setCursor(136, 155); // for one
    }
    else
    {
        gfx->setCursor(120, 155); // for normal
    }
    gfx->println(m2);

    // Date

    gfx->setFont(&Poppins_Medium9pt7b);
    gfx->setTextColor(rgb565(212, 212, 212));

    gfx->setCursor(160, 65);
    String date = (time->getWeekDayStr().substring(0, 3)) + " " + (((day) < 10) ? "0" + String(day) : String(day));
    gfx->print(date);

    gfx->drawThickLine(162, 73, 215, 73, 1, RED);

    // Hour

    gfx->setFont(&Poppins_Medium17pt7b);
    gfx->setTextColor(rgb565(212, 212, 212));

    gfx->setCursor(190, 110);
    gfx->print(((hour < 10) ? "0" + String(hour) : hour));

    // line and details
    for (int i = 0; i < 15; i++)
    {
        gfx->drawThickLine(rpx(120, 100, 314 - (step * i)), rpy(120, 100, 314 - (step * i)), rpx(120, 100, 110 + (step * i)), rpy(120, 100, 110 + (step * i)), 1, BLACK, true);
    }

    // add bar
    gfx->drawArc(120, 120, 335, 385, 90, 1, rgb565(33, 33, 33), 100, true);
    gfx->drawArc(120, 120, 95, 145, 90, 1, rgb565(33, 33, 33), 100, true);
    gfx->drawArc(120, 120, 155, 205, 90, 1, rgb565(33, 33, 33), 100, true);
    gfx->drawArc(120, 120, 215, 265, 90, 1, rgb565(33, 33, 33), 100, true);
    gfx->drawArc(120, 120, 275, 325, 90, 1, rgb565(33, 33, 33), 100, true);

    gfx->flush();

    if (navigation->get_action() == BACK)
    {
        sysUi->setApp("HelloWord");
    }
}