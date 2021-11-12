#include <Arduino.h>

#include <System/TimeOsSystem.h>

TimeOsSystem timeOsSys;

void setup()
{
    Serial.begin(115200);
    timeOsSys.applicationRegistration();
    timeOsSys.watchFacesRegistration();
    timeOsSys.begin();
}

void loop()
{
    timeOsSys.run();
}