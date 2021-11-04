#include <Arduino.h>
#include <App.h>
#include <App/helloWorld.h>

HelloWorld::HelloWorld(Navigation *_navigation, Arduino_Canvas_EXT *_gfx) : App(_navigation, _gfx)
{
    gfx->setFont(&RobotoRegular12pt7b);
};

void HelloWorld::draw_main()
{
    int tmp = navigation->get_action();
    state = (tmp != 0) ? tmp : state;
    gfx->fillScreen(BLACK);
    gfx->setCursor(30, 120);
    gfx->setTextColor(ORANGE);
    gfx->println("Hello World!");
    gfx->setCursor(120, 160);
    gfx->setTextColor(GREEN);
    gfx->println(state);
    gfx->flush();
}