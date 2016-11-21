#include <MotorAxis.h>

MotorAxis::MotorAxis(uint8_t motornum, uint8_t _stepPin, uint8_t _stopPin, uint8_t _maxCoord)
{
    pinMode(stepPin, INPUT);
    pinMode(stopPin, INPUT);
    currentCoord = maxCoord + 10;
    maxCoord = _maxCoord;
    stepPin = _stepPin;
    stopPin = _stopPin;
    motor = AF_DCMotor motor(motornum);
}

void MotorAxis::moveTo(uint8_t coord)
{
    targetCoord = coord;
    checkPins();
}

bool MotorAxis::isReachedTarget(void)
{
    if (targetCoord == currentCoord) {
        motor.setSpeed(0);
        motor.run(BREAK);
        motor.run(RELEASE);

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
            currentCoord = 0;
        } else {
            currentCoord = maxCoord;
        }
    }
    lastStopPinState = _stopPinState;

    if (isReachedTarget()) {
        return;
    }

    if (targetCoord > currentCoord) {
        motor.run(FORWARD);
        uint8_t dist = targetCoord - currentCoord;
    } else {
        motor.run(BACKWARD);
        uint8_t dist = currentCoord - targetCoord;
    }

    if (dist < 4) {
        motor.setSpeed(LOW_SPEED);
    } else {
        motor.setSpeed(FULL_SPEED);
    }
}
