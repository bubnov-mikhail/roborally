#define STEP_PIN_X A6
#define STOP_PIN_X A7
#define STEP_PIN_Y A1
#define STOP_PIN_Y A2
#define SENSORS_ENABLE_PIN A0
#define MOTOR_SLAVE_INTERRUPT_PIN 2

#define GRAB_PIN 10
#define SERVO_PIN 9

void receiveCommandEvent(int numBytes);
void execCommandEvent();
void calibrate();
void doExecCommand();
void onInterrupt();
