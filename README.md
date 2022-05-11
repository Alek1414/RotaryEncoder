Rotary Encoder class
--------------------

Contains a class to detect different actions of a Rotary Encoder.
After initialization of the `RotaryEncoder` object, the `check` method must be called cyclically so the action is detected and the `action` variable is updated.
This variable shows the detected action for one cycle only.
A function containing a call to the `clk_isr()` method must be created and assigned in the declaration of the `RotaryEncoder` object.
See example program.

## Example of object declaration

```lua
#define CLK_PIN 3 // Defines input for the clock pin
#define DT_PIN 10 // Defines input for the direction pin
#define BTN_PIN 11 // Defines input for the button pin

void encoderISR(void); // Function that calls the clk_isr method of the RotaryEncoder class
RotaryEncoder rot_enc(CLK_PIN, DT_PIN, BTN_PIN, &encoderISR); // Declaration of the RotaryEncoder object

// The interrupt function should alwas look like this
void encoderISR(void)
{
    rot_enc.clk_isr();
}
```

## Detectable actions

```lua
enum eRotaryEncoder
{
  RE_NONE = 0,  // No action has been detectet
  RE_CW,        // Rotate Rotary Encoder CW
  RE_CCW,       // Rotate Rotary Encoder CCW
  RE_SHORT,     // Press Rotary Encoder button for a short period
  RE_LONG,      // Press Rotary Encoder button for a long period
  RE_DOUBLE     // Double press Rotary Encoder button
};
```

## Timings for the detection of the actions

The timings for the detection of the actions are set by some defines.
If necesary this defines can be redifened in your code.
This defines are the following:
* TIME_SHORT (minimum time for RE_SHORT detection [ms])
* TIME_LONG (minimum time for RE_LONG detection [ms])
* DOUBLE_DELAY (maximum time between two pushes of the button for RE_DOUBLE detection [ms])
* DEBOUNCE_TIME (debounce time for all signals [ms])

Example of redefinition of the timings (with default values):
```lua
#define TIME_SHORT 100
#define TIME_LONG 800
#define DOUBLE_DELAY 200
#define DEBOUNCE_TIME 50
```