#include <Joystick.h>
#define BUTTON_COUNT 4
#define LED_COUNT 3

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogInPin2 = A1; // Analog output pin that the LED is attached to
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  BUTTON_COUNT, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering


// Last state of the buttons
byte ledPins[LED_COUNT] = {7,8,9};
byte buttonPins[BUTTON_COUNT] = {2,3,4,5};

int buttonState[BUTTON_COUNT] = {0,0,0,0};
int lastButtonState[BUTTON_COUNT] = {0,0,0,0};
int ledState[3] = {HIGH,LOW,HIGH};
int currX;
int currY;
int outputValue;
int outputValue2;
int baseX, baseY, minX, maxX, minY, maxY;
#define AXISLX 0
#define AXISLY 1
byte buttonStatus[2];

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

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(0, 255);
  Joystick.setYAxisRange(0, 255);
  
  baseX = analogRead(analogInPin);
  baseY = analogRead(analogInPin2);
  minX = 200;
  minY = 200;
  maxX = 800;
  maxY = 800;
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
          Joystick.setButton(i, buttonState[i]);
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
  currX = analogRead(analogInPin);
  currY = analogRead(analogInPin2);
  if ((currX - baseX < 50)&&(currX - baseX > -50))
    buttonStatus[AXISLX] = 127;
  else if (currX < minX){
    minX = currX-20;
    buttonStatus[AXISLX] = 0;
  }
  else if (currX > maxX){
    maxX = currX+20;
    buttonStatus[AXISLX] = 255;
  } else if (currX > baseX){
    buttonStatus[AXISLX] = map(currX, baseX, maxX, 127, 255);
  } else if (currX < baseX){
    buttonStatus[AXISLX] = map(currX, minX, baseX, 0, 127);
  }
  

  if ((currY - baseY < 50)&&(currY - baseY > -50))
    buttonStatus[AXISLY] = 127;
  else if (currY < minY){
    minY = currY-20;
    buttonStatus[AXISLY] = 0;
  }
  else if (currY > maxY){
    maxY = currY+20;
    buttonStatus[AXISLY] = 255;
  } else if (currY > baseY){
    buttonStatus[AXISLY] = map(currY, baseY, maxY, 127, 255);
  } else if (currY < baseY){
    buttonStatus[AXISLY] = map(currY, minY, baseY, 0, 127);
  }
    buttonStatus[AXISLY] *= -1;
    
  Joystick.setXAxis(buttonStatus[AXISLX]);
  Joystick.setYAxis(buttonStatus[AXISLY]);
  
  delay(2);
}

