#include <Arduino.h>
//#include <Print.h>
#include <test.h>
#include <SPI.h>
#include <LiquidCrystal.h>

const byte latchPin = 8;
const byte buttonAPin = 2;
const byte buttonBPin = 4;
const byte interruptPin = 3;
const String buttonAStateMsg = "Button A: ";
const String buttonBStateMsg = "Button B: ";
const String impulseLengthMsg = "Delay: ";

LiquidCrystal lcd(13, 12, 11, 10,  9,  8);
uint8_t lastData = 0;

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
  attachInterrupt(digitalPinToInterrupt(interruptPin), onInterrupt, CHANGE);

  //SPI.begin();
  /* Включаем защёлку */
  //pinMode(latchPin, OUTPUT);
  //digitalWrite(latchPin, HIGH);
}

void loop()
{
  // delay(1000);
  // digitalWrite(latchPin, LOW);
  // uint8_t data = SPI.transfer(0);
  // digitalWrite(latchPin, HIGH);
  // if (data != lastData) {
  //   Serial.println((int)data);
  //   Serial.println(data, BIN);
  //   Serial.println("");
  //   lastData = data;
  // }
}

void onInterrupt()
{
  bool buttonAState = digitalRead(buttonAPin);
  bool buttonBState = digitalRead(buttonBPin);
  bool interruptState = digitalRead(interruptPin);

  if (interruptState) {
    lcd.setCursor(0, 0);
    lcd.print(buttonAStateMsg + buttonAState);
    lcd.setCursor(0, 1);
    lcd.print(buttonBStateMsg + buttonBState);
  }
}
