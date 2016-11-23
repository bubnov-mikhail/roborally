#include <DataBus.h>

DataBus::DataBus(uint8_t _busCsPin, uint8_t _interruptNumber)
{
    busCsPin = _busCsPin;
    interruptNumber = _interruptNumber;
}

void DataBus::begin()
{
    SPI.begin();
    SPI.usingInterrupt(interruptNumber);
    pinMode(busCsPin, OUTPUT);
    resetDevices();
}

uint16_t DataBus::getDeviceData(uint8_t deviceNumber)
{
    select(deviceNumber, true);

    return transferData(0, false);
}

void DataBus::sendDeviceData(uint8_t deviceNumber, uint16_t data)
{
    select(deviceNumber, false);
    transferData(data, false);
}

void DataBus::resetDevices()
{
    uint16_t resetData = 0xFFFF;
    transferData(resetData, true);
}

void DataBus::select(uint8_t deviceNumber, bool forRead)
{
    deviceNumber += (forRead)
        ? 1
        : 0
    ;
    uint16_t select = 0xFFFF;
    bitClear(select, deviceNumber);
    transferData(select, true);
}

uint16_t DataBus::transferData(uint16_t data, bool toBusCs)
{
    SPI.beginTransaction (SPISettings(2000000, MSBFIRST, SPI_MODE0));
    if (toBusCs) {
        digitalWrite(busCsPin, LOW);
    }
    uint16_t receivedData = SPI.transfer16(data);

    if (toBusCs) {
        digitalWrite(busCsPin, HIGH);
    }
    SPI.endTransaction();

    return receivedData;
}
