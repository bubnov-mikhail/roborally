#include <Arduino.h>
#include <Wire.h>
#include "motorCommand.h"
#include "motorCtrlTransmitStatuses.h"
#include "motorAddress.h"

volatile bool haveCommand = false;
volatile MotorCommand currentCommand;
void receiveCommandEvent(int numBytes);
void execCommandEvent();

void setup() {
  Wire.begin(MOTOR_ADDRESS);
  Wire.onReceive(receiveCommandEvent);
  Wire.onRequest(execCommandEvent);
  Serial.begin(9600);
  delay(1000);
  Serial.write("Ready to work...");
}

void loop() {
}

void receiveCommandEvent(int numBytes) {
  Serial.write("receiveCommandEvent");
  unsigned int i = 0;
  unsigned char buffer[COMMAND_LENGTH];

  while (Wire.available()) {
    if (i < COMMAND_LENGTH) {
        buffer[i] = Wire.read();
    } else {
        // if we receive more data then allowed just throw it away
        Wire.read();
    }
    i++;
  }
  currentCommand.xFrom = buffer[0];
  currentCommand.yFrom = buffer[1];
  currentCommand.xTo = buffer[2];
  currentCommand.yTo = buffer[3];
  currentCommand.rFrom = buffer[4];
  currentCommand.rTo = buffer[5];

  haveCommand = true;
  Serial.write("Command received!");
}

void execCommandEvent() {
    Serial.write("execCommandEvent");
    if (!haveCommand) {
        Serial.write("There is no current programm!");
        MotorCtrlTransmitStatuses returnCode = STATE_ERROR_EMPTY_CMD;
        Wire.write(returnCode);

        return;
    }
    Serial.write("programm: ");
    Serial.write(currentCommand.xFrom);
    Serial.write(currentCommand.yFrom);
    Serial.write(currentCommand.xTo);
    Serial.write(currentCommand.yTo);
    Serial.write(currentCommand.rFrom);
    Serial.write(currentCommand.rTo);
    delay(2000);
    haveCommand = false;
    Serial.write("Command executed!");

    MotorCtrlTransmitStatuses returnCode = STATE_OK;
    Wire.write(returnCode);
}
