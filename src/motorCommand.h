#define COMMAND_LENGTH 6

struct MotorCommand {
  unsigned char xFrom, yFrom, xTo, yTo, rFrom, rTo;
};
