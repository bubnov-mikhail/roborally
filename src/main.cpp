#include <Arduino.h>
#include <Wire.h>
#include <main.h>
#include <motorCtrlTransmitStatuses.h>
#include <motorAddress.h>
#include <DataBus.h>

DataBus dataBus(BUS_CS_PIN, digitalPinToInterrupt(MAIN_INTERRUPT_PIN));

void setup()
{
  pinMode(FATAL_ERROR_PIN, OUTPUT);
  pinMode(MAIN_INTERRUPT_PIN, INPUT_PULLUP);

  delay(2000);
  Wire.begin();
  dataBus.begin();

  /* DEMO */
  /* xFrom, yFrom, xTo, yTo, rFrom, rTo */
  MotorCommand currentCommand = {4, 0, 7, 10, 0, 2};
  sendCommand(&currentCommand);
}

void loop()
{
}

void handleFatalError(bool loop = true)
{
    do {
      digitalWrite(FATAL_ERROR_PIN, HIGH);
      delay(500);
      digitalWrite(FATAL_ERROR_PIN, LOW);
      delay(500);
    } while (loop);
    delay(1000);
}

void sendCommand(MotorCommand* currentCommand)
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
            digitalWrite(FATAL_ERROR_PIN, HIGH);
            break;
        case STATE_CALIBRATING:
            handleFatalError(false);
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
