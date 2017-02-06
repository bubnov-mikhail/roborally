#include <MotorAxis.h>

#define STEP_PIN_X A0
#define STOP_PIN_X A1
#define STEP_PIN_Y A2
#define STOP_PIN_Y A3
#define MOTOR_X_PORT 1
#define MOTOR_Y_PORT 4
#define SENSORS_ENABLE_PIN 2
#define MAX_COORD_X 15
#define MAX_COORD_Y 20

#define GRAB_PIN 10
#define SERVO_PIN 9

void receiveCommandEvent(int numBytes);
void execCommandEvent();
void calibrate();
void doExecCommand();
void checkAxises(MotorAxis* motorAxisX, MotorAxis* motorAxisY);
