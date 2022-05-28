/*
  Rotary Encoder class

  Contains a class to detect different actions of a Rotary Encoder.
  After initialization of the 'RotaryEncoder' object, the 'check' method 
  must be called cyclically so the action is detected and the 'action' variable is updated.
  This variable shows the detected action for one cycle only.
  A function containing a call to the 'clk_isr()' method must be created and
  assigned in the declaration of the 'RotaryEncoder' object.

  The detectable actions are as follows:
    - CW rotation
    - CCW rotation
    - Short press
    - Long press
    - Double press

  Timings for the detection can be changed with the following defines:
    - TIME_SHORT (minimum time for RE_SHORT detection [ms])
    - TIME_LONG (minimum time for RE_LONG detection [ms])
    - DOUBLE_DELAY (maximum time between two pushes of the button for RE_DOUBLE detection [ms])
    - DEBOUNCE_TIME (debounce time for all signals [ms])

  created 01.04.2022
  by Alejandro Kölbl

*/

#ifndef KY_040
#define KY_040

#include <Arduino.h>

// Minimum time for RE_SHORT detection [ms]
#ifndef TIME_SHORT
#define TIME_SHORT 100
#endif

// Minimum time for RE_LONG detection [ms]
#ifndef TIME_LONG
#define TIME_LONG 800
#endif

// Maximum time between two presses of the pushes for RE_DOUBLE detection [ms]
#ifndef DOUBLE_DELAY
#define DOUBLE_DELAY 200
#endif

// Debounce time for all signals [ms]
#ifndef DEBOUNCE_TIME
#define DEBOUNCE_TIME 50
#endif

// Status list which the Rotary Encoder can have
enum eRotaryEncoder
{
  RE_NONE = 0,  // No action detectet
  RE_CW,        // CW rotation
  RE_CCW,       // CCW rotation
  RE_SHORT,     // Button pressed for a short period
  RE_LONG,      // Button pressed for a long period
  RE_DOUBLE     // Button pressed two times
};

class RotaryEncoder
{
  public:
    RotaryEncoder(byte clk, // Must be pin with interrupt
                    byte dt, // Input pin
                    byte btn, // Input pin
                    void (*interrupt)(void)); // Function that calls the clk_isr method of the RotaryEncoder class
    void check(void); // Functon to be called cyclically
    void clk_isr(void); // Interrupt function for the clk input
    enum eRotaryEncoder action; // Gives the current action of the encoder

  private:
    byte clk_pin;
    byte dt_pin;
    byte btn_pin;

    unsigned long last_encoder_interrupt;
    bool new_encoder_direction;
    bool encoder_direction;
    unsigned long last_pressed;
    bool btn_last_value;
    bool first_encoder_short;
    void (*clk_isr_function)(void);
};

#endif