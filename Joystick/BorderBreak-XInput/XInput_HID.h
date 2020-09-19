#ifndef _XInput_HID_H_
#define _XInput_HID_H_

/* Includes: */
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/power.h>
#include <avr/interrupt.h>
#include <string.h>

#include "Descriptors.h"

#include <LUFA/LUFA/Drivers/USB/USB.h>
#include <LUFA/LUFA/Drivers/Board/Joystick.h>
#include <LUFA/LUFA/Drivers/Board/LEDs.h>
#include <LUFA/LUFA/Drivers/Board/Buttons.h>
#include <LUFA/LUFA/Platform/Platform.h>

// XInput digital_buttons_1
#define XBOX_DPAD_UP    0x01
#define XBOX_DPAD_DOWN    0x02
#define XBOX_DPAD_LEFT    0x04
#define XBOX_DPAD_RIGHT   0x08
#define XBOX_START      0x10
#define XBOX_BACK     0x20
#define XBOX_LEFT_STICK   0x40
#define XBOX_RIGHT_STICK  0x80

// XInput digital_buttons_2
#define XBOX_LB   0x01
#define XBOX_RB   0x02
#define XBOX_HOME 0x04
#define XBOX_A    0x10
#define XBOX_B    0x20
#define XBOX_X    0x40
#define XBOX_Y    0x80

// Generic XS pad status (follows nintendo switch convention (X = up / B = down))
#define BUTTONUP 0
#define BUTTONDOWN 1
#define BUTTONLEFT 2
#define BUTTONRIGHT 3
#define BUTTONA 4
#define BUTTONB 5
#define BUTTONX 6
#define BUTTONY 7
#define BUTTONLB 8
#define BUTTONRB 9
#define BUTTONLT 10
#define BUTTONRT 11
#define BUTTONSTART 12
#define BUTTONSELECT 13
#define AXISLX 14
#define AXISLY 15
#define AXISRX 16
#define AXISRY 17
#define BUTTONL3 18
#define BUTTONR3 19
#define BUTTONHOME 20
byte buttonStatus[21];

/* Type Defines: */
/** Type define for the joystick HID report structure, for creating and sending HID reports to the host PC.
 *  This mirrors the layout described to the host in the HID report descriptor, in Descriptors.c.
 */
typedef struct {
  uint8_t rid;
  uint8_t rsize;
  uint8_t digital_buttons_1;
  uint8_t digital_buttons_2;
  uint8_t lt;
  uint8_t rt;
  int l_x;
  int l_y;
  int r_x;
  int r_y;
  uint8_t reserved_1[6];
} USB_JoystickReport_XInput_t;

/* Function Prototypes: */
#ifdef __cplusplus
extern "C" {
#endif
// Setup all necessary hardware, including USB initialization.
void SetupHardware();
// Process and deliver data from IN and OUT endpoints.
void HID_Task(void);
// USB device event handlers.
void EVENT_USB_Device_Connect(void);
void EVENT_USB_Device_Disconnect(void);
void EVENT_USB_Device_ConfigurationChanged(void);
void EVENT_USB_Device_ControlRequest(void);

void send_pad_state(void);
static void generate_report();

#ifdef __cplusplus
}
#endif

#endif
