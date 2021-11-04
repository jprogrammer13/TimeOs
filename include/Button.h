#ifndef __BUTTON_H__
#define __BUTTON_H__
#include <Arduino.h>

class Button
{
public:
    Button(){};
    Button(uint8_t _pin)
    {
        this->pin = _pin;
        this->last_read = LOW;
        this->state = 0;
        this->inverted = false;
    };
    Button(uint8_t _pin, bool _inverted)
    {
        this->pin = _pin;
        this->inverted = _inverted;
        this->last_read = LOW;
        this->state = 0;
    };
    int readState()
    {
        int tmp_state = LOW;
        if (inverted)
        {
            tmp_state = !digitalRead(pin);
        }
        else
        {
            tmp_state = digitalRead(pin);
        }
        return tmp_state;
    }
    void begin() { pinMode(this->pin, INPUT); };
    void update()
    {
        // if last state is LOW and the button is pressed
        if (last_read == LOW && readState())
        {
            t_start = millis();
            last_read = HIGH;
        }
        // if last state is HIGH and the button is not pressed
        else if (last_read == HIGH && !readState())
        {
            if (millis() - t_start >= threshold_hold)
            {
                // is a single press
                state = 2;
            }
            else if (millis() - t_start < threshold_hold)
            {
                state = 1;
            }
            last_read = LOW;
        }
        else
        {
            state = 0;
        }
    };
    int get_state()
    {
        return this->state;
    }

private:
    int state;
    int last_read;
    int t_start;
    int threshold_hold = 350;
    bool inverted;
    uint8_t pin;
};

#endif