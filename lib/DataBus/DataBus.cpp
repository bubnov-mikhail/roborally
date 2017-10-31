#include <DataBus.h>

DataBus::DataBus(uint8_t _busCsPin, uint8_t _interruptNumber)
{
    busCsPin = _busCsPin;
    interruptNumber = _interruptNumber;
}

void DataBus::begin()
{
    pinMode(busCsPin, OUTPUT);
    digitalWrite(busCsPin, HIGH);
    SPI.begin();
    SPI.usingInterrupt(interruptNumber);
    unselectAll();
}

void DataBus::end()
{
    SPI.end();
}

/**
 * @param uint8_t DeviceNumber Device number starting with 0 for the first device
 * @param uint8_t Data Data to Send
 * @return uint8_t Data from the device
 */
uint8_t DataBus::transferDataToDevice(uint8_t data, uint8_t deviceNumber)
{
    select(deviceNumber);
    uint8_t receivedData = transferData(data, false);
    unselectAll();

    return receivedData;
}

void DataBus::unselectAll()
{
    transferData(0x00, true);
}

/**
 * @param uint8_t DeviceNumber Device number starting with 0 for the first device
 */
void DataBus::select(uint8_t deviceNumber)
{
    uint8_t select = 0x00;
    select = 1 << deviceNumber;
    transferData(select, true);
}

uint8_t DataBus::transferData(uint8_t data, bool toBusCs)
{
    if (toBusCs) {
        digitalWrite(busCsPin, LOW);
        delayMicroseconds(120); //We need this delay for 2andNot chip has a time to switch his outputs
    }
    uint8_t receivedData = SPI.transfer(data);
    if (toBusCs) {
        digitalWrite(busCsPin, HIGH);
    }

    return receivedData;
}
