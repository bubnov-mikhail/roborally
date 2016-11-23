#include <motorCommand.h>

#define FATAL_ERROR_PIN 1
#define MAIN_INTERRUPT_PIN 2
#define BUS_CS_PIN 3

void sendCommand(MotorCommand* currentCommand);
void handleFatalError();
