#include <Arduino.h>
#define INTERRUPT_PIN 2

uint8_t interruptNumber = digitalPinToInterrupt(INTERRUPT_PIN);
volatile unsigned long changeTime = 0;

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

}

void onInterrupt()
{
  bool state = digitalRead(INTERRUPT_PIN);
  unsigned long diffTime = 0;
  digitalWrite(13, state);
  if (!state) {
    diffTime = millis() - changeTime;
    Serial.println(diffTime);
  }
  changeTime = millis();
}
