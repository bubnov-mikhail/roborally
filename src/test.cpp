#include <Arduino.h>
#include <test.h>
#include <DataBus.h>

const byte mainInterruptPin = 2;
const byte busCSPin = 8;
DataBus dataBus(busCSPin, digitalPinToInterrupt(mainInterruptPin));

void setup()
{
  dataBus.begin();
}

void loop()
{
  uint8_t dataA = 0x00;
  uint8_t dataB = 0x00;
  int i;
  dataBus.transferDataToDevice(0, 0);
  dataBus.transferDataToDevice(0, 1);
  for (i = 0; i < 4; i++) {
    bitSet(dataA, i);
    dataBus.transferDataToDevice(dataA, 0);
    bitSet(dataB, 3 - i);
    dataBus.transferDataToDevice(dataB, 1);
    delay(200);
  }
  for (i = 4; i >= 0; i--) {
    bitClear(dataA, i);
    dataBus.transferDataToDevice(dataA, 0);
    bitClear(dataB, 3 - i);
    dataBus.transferDataToDevice(dataB, 1);
    delay(200);
  }
}
