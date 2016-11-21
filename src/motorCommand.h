#include <inttypes.h>
#define COMMAND_LENGTH 6

struct MotorCommand {
  uint8_t xFrom, yFrom, xTo, yTo, rFrom, rTo;
};
