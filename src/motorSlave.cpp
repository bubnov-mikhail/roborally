#include <Arduino.h>
#include <Wire.h>
#include <motorSlave.h>
#include <motorCommand.h>
#include <motorCtrlTransmitStatuses.h>
#include <motorAddress.h>
#include <MotorAxis.h>
#include <AFMotor.h>

volatile bool haveCommand = false;
volatile bool calibrating = true;
volatile MotorCommand currentCommand;
AF_DCMotor motorX(1);
AF_DCMotor motorY(2);
MotorAxis motorAxisX(&motorX, STEP_PIN_X, STOP_PIN_X, 12);
MotorAxis motorAxisY(&motorY, STEP_PIN_Y, STOP_PIN_Y, 16);
uint8_t interruptNumber = digitalPinToInterrupt(MOTOR_SLAVE_INTERRUPT_PIN);

void setup()
{
    pinMode(GRAB_PIN, OUTPUT);
    pinMode(SERVO_PIN, OUTPUT);
    pinMode(SENSORS_ENABLE_PIN, OUTPUT);
    pinMode(MOTOR_SLAVE_INTERRUPT_PIN, INPUT_PULLUP);

    Wire.begin(MOTOR_SLAVE_ADDRESS);
    Wire.onReceive(receiveCommandEvent);
    Wire.onRequest(execCommandEvent);
    calibrate();
}

void loop()
{
}

void calibrate()
{
    currentCommand.xFrom = 0;
    currentCommand.yFrom = 0;
    currentCommand.xTo = 0;
    currentCommand.yTo = 0;
    currentCommand.rFrom = 0;
    currentCommand.rTo = 0;
    doExecCommand();
    calibrating = false;
}

void receiveCommandEvent(int numBytes)
{
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
        return;
    } else if (calibrating) {
        return;
    }
    currentCommand.xFrom = buffer[0];
    currentCommand.yFrom = buffer[1];
    currentCommand.xTo = buffer[2];
    currentCommand.yTo = buffer[3];
    currentCommand.rFrom = buffer[4];
    currentCommand.rTo = buffer[5];

    haveCommand = true;
}

void execCommandEvent()
{
    if (calibrating) {
        Wire.write(STATE_CALIBRATING);

        return;
    }
    if (!haveCommand) {
        Wire.write(STATE_ERROR_EMPTY_CMD);

        return;
    }

    doExecCommand();
    haveCommand = false;

    Wire.write(STATE_OK);
}

void doExecCommand()
{
    digitalWrite(SENSORS_ENABLE_PIN, HIGH);
    attachInterrupt(interruptNumber, onInterrupt, CHANGE);

    // Move to "From"
    motorAxisX.moveTo(currentCommand.xFrom);
    motorAxisY.moveTo(currentCommand.yFrom);
    while (!motorAxisX.isReachedTarget() || !motorAxisY.isReachedTarget()) {}

    /*
    * @todo Grab, Rotate, Ungrab...
    */

    // Move to "To"
    motorAxisX.moveTo(currentCommand.xTo);
    motorAxisY.moveTo(currentCommand.yTo);
    while (!motorAxisX.isReachedTarget() || !motorAxisY.isReachedTarget()) {}

    detachInterrupt(interruptNumber);
    digitalWrite(SENSORS_ENABLE_PIN, LOW);
}

void onInterrupt()
{
    motorAxisX.checkPins();
    motorAxisY.checkPins();
}
