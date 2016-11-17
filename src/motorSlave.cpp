#include <Arduino.h>
#include <Wire.h>
#include <AFMotor.h>
#include <motorSlave.h>
#include <motorCommand.h>
#include <motorCtrlTransmitStatuses.h>
#include <motorAddress.h>

volatile bool haveCommand = false;
volatile bool calibrating = true;
volatile MotorCommand currentCommand;

void setup() {
  Wire.begin(MOTOR_SLAVE_ADDRESS);
  Wire.onReceive(receiveCommandEvent);
  Wire.onRequest(execCommandEvent);
  Serial.begin(9600);
  Serial.println("Ready to work...");
  calibrate();
}

void loop() {
}

void calibrate() {
  pinMode(SENSORS_ENABLE_PIN, OUTPUT);
  pinMode(STEP_PIN_X, INPUT);
  digitalWrite(SENSORS_ENABLE_PIN, HIGH);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), onInterrupt, CHANGE);
  while (true) {

  }
  calibrating = false;
  Serial.println("Calibrating done");
}

void onInterrupt() {
  digitalWrite(13, analogRead(STEP_PIN_X) > 512);
}

void receiveCommandEvent(int numBytes) {
  Serial.println("receiveCommandEvent");
  unsigned int i = 0;
  unsigned char buffer[COMMAND_LENGTH];

  while (Wire.available()) {
    if (i < COMMAND_LENGTH && !haveCommand && !calibrating) {
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
  } else if (calibrating) {
    Serial.println("Calibrating, ignore");
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
    if (calibrating) {
        Serial.println("Calibrating!");
        Wire.write(STATE_CALIBRATING);

        return;
    }
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
