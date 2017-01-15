#include <inttypes.h>
#include <Arduino.h>
#include <AFMotor.h>
#define FULL_SPEED 255
#define LOW_SPEED 255

class MotorAxis
{
    public:
        MotorAxis(AF_DCMotor* _motor, uint8_t stepPin, uint8_t stopPin, uint8_t maxCoord);
        void moveTo(uint8_t coord);
        void checkPins(void);
        bool isReachedTarget(void);

    private:
        uint8_t stepPin;
        uint8_t stopPin;
        volatile uint8_t currentCoord;
        uint8_t maxCoord;
        uint8_t targetCoord;
        volatile bool lastStepPinState;
        volatile bool lastStopPinState;
        AF_DCMotor* motor;
        void checkStepPin(void);
        void checkStopPin(void);
};
