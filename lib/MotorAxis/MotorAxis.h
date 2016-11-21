#include <inttypes.h>
#include <AFMotor.h>
#define FULL_SPEED 128
#define LOW_SPEED 20

class MotorAxis
{
    public:
        MotorAxis(uint8_t motornum, uint8_t stepPin, uint8_t stopPin, uint8_t maxCoord);
        void moveTo(uint8_t coord);
        void checkPins(void);
        bool isReachedTarget(void);

    private:
        uint8_t stepPin;
        uint8_t stopPin;
        volatile uint8_t currentCoord;
        uint8_t maxCoord;
        uint8_t targetCoord = 0;
        volatile bool lastStepPinState = false;
        volatile bool lastStopPinState = false;
        AF_DCMotor motor;
};
