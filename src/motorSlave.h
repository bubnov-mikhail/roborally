#define STEP_PIN_X A0
#define STOP_PIN_X A1
#define STEP_PIN_Y A2
#define STOP_PIN_Y A3
#define SENSORS_ENABLE_PIN 2
#define MAX_COORD_X 15
#define MAX_COORD_Y 20

#define GRAB_PIN 10
#define SERVO_PIN 9

void receiveCommandEvent(int numBytes);
void execCommandEvent();
void calibrate();
void doExecCommand();
void checkAxises();
