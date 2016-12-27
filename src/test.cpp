#include <Arduino.h>
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
  /* Выставим на защёлке сначала низкий, потом - высокий уровни.
   * Сдвиговый регистр запомнит уровни сигналов на входах и сможет
   * их нам потом отдать бит за битом.
   */
  digitalWrite(REG_LATCH, LOW);
  delay(10);
  digitalWrite(REG_LATCH, HIGH);
  /* Читаем запомненные состояния входов. Ноль шлём просто потому,
   * что transfer() одновременно и шлёт, и принимает. Да и вообще,
   * MOSI не подключена (:
   */
  uint8_t data = SPI.transfer(0);
  if (data != lastData) {
    Serial.println((int)data);
    lastData = data;
  }
}
