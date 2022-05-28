# Rotary Encoder library

This Arduino library contains a class to detect different actions of a Rotary Encoder.
It works with any encoder thas has the following signals:
* Push button
* Encoder clock
* Encoder direction

After initialization of the `RotaryEncoder` object, the `check` method must be called cyclically so the action is detected and the `action` variable is updated.
This variable shows the detected action for one cycle only.
A function containing a call to the `clk_isr()` method must be created and assigned in the declaration of the `RotaryEncoder` object.
See example program.

### Example of the object declaration

```cpp
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

### Detectable actions

The detectable actions of the Rotary Encoder, that are present for one cycle only in the `action` variable of the object, are the following:

```cpp
enum eRotaryEncoder
{
  RE_NONE = 0,  // No action detectet
  RE_CW,        // CW rotation
  RE_CCW,       // CCW rotation
  RE_SHORT,     // Button pressed for a short period
  RE_LONG,      // Button pressed for a long period
  RE_DOUBLE     // Button pressed two times
};
```

### Timings for the detection of the actions

The timings for the detection of the actions are set by some defines.
If necesary this defines can be redifened in your code.
This defines are the following:
* `TIME_SHORT` (minimum time for `RE_SHORT` detection [ms])
* `TIME_LONG` (minimum time for `RE_LONG` detection [ms])
* `DOUBLE_DELAY` (maximum time between two pushes of the button for `RE_DOUBLE` detection [ms])
* `DEBOUNCE_TIME` (debounce time for all input signals [ms])

Example of redefinition of the timings (here with default values):
```cpp
#define TIME_SHORT 100
#define TIME_LONG 800
#define DOUBLE_DELAY 200
#define DEBOUNCE_TIME 50
```
