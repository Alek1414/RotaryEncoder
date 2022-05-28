#include <Arduino.h>
#include "RotaryEncoder.h"

RotaryEncoder::RotaryEncoder(   byte clk, 
                                byte dt,
                                byte btn,
                                void (*clk_isr_function)(void))
{
    this->clk_pin = clk;
    this->dt_pin = dt;
    this->btn_pin = btn;

    this->last_encoder_interrupt = millis();
    this->new_encoder_direction = false;
    this->encoder_direction = false;
    this->last_pressed = millis();
    this->btn_last_value = true;
    this->first_encoder_short = false;
    this->clk_isr_function = clk_isr_function;

    pinMode(this->dt_pin, INPUT_PULLUP);
	pinMode(this->clk_pin, INPUT_PULLUP);
    pinMode(this->btn_pin, INPUT_PULLUP);

    this->action = RE_NONE;
    attachInterrupt(digitalPinToInterrupt(this->clk_pin), this->clk_isr_function, CHANGE);
}

void RotaryEncoder::check(void)
{
    this->action = RE_NONE;

    if(this->new_encoder_direction)
    {
        if(millis() - this->last_encoder_interrupt > DEBOUNCE_TIME)
        {
            if(!this->encoder_direction) this->action = RE_CW;
            else this->action = RE_CCW;
            this->new_encoder_direction = false;
            EIFR = (1 << digitalPinToInterrupt(this->clk_pin));
            attachInterrupt(digitalPinToInterrupt(this->clk_pin), this->clk_isr_function, RISING);
        }
    }

    unsigned long delay = millis()-this->last_pressed;
    bool sw_value = digitalRead(this->btn_pin);
    if(delay > DEBOUNCE_TIME)
    {
        if(this->btn_last_value && !sw_value)
        {
            detachInterrupt(digitalPinToInterrupt(this->clk_pin));
            this->last_pressed = millis();
        }
        else if(!this->btn_last_value && sw_value)
        {
            if(delay > TIME_LONG)
            {
                this->action = RE_LONG;
                EIFR = (1 << digitalPinToInterrupt(this->clk_pin));
                attachInterrupt(digitalPinToInterrupt(this->clk_pin), this->clk_isr_function, RISING);
            }
            else if(delay > TIME_SHORT)
            {
                if(this->first_encoder_short)
                {
                    this->action = RE_DOUBLE;
                    this->first_encoder_short = false;
                    EIFR = (1 << digitalPinToInterrupt(this->clk_pin));
                    attachInterrupt(digitalPinToInterrupt(this->clk_pin), this->clk_isr_function, RISING);
                }
                else
                {
                    this->first_encoder_short = true;
                }
            }
            this->last_pressed = millis();
        }
        else if(this->first_encoder_short && delay > DOUBLE_DELAY)
        {
            this->action = RE_SHORT;
            this->first_encoder_short = false;
            EIFR = (1 << digitalPinToInterrupt(this->clk_pin));
            attachInterrupt(digitalPinToInterrupt(this->clk_pin), this->clk_isr_function, RISING);
        }
    }
    this->btn_last_value = sw_value;
}

void RotaryEncoder::clk_isr(void)
{
    detachInterrupt(digitalPinToInterrupt(this->clk_pin));
    this->last_encoder_interrupt = millis();
    this->new_encoder_direction = true;
    this->encoder_direction = digitalRead(this->dt_pin);
}