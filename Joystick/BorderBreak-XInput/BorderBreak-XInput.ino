#include "LUFAConfig.h"
#include <LUFA.h>
#include "XInput_HID.h"
#define BUTTON_COUNT 4
#define LED_COUNT 3

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A1; // Analog output pin that the LED is attached to

// Last state of the buttons
byte ledPins[LED_COUNT] = {7,8,9};
byte buttonPins[BUTTON_COUNT] = {2,3,4,5};
byte buttonOrder[BUTTON_COUNT] = {BUTTONB,BUTTONA,BUTTONY,BUTTONX};

int buttonState[BUTTON_COUNT] = {0,0,0,0};
int lastButtonState[BUTTON_COUNT] = {0,0,0,0};
int ledState[3] = {HIGH,LOW,HIGH};
int sensorValue;
int sensorValue2;
int outputValue;
int outputValue2;

void setup() {
  //additional gnd
  pinMode(10, OUTPUT);
  delay(10);
  digitalWrite(10, LOW);
  // Initialize Button Pins
  for (int i=0; i<BUTTON_COUNT;i++){
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  for (int i=0; i<LED_COUNT;i++){
    pinMode(ledPins[i], OUTPUT);
  }

  SetupHardware();
  GlobalInterruptEnable();
}

unsigned long currTime = 0;
unsigned long blueTime = 0;
unsigned long pinkTime = 0;
boolean blueMode = false;
boolean pinkMode = false;
void loop() {
  currTime = millis();
  //light led
  for (int i=0; i<LED_COUNT;i++){
    digitalWrite(ledPins[i],ledState[i]);
  }

  for (int i=0; i<BUTTON_COUNT;i++){
    lastButtonState[i] = buttonState[i]; 
    buttonState[i] = !digitalRead(buttonPins[i]);

    if (buttonState[i] != lastButtonState[i]){
          buttonStatus[buttonOrder[i]] = buttonState[i];
    }
    
  }

  //update leds
  if (!buttonState[2] && lastButtonState[2]){
    blueTime = millis();
    blueMode = true;
  }
  if (!buttonState[0] && lastButtonState[0]){
    pinkTime = millis();
    pinkMode = true;
  }
  if (!buttonState[1] && lastButtonState[1]){
    pinkTime = millis();
    pinkMode = true;
  }
  
  if (currTime - blueTime > 500){
    blueTime = 0;
    blueMode = false;
  }
  if (currTime - pinkTime > 500){
    pinkTime = 0;
    pinkMode = false;
  }

  if (buttonState[0] || buttonState[1]){
    ledState[0] = LOW;
    ledState[1] = LOW;
    ledState[2] = LOW;
  } else if (buttonState[2]){
    ledState[0] = HIGH;
    ledState[1] = HIGH;
    ledState[2] = LOW;
  }
  else if (buttonState[3]){
    ledState[0] = LOW;
    ledState[1] = HIGH;
    ledState[2] = LOW;
  } else if (pinkMode) {
    ledState[0] = LOW;
    ledState[1] = LOW;
    ledState[2] = LOW;
  } else {
    ledState[0] = HIGH;
    ledState[1] = blueMode ? HIGH : LOW;
    ledState[2] = blueMode ? LOW : HIGH;
  }
  
  // Read analogs
  sensorValue = analogRead(analogInPin);
  sensorValue2 = analogRead(analogInPin2);
  buttonStatus[AXISLX] = map(sensorValue, 170, 860, 0, 255);
  buttonStatus[AXISLY] = -1*map(sensorValue2, 150, 900, 0, 255);
  
  send_pad_state();
  delay(2);
}

