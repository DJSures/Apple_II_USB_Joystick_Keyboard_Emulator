#include <Keyboard.h>
#include <Mouse.h>
#include "pitches.h"
#include "Joystick.h"

// ***********************************************************************
// **                                                                   **
// ** Keyboard & Joystick USB HID for Teensy or Pro Micro               **
// ** By DJ Sures (Synthiam.com) (c)2019                                **
// **                                                                   **
// ** Updated: 11/26/2019                                               **
// **                                                                   **
// ***********************************************************************

// uncomment to use for serial terminal debugging rather than usb hid device
// this is so you can see the ascii values to verify
//#define SERIAL_DEBUG

#define strobePin 2
#define resetPin 3
#define kb0Pin 4
#define kb1Pin 5
#define kb2Pin 6
#define kb3Pin 7
#define kb4Pin 8
#define kb5Pin 9
#define kb6Pin 10
#define JoyButton1 15
#define JoyButton2 14
#define JoyAxisX 0
#define JoyAxisY 1
#define Speaker 16

// toggle with CTRL-a two times
// 0 = regular keyboard
// 1 = number pad is arrow keys
int keyboardMode = 0;
int ctrlacnt = 0;

// toggle with CTRL-z two times
// 0 = mouse mode
// 1 = joystick mode
int joystickMode = 0;
int ctrlzcnt = 0;

// hit CTRL-q two times press ALT-F4 (Close current program)
int ctrlqcnt = 0;

void setup() {

#ifdef SERIAL_DEBUG
  Serial.begin(9600);
#else
  Keyboard.begin();
  Mouse.begin();
  Joystick.begin();
#endif

  attachInterrupt(1, strobe, RISING);

  // attachInterrupt(0, reset_pressed, FALLING);

  pinMode(kb0Pin, INPUT);
  pinMode(kb1Pin, INPUT);
  pinMode(kb2Pin, INPUT);
  pinMode(kb3Pin, INPUT);
  pinMode(kb4Pin, INPUT);
  pinMode(kb5Pin, INPUT);
  pinMode(kb6Pin, INPUT);
  pinMode(strobePin, INPUT);
  pinMode(resetPin, INPUT);

  pinMode(JoyButton1, INPUT_PULLUP);
  pinMode(JoyButton2, INPUT_PULLUP);

  tone(Speaker, NOTE_C6, 100);
}

void loop() {

#ifdef SERIAL_DEBUG

  Serial.print("X=");
  Serial.print(analogRead(JoyAxisX));
  Serial.print(",");
  Serial.print(readAxisForJoystickX());
  Serial.print(" Y=");
  Serial.print(analogRead(JoyAxisY));
  Serial.print(",");
  Serial.print(readAxisForJoystickY());
  Serial.print(" B1=");
  Serial.print(digitalRead(JoyButton1));
  Serial.print(" B2=");
  Serial.print(digitalRead(JoyButton2));
  Serial.write("\r\n");

#else

  if (joystickMode == 0) {

    int x = readAxisForMouseX();
    int y = readAxisForMouseY();

    Mouse.move(x, y);

    Joystick.setXAxis(0);
    Joystick.setYAxis(0);

    if (digitalRead(JoyButton1))
      Mouse.press(MOUSE_LEFT);
    else
      Mouse.release(MOUSE_LEFT);

    if (digitalRead(JoyButton2))
      Mouse.press(MOUSE_RIGHT);
    else
      Mouse.release(MOUSE_RIGHT);
  } else {

    int x = readAxisForJoystickX();
    int y = readAxisForJoystickY();

    Joystick.setXAxis(x);
    Joystick.setYAxis(y);

    Joystick.setButton(0, digitalRead(JoyButton1));
    Joystick.setButton(1, digitalRead(JoyButton2));
  }
#endif

  delay(25);
}

int readAxisForJoystickX() {

  int reading = analogRead(JoyAxisX);

  return constrain(map(reading, 210, 1023, 127, -127), -127, 127);
}

int readAxisForJoystickY() {

  int reading = analogRead(JoyAxisY);

  return constrain(map(reading, 210, 1023, 127, -127), -127, 127);
}

int readAxisForMouseX() {

  int reading = analogRead(JoyAxisX);

  reading = map(reading, 210, 1023, 16, -16);

  if (abs(reading) < 4)
    return 0;

  return constrain(reading, -16, 16);
}

int readAxisForMouseY() {

  int reading = analogRead(JoyAxisY);

  reading = map(reading, 210, 1023, 16, -16);

  if (abs(reading) < 4)
    return 0;

  return constrain(reading, -16, 16);
}

void reset_pressed() {

#ifdef SERIAL_DEBUG
  Serial.print("RESET\r\n");
#endif
}

void strobe() {

  int val = digitalRead(kb0Pin) * 1;
  val = digitalRead(kb1Pin) * 2 + val;
  val = digitalRead(kb2Pin) * 4 + val;
  val = digitalRead(kb3Pin) * 8 + val;
  val = digitalRead(kb4Pin) * 16 + val;
  val = digitalRead(kb5Pin) * 32 + val;
  val = digitalRead(kb6Pin) * 64 + val;

#ifdef SERIAL_DEBUG
  // display debug data before conversion
  Serial.print(val);
  Serial.print(",");
#endif

  if (val == 13)
    val = KEY_RETURN;
  else if (val == 27)
    val = KEY_ESC;
  //  else if (val == 8)
  //    val = KEY_LEFT_ARROW;
  else if (val == 21)
    val = KEY_RIGHT_ARROW;
  else if (val == 1) { // a

    ctrlacnt++;

    if (ctrlacnt == 2) {

      ctrlacnt = 0;

      if (keyboardMode == 0) {

        keyboardMode = 1;
        tone(Speaker, NOTE_C5, 100);
      } else {

        keyboardMode = 0;
        tone(Speaker, NOTE_C4, 100);
      }

      return;
    } else {

      tone(Speaker, NOTE_C3, 50);
    }
  } else if (val == 26) { // z

    ctrlzcnt++;

    if (ctrlzcnt == 2) {

      ctrlzcnt = 0;

      if (joystickMode == 0) {

        joystickMode = 1;
        tone(Speaker, NOTE_E5, 100);
      } else {

        joystickMode = 0;
        tone(Speaker, NOTE_E4, 100);
      }

      return;
    } else {

      tone(Speaker, NOTE_E3, 50);
    }
  } else if (val == 17) { // q

    ctrlqcnt++;

    if (ctrlqcnt == 2) {

      ctrlqcnt = 0;

      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.press(KEY_F4);
      delay(100);
      Keyboard.releaseAll();

      tone(Speaker, NOTE_A4, 100);

      return;
    } else {

      tone(Speaker, NOTE_A3, 50);
    }
  } else {

    ctrlzcnt = 0;
    ctrlacnt = 0;
    ctrlqcnt = 0;
  }

  if (keyboardMode == 1) {

    if (val == 56)
      val = KEY_UP_ARROW;
    else if (val == 54)
      val = KEY_RIGHT_ARROW;
    else if (val == 50)
      val = KEY_DOWN_ARROW;
    else if (val == 52)
      val = KEY_LEFT_ARROW;
  }

#ifdef SERIAL_DEBUG
  Serial.print(val);
  Serial.write("\r\n");
  //  Serial.write(val);
#else
  Keyboard.write(val);
#endif
}
