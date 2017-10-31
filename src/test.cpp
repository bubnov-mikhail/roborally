#include <Arduino.h>
#include <test.h>
#include <LiquidCrystal.h>

const byte buttonAPin = 2;
const byte buttonBPin = 4;
const byte interruptPin = 3;
const String buttonAStateMsg = "A: ";
const String buttonBStateMsg = " B: ";
const String impulseLengthMsg = "Delay: ";

LiquidCrystal lcd(13, 12, 11, 10,  9,  8);
volatile uint8_t interrupts = 0;

void setup()
{
  // начинаем работу с экраном. Сообщаем объекту количество
  // строк и столбцов. Опять же, вызывать pinMode не требуется:
  // функция begin сделает всё за нас
  lcd.begin(16, 2);
  // печатаем сообщение на первой строке
  lcd.print("I am ready!");
  pinMode(buttonAPin, INPUT);
  pinMode(buttonBPin, INPUT);
  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), onInterrupt, RISING);
}

void loop()
{
}

void onInterrupt()
{
  bool buttonAState = digitalRead(buttonAPin);
  bool buttonBState = digitalRead(buttonBPin);
  bool interruptState = digitalRead(interruptPin);
  interrupts++;
  if (interruptState) {
    lcd.setCursor(0, 0);
    lcd.print(buttonAStateMsg + buttonAState + buttonBStateMsg + buttonBState);
    lcd.setCursor(0, 1);
    lcd.print(interrupts);
  }
}
