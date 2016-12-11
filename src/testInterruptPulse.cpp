/*
* Этот тест проверяет схему импульсного фильтра для линии прерываний.
* Схема использует компаратор LM393P и
* разводку от входа на две параллельные RC-цепочки с конденсаторами на 2.2uF и 4.4 uF
* Такая схема регистрирует только повышение сигнала 0->1.
* Регистрация длится несколько миллисекунд.
*/
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
