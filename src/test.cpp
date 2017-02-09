#include <Arduino.h>
#include <Print.h>
#include <test.h>
#include <SPI.h>

#define REG_LATCH 8

uint8_t lastData = 0;

void setup()
{
  Serial.begin(9600);
  Serial.println("Ready");
  SPI.begin();
  /* Включаем защёлку */
  pinMode(REG_LATCH, OUTPUT);
  digitalWrite(REG_LATCH, HIGH);
}

void loop()
{
  delay(1000);
  digitalWrite(REG_LATCH, LOW);
  digitalWrite(REG_LATCH, HIGH);
  uint8_t data = SPI.transfer(0);

  if (data != lastData) {
    Serial.println((int)data);
    Serial.println(data, BIN);
    Serial.println("");
    lastData = data;
  }
}
