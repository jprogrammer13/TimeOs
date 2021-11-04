#include <Arduino.h>
#include <Navigation.h>

Navigation::Navigation(uint8_t _B_UP, uint8_t _B_DOWN, uint8_t _B_SLC)
{
    this->B_UP = Button(_B_UP);
    this->B_DOWN = Button(_B_DOWN);
    this->B_SLC = Button(_B_SLC, true);
    this->action = NONE;
}

void Navigation::begin()
{
    this->B_UP.begin();
    this->B_DOWN.begin();
    this->B_SLC.begin();
}

void Navigation::update()
{
    B_UP.update();
    B_DOWN.update();
    B_SLC.update();

    states[0] = B_UP.get_state();
    states[1] = B_DOWN.get_state();
    states[2] = B_SLC.get_state();
}

Action Navigation::get_action()
{
    Action tmp_action = NONE;
    switch (states[0])
    {
    // Check UP button
    case 1:
        tmp_action = UP;
        break;
    case 2:
        tmp_action = UP_LONG;
        break;
    case 0:
        // Check DOWN button
        switch (states[1])
        {
        case 1:
            tmp_action = DOWN;
            break;
        case 2:
            tmp_action = DOWN_LONG;
            break;
        case 0:
            // Check SLC button
            switch (states[2])
            {
            case 1:
                tmp_action = SELECT;
                break;
            case 2:
                tmp_action = BACK;
                break;
            }
            break;
        }
        break;
    }

    return tmp_action;
}