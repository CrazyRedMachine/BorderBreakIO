# BorderBreakController Joystick Firmware

There are two versions of the Joystick firmware. Both share the same wiring.
They are compatible with the clickable thumbstick mod described in this repo main readme file.

I've set GPIO pin 10 as an additional GND pin for easier wiring during my tests.

## Acknowledgements

DInput version is based on [Matthew Heironimus' ArduinoJoystick](https://github.com/MHeironimus/ArduinoJoystickLibrary).

XInput version is based on [bootsector's XInputPadMicro](https://github.com/bootsector/XInputPadMicro) for LUFA

## Features

LED lighting mostly follows the mouse lights behavior (which seems consistent with the arcade cabinet) :

- Green when idle
- White when you press one of the trigger buttons, and until 500ms after you release it
- Blue when you press the action button, and until 500ms after you release it

And because it is compatible with my mod :

- Purple when you click the analog stick.

## Wiring Diagram

### CN7

It is a 7 pin connector but only 6 are populated with wires.

Pinout in order :
- Black : GND              -> to Arduino GND
- Blue : Thumbstick click  -> to Arduino pin 5
- White : LED Blue (-)     -> to Arduino pin 9
- Purple : LED Green (-)   -> to Arduino pin 8
- Brown : LED Red (-)      -> to Arduino pin 7
- Red : LED Vin (+5V)      -> to Arduino Vcc

### CN2+4

It is a 6 pin connector with 2 wires coming from one cable then 4 wires from another.

Pinout in order :
- Black : GND              -> to Arduino GND
- Green : Button 3         -> to Arduino pin 4
- Black : GND Analog       -> to Arduino GND
- Yellow : Rx Analog       -> to Arduino pin A0
- Orange : Ry Analog       -> to Arduino pin A1
- Red : Vin Analog (+5V)   -> to Arduino Vcc

### CN3

It is a 3 pin connector all populated.

Pinout in order :
- Black: GND               -> to Arduino GND
- White: Button 2          -> to Arduino pin 3
- Orange: Button 1         -> to Arduino pin 2

## DInput firmware notes

### Instructions

- Download Arduino IDE,
- Download Joystick library from https://github.com/MHeironimus/ArduinoJoystickLibrary and follow the instructions to install it
- Build and Flash for your ATMEGA32U4 Board
- Have Fun

## XInput firmware notes
 
### Instructions

- Download Arduino IDE,
- Download Arduino Lufa from https://github.com/Palatis/Arduino-Lufa and follow the instructions to install and activate it
- Build and Flash for your ATMEGA32U4 Board
- Have Fun
