#include <Arduino.h>
#include "RotaryEncoder.h"

#define CLK_PIN 3 // Defines input for the clock pin
#define DT_PIN 10 // Defines input for the direction pin
#define BTN_PIN 11 // Defines input for the button pin

void encoderISR(void); // Function that calls the clk_isr method of the RotaryEncoder class
RotaryEncoder rot_enc(CLK_PIN, DT_PIN, BTN_PIN, &encoderISR); // Declaration of the RotaryEncoder object

// This function should alwas look like this
void encoderISR(void)
{
    rot_enc.clk_isr();
}

void setup()
{
    Serial.begin(115200);
    Serial.println("Rotary Encoder status:");
}

void loop()
{
    rot_enc.check(); // Functon to be called cyclically
    switch (rot_enc.action) // The status action in the object shows the detected action of the encoder for just one cycle
	{
		case RE_CW:
			Serial.println("RE_CW");
			break;
		case RE_CCW:
			Serial.println("RE_CCW");
			break;
		case RE_LONG:
			Serial.println("RE_LONG");
			break;
		case RE_SHORT:
			Serial.println("RE_SHORT");
            break;
        case RE_DOUBLE:
			Serial.println("RE_DOUBLE");
			break;
	}
}