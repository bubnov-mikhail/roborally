#define STEP_PIN_X A0
#define STOP_PIN_X A1
#define STEP_PIN_Y A6
#define STOP_PIN_Y A7
#define SENSORS_ENABLE_PIN A2
#define MOTOR_SLAVE_INTERRUPT_PIN 2

#define GRAB_PIN 10
#define SERVO_PIN 9

void receiveCommandEvent(int numBytes);
void execCommandEvent();
void calibrate();
void doExecCommand();
void onInterrupt();
