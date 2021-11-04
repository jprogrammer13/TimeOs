#include <Arduino.h>
#include <App.h>
#include <Fonts/RobotoRegular12pt7b.h>

class HelloWorld : public App
{
public:
    HelloWorld(){};
    HelloWorld(Navigation *_navigation, Arduino_Canvas_EXT *_gfx);
    void draw_main();
    void draw_widget(){};
    void background(){};

private:
    int state = 0;
};