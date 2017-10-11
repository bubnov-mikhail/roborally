#pragma once

/*
* Class for selecting and transferring data to/from
* up to 8 devices (each with 2 input and 2 output shift registers)
* Data to be transferred must be of type "uint16_t" or "short"
* Class uses default SPI pins (SCLK, MOSI, MISO)
* Attr "deviceNumber" should start from 0
*/

#include <inttypes.h>
#include <SPI.h>

class DataBus
{
    public:
        DataBus(uint8_t _busCsPin, uint8_t _interruptNumber);
        void begin(); // Initializes the SPI bus
        uint16_t getDeviceData(uint8_t deviceNumber);
        void sendDeviceData(uint8_t deviceNumber, uint16_t data);
        void resetDevices();

    private:
        uint8_t busCsPin; // Pin for activating main SN74HC595N
        uint8_t interruptNumber; // Number for interrupt (not pin!) to be used in SPI.usingInterrupt()
        void select(uint8_t deviceNumber, bool forRead); // Selects device with main SN74HC595N
        uint16_t transferData(uint16_t data, bool toBusCs); // Sends data to main SN74HC595N or other device
};
