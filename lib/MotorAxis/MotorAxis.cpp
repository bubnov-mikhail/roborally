#include <MotorAxis.h>

MotorAxis::MotorAxis(AF_DCMotor* _motor, uint8_t _stepPin, uint8_t _stopPin, uint8_t _maxCoord)
{
    currentCoord = maxCoord + 10;
    maxCoord = _maxCoord;
    stepPin = _stepPin;
    stopPin = _stopPin;
    lastStepPinState = false;
    lastStopPinState = false;
    motor = _motor;
    pinMode(stepPin, INPUT);
    pinMode(stopPin, INPUT);
}

void MotorAxis::moveTo(uint8_t coord)
{
    targetCoord = coord;
    checkPins();
}

bool MotorAxis::isReachedTarget(void)
{
    if (targetCoord == currentCoord) {
        motor->setSpeed(0);
        motor->run(RELEASE);
        motor->run(BRAKE);

        return true;
    }

    return false;
}

void MotorAxis::checkPins(void)
{
    bool _stepPinState = (analogRead(stepPin) > 512);
    if (_stepPinState && !lastStepPinState) {
        if (targetCoord > currentCoord) {
            currentCoord++;
        } else {
            currentCoord--;
        }
    }
    lastStepPinState = _stepPinState;

    bool _stopPinState = (analogRead(stopPin) > 512);
    if (_stopPinState && !lastStopPinState) {
        if (lastStepPinState) {
            // If We have step interrupt + stop interupt - this is 0 coord
            currentCoord = 0;
        } else {
            // If we have only stop interrupt - this is maximum coord
            currentCoord = maxCoord;
        }
    }
    lastStopPinState = _stopPinState;

    if (isReachedTarget()) {
        return;
    }

    uint8_t dist;
    if (targetCoord > currentCoord) {
        motor->run(FORWARD);
        dist = targetCoord - currentCoord;
    } else {
        motor->run(BACKWARD);
        dist = currentCoord - targetCoord;
    }

    if (dist < 4) {
        motor->setSpeed(LOW_SPEED);
    } else {
        motor->setSpeed(FULL_SPEED);
    }
}
