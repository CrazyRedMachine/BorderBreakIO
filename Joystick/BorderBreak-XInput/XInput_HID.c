#include "XInput_HID.h"
static USB_JoystickReport_XInput_t XInput_ReportData;

// Configures hardware and peripherals, such as the USB peripherals.
void SetupHardware() {
  // We need to disable watchdog if enabled by bootloader/fuses.
  MCUSR &= ~(1 << WDRF);
  wdt_disable();
  // We need to disable clock division before initializing the USB hardware.
  clock_prescale_set(clock_div_1);
  // We can then initialize our hardware and peripherals, including the USB stack.
  // The USB stack should be initialized last.
  USB_Init();
}

// Fired to indicate that the device is enumerating.
void EVENT_USB_Device_Connect(void) {
  // We can indicate that we're enumerating here (via status LEDs, sound, etc.).
}

// Fired to indicate that the device is no longer connected to a host.
void EVENT_USB_Device_Disconnect(void) {
  // We can indicate that our device is not ready (via status LEDs, sound, etc.).
}

// Fired when the host set the current configuration of the USB device after enumeration.
void EVENT_USB_Device_ConfigurationChanged(void) {

  Endpoint_ConfigureEndpoint((ENDPOINT_DIR_IN | 3), EP_TYPE_INTERRUPT, 32, 1);
  Endpoint_ConfigureEndpoint(JOYSTICK_IN_EPADDR, EP_TYPE_INTERRUPT, JOYSTICK_EPSIZE_XINPUT, 1);

}

// Process control requests sent to the device from the USB host.
void EVENT_USB_Device_ControlRequest(void) {
  /* Handle HID Class specific requests */
  switch (USB_ControlRequest.bRequest) {
  case HID_REQ_GetReport:
    if (USB_ControlRequest.bmRequestType
        == (REQDIR_DEVICETOHOST | REQTYPE_CLASS | REQREC_INTERFACE)) {
      Endpoint_ClearSETUP();

      /* Write the report data to the control endpoint */
      Endpoint_Write_Control_Stream_LE(&XInput_ReportData, 20);
      Endpoint_ClearOUT();
    }
    break;
  }
}

// Process and deliver data from IN and OUT endpoints.
void HID_Task(void) {
    /* Device must be connected and configured for the task to run */
if (USB_DeviceState != DEVICE_STATE_Configured)
    return;

/* Select the Joystick Report Endpoint */
  Endpoint_SelectEndpoint(JOYSTICK_IN_EPADDR);

  /* Check to see if the host is ready for another packet */
  if (Endpoint_IsINReady()) {
    /* Write Joystick Report Data */
    Endpoint_Write_Stream_LE(&XInput_ReportData, 20, NULL);

    /* Finalize the stream transfer to send the last packet */
    Endpoint_ClearIN();
    /* Clear the report data afterwards */
    memset(&XInput_ReportData, 0, 20);
    XInput_ReportData.rsize = 20;
  }
}

void send_pad_state(void){  
  generate_report();
  HID_Task();
  USB_USBTask();
}

void generate_report(){
  // HAT
    if (buttonStatus[BUTTONUP]){XInput_ReportData.digital_buttons_1 |= XBOX_DPAD_UP;}
    if (buttonStatus[BUTTONDOWN]){XInput_ReportData.digital_buttons_1 |= XBOX_DPAD_DOWN;}
    if (buttonStatus[BUTTONLEFT]){XInput_ReportData.digital_buttons_1 |= XBOX_DPAD_LEFT;}
    if (buttonStatus[BUTTONRIGHT]){XInput_ReportData.digital_buttons_1 |= XBOX_DPAD_RIGHT;}
    
  // analogs    
    XInput_ReportData.l_x = buttonStatus[AXISLX] * 257 + -32768;
    XInput_ReportData.l_y = buttonStatus[AXISLY] * -257 + 32767;
    XInput_ReportData.r_x = buttonStatus[AXISRX] * 257 + -32768;
    XInput_ReportData.r_y = buttonStatus[AXISRY] * -257 + 32767;
    
  // buttons
    if (buttonStatus[BUTTONSTART]){XInput_ReportData.digital_buttons_1 |= XBOX_START;}
    if (buttonStatus[BUTTONSELECT]){XInput_ReportData.digital_buttons_1 |= XBOX_BACK;}
    if (buttonStatus[BUTTONL3]){XInput_ReportData.digital_buttons_1 |= XBOX_LEFT_STICK;}
    if (buttonStatus[BUTTONR3]){XInput_ReportData.digital_buttons_1 |= XBOX_RIGHT_STICK;}

    /* xbox buttons are not in the same position as nintendo controllers */
    if (buttonStatus[BUTTONA]){XInput_ReportData.digital_buttons_2 |= XBOX_B;}
    if (buttonStatus[BUTTONB]){XInput_ReportData.digital_buttons_2 |= XBOX_A;}
    if (buttonStatus[BUTTONX]){XInput_ReportData.digital_buttons_2 |= XBOX_Y;}
    if (buttonStatus[BUTTONY]){XInput_ReportData.digital_buttons_2 |= XBOX_X;}

    if (buttonStatus[BUTTONLB]){XInput_ReportData.digital_buttons_2 |= XBOX_LB;}
    if (buttonStatus[BUTTONRB]){XInput_ReportData.digital_buttons_2 |= XBOX_RB;}
    if (buttonStatus[BUTTONHOME]){XInput_ReportData.digital_buttons_2 |= XBOX_HOME;}

    if (buttonStatus[BUTTONLT]){XInput_ReportData.lt = 0xFF;}
    if (buttonStatus[BUTTONRT]){XInput_ReportData.rt = 0xFF;}    
}
