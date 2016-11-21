#include <Arduino.h>
#include <Wire.h>
#include <main.h>
#include <motorCtrlTransmitStatuses.h>
#include <motorAddress.h>

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  delay(2000);
  Wire.begin();
  /* DEMO */
  /* xFrom, yFrom, xTo, yTo, rFrom, rTo */
  MotorCommand currentCommand = {0, 0, 3, 10, 0, 2};
  sendCommand(currentCommand);
}

void loop()
{
}

void handleFatalError()
{
    while (true) {
      digitalWrite(FATAL_ERROR_PIN, HIGH);
      delay(500);
      digitalWrite(FATAL_ERROR_PIN, LOW);
      delay(500);
    }
}

void sendCommand(MotorCommand *currentCommand)
{
  Wire.beginTransmission(MOTOR_SLAVE_ADDRESS);
  Wire.write(currentCommand->xFrom);
  Wire.write(currentCommand->yFrom);
  Wire.write(currentCommand->xTo);
  Wire.write(currentCommand->yTo);
  Wire.write(currentCommand->rFrom);
  Wire.write(currentCommand->rTo);
  Wire.endTransmission();

  Wire.requestFrom(MOTOR_SLAVE_ADDRESS, 1);
  while (Wire.available()) {
    switch (Wire.read()) {
        case STATE_OK:
            break;
        case STATE_CALIBRATING:
            delay(3000);
            sendCommand(currentCommand);
            break;
        case STATE_ERROR_EMPTY_CMD:
            handleFatalError();
            break;
        case STATE_ERROR_UNKNOWN:
            handleFatalError();
            break;
        default:
          handleFatalError();
    }
  }
}
