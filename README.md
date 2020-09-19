# BorderBreakIO

Notes and code on converting a Border Break panel for home computer use

## Introduction

Border Break panel has a headphone jack, a mouse and a joystick.

## Headphone jack

This is a headphone jack, duh.

## Mouse

The mouse is a regular USB HID mouse, which can be plugged on PC.

It has a 5 pin connector whose wire color match the usual USB pinout wires, as well as an extra brown who actually is in continuity with the black one, which gives us, in order, the following pinout :

- Red : +5V
- White : Data -
- Green : Data +
- Black : GND
- Brown : GND

## Joystick

The Joystick has a lot of wires coming from it, but that's just because it's internally made out of 3 separate PCBs :

- Top PCB : clickable analog stick and *common anode* RGB led
- Bottom PCB : one microswitch for the side button
- Front PCB : two microswitches or the two triggers

The connectors coming out of the joystick all have a different number of pins so I'm gonna use that number to distinguish.

### CN7

It is a 7 pin connector but only 6 are populated with wires.

Pinout in order :
- Black : GND
- Blue : Thumbstick click (note: requires a mod to work, see footnote)
- White : LED Blue (-)
- Purple : LED Green (-)
- Brown : LED Red (-)
- Red : LED Vin (+5V)

### CN2+4

It is a 6 pin connector with 2 wires coming from one cable then 4 wires from another.

Pinout in order :
- Black : GND
- Green : Button 3 (side "action" button)
- Black : GND Analog 
- Yellow : Rx Analog 
- Orange : Ry Analog 
- Red : Vin Analog (+5V)

### CN3

It is a 3 pin connector all populated.

Pinout in order :
- Black: GND
- White: Button 2 (bottom "dash" trigger)
- Orange: Button 1 (top "jump" trigger)

## Clickable Thumbstick mod

The analog stick PCB inside the joystick actually contains a clickable analog stick, however because Border Break doesn't make use of it, the shaft which allows the thumbstick to be clickable is not present. You can cut a toothpick and insert it into the component to restore this functionnality. Note that this toothpick bit has to be quite short in order not to hinder the stick motion once the joystick is reassembled.

## Arduino firmware

You'll find two firmware variants on this repo to turn the Border Break joystick into an USB game controller. One DInput, using Matt Heironimus' Joystick library, and one XInput using LUFA library. Both share the same pinout.

Please refer to the respective pages for flashing instructions and wiring diagrams.
