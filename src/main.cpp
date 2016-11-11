#include <Arduino.h>
#include <Wire.h>
#include "motorCommand.h"
#include "motorCtrlTransmitStatuses.h"
#include "motorAddress.h"

void sendCommand(MotorCommand currentCommand);

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
  Wire.begin();
  /* xFrom, yFrom, xTo, yTo, rFrom, rTo */
  MotorCommand currentCommand = {0, 0, 3, 10, 0, 2};
  sendCommand(currentCommand);
}

void loop() {
}

void sendCommand(MotorCommand currentCommand) {
  digitalWrite(LED_BUILTIN, HIGH);
  Wire.beginTransmission(MOTOR_SLAVE_ADDRESS);
  Wire.write(currentCommand.xFrom);
  Wire.write(currentCommand.yFrom);
  Wire.write(currentCommand.xTo);
  Wire.write(currentCommand.yTo);
  Wire.write(currentCommand.rFrom);
  Wire.write(currentCommand.rTo);
  Wire.endTransmission();
  digitalWrite(LED_BUILTIN, LOW);

  Wire.requestFrom(MOTOR_SLAVE_ADDRESS, 1);
  while (Wire.available()) {
    switch (Wire.read()) {
      case STATE_OK:
        while (true) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(200);
          digitalWrite(LED_BUILTIN, LOW);
          delay(200);
        }
        break;
      case STATE_ERROR_EMPTY_CMD:
        while (true) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(1000);
          digitalWrite(LED_BUILTIN, LOW);
          delay(200);
        }
        break;
      case STATE_ERROR_UNKNOWN:
        while (true) {
          digitalWrite(LED_BUILTIN, HIGH);
          delay(3000);
          digitalWrite(LED_BUILTIN, LOW);
          delay(200);
        }
        break;
        default:
          while (true) {
            digitalWrite(LED_BUILTIN, HIGH);
          }
    }
  }
}
