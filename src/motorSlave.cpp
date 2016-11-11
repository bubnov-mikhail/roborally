#include <Arduino.h>
#include <Wire.h>
#include "motorCommand.h"
#include "motorCtrlTransmitStatuses.h"
#include "motorAddress.h"

void receiveCommandEvent(int numBytes);

void setup() {
  Wire.begin(MOTOR_ADDRESS);
  Wire.onReceive(receiveCommandEvent);
  Serial.begin(9600);
  delay(1000);
  Serial.write("Ready...");
}

void loop() {
}

void receiveCommandEvent(int numBytes) {
  Serial.write("receiveCommandEvent");
  unsigned int i = 0;

  while (Wire.available() && i < sizeof(lastCommand)) {
    lastCommand[i] = Wire.read();
    i++;
  }
  Serial.write("Command received!");
}
