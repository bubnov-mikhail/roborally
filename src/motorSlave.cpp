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
  Wire.begin(MOTOR_SLAVE_ADDRESS);
  Wire.onReceive(receiveCommandEvent);
  Wire.onRequest(execCommandEvent);
  Serial.begin(9600);
  delay(1000);
  Serial.println("Ready to work...");
}

void loop() {
}

void receiveCommandEvent(int numBytes) {
  Serial.println("receiveCommandEvent");
  unsigned int i = 0;
  unsigned char buffer[COMMAND_LENGTH];

  while (Wire.available()) {
    if (i < COMMAND_LENGTH && !haveCommand) {
        buffer[i] = Wire.read();
    } else {
        // if we receive more data then allowed just throw it away
        Wire.read();
    }
    i++;
  }
  if (haveCommand) {
    Serial.println("Already have command, ignore");
    return;
  }
  currentCommand.xFrom = buffer[0];
  currentCommand.yFrom = buffer[1];
  currentCommand.xTo = buffer[2];
  currentCommand.yTo = buffer[3];
  currentCommand.rFrom = buffer[4];
  currentCommand.rTo = buffer[5];

  haveCommand = true;
  Serial.println("Command received!");
}

void execCommandEvent() {
    Serial.println("execCommandEvent");
    if (!haveCommand) {
        Serial.println("There is no current programm!");
        Wire.write(STATE_ERROR_EMPTY_CMD);

        return;
    }
    Serial.println("programm: ");
    Serial.println(currentCommand.xFrom);
    Serial.println(currentCommand.yFrom);
    Serial.println(currentCommand.xTo);
    Serial.println(currentCommand.yTo);
    Serial.println(currentCommand.rFrom);
    Serial.println(currentCommand.rTo);
    delay(2000);
    haveCommand = false;
    Serial.println("Command executed!");

    Wire.write(STATE_OK);
}
