#include <Arduino.h>
#define INTERRUPT_PIN 2

uint8_t interruptNumber = digitalPinToInterrupt(INTERRUPT_PIN);
volatile unsigned long changeTime = 0;
volatile unsigned long diffTime = 0;

void onInterrupt();

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(INTERRUPT_PIN, INPUT_PULLUP);
  attachInterrupt(interruptNumber, onInterrupt, CHANGE);
  Serial.begin(9600);
}

void loop()
{
  digitalWrite(13, digitalRead(INTERRUPT_PIN));
  if (0 < diffTime) {
    Serial.println(diffTime);
    changeTime = 0;
    diffTime = 0;
  }
}

void onInterrupt()
{
  if (0 < changeTime) {
    diffTime = millis() - changeTime;
  }
  changeTime = millis();
}
