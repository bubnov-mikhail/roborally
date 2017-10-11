#pragma once

#include <inttypes.h>
#include <Arduino.h>
#include <AFMotor.h>

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
        volatile uint8_t targetCoord;
        uint8_t maxCoord;
        const static uint8_t fullSpeed = 255;
        const static uint8_t lowSpeed = 128;
        volatile bool lastStepPinState;
        volatile bool lastStopPinState;
        AF_DCMotor* motor;
        void checkStepPin(void);
        void checkStopPin(void);
        void updateSpeed(void);
};
