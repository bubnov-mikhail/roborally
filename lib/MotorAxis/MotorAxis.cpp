#include <MotorAxis.h>

MotorAxis::MotorAxis(AF_DCMotor* _motor, uint8_t _stepPin, uint8_t _stopPin, uint8_t _maxCoord)
{
    currentCoord = _maxCoord;
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
    if (targetCoord > currentCoord) {
        motor->run(FORWARD);
    } else if (targetCoord < currentCoord) {
        motor->run(BACKWARD);
    }
    updateSpeed();
}

bool MotorAxis::isReachedTarget(void)
{
    if (targetCoord == currentCoord) {
        motor->setSpeed(0);
        motor->run(RELEASE);

        return true;
    }

    return false;
}

void MotorAxis::checkPins(void)
{
    if (isReachedTarget()) {
        return;
    }

    checkStepPin();
    checkStopPin();

    if (isReachedTarget()) {
        return;
    }
}

void MotorAxis::checkStepPin(void)
{
    bool _stepPinState = !digitalRead(stepPin);
    if (_stepPinState && !lastStepPinState) {
        if (targetCoord > currentCoord) {
            currentCoord = min(currentCoord + 1, maxCoord);
        } else if (targetCoord < currentCoord) {
            currentCoord = max(currentCoord - 1, 0);
        }
        updateSpeed();
    }
    lastStepPinState = _stepPinState;
}

void MotorAxis::checkStopPin(void)
{
    bool _stopPinState = !digitalRead(stopPin);
    if (_stopPinState && !lastStopPinState) {
        if (lastStepPinState) {
            // If We have step interrupt + stop interupt - this is 0 coord
            currentCoord = 0;
        } else {
            // If we have only stop interrupt - this is maximum coord
            currentCoord = maxCoord;
        }
        updateSpeed();
    }
    lastStopPinState = _stopPinState;
}

void MotorAxis::updateSpeed(void)
{
  uint8_t dist = abs(currentCoord - targetCoord);
  if (dist < 4 && dist > 0) {
      motor->setSpeed(lowSpeed);
  } else {
      motor->setSpeed(fullSpeed);
  }
}
