#include <Arduino.h>
#include <WatchFace.h>
#include <Fonts/Poppins_Medium50pt7b.h>
#include <Fonts/Poppins_Medium17pt7b.h>
#include <Fonts/Poppins_Medium12pt7b.h>
#include <Fonts/Poppins_Medium9pt7b.h>
#include <Fonts/RobotoBold12pt7b.h>
#include <Fonts/RobotoRegular9pt7b.h>



class TimeOsDigital : public WatchFace
{
public:
    TimeOsDigital(){};
    TimeOsDigital(Navigation *_navigation, Arduino_Canvas_EXT *_gfx, TimeCLock *_time, SystemUi *_sysUi);
    void draw();
};