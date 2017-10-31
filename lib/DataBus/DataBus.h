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
        DataBus(uint8_t _busCsPin, uint8_t _interruptNumber); //Constructor
        void begin(); // Initializes the SPI bus
        void end(); // End the SPI bus
        uint8_t transferDataToDevice(uint8_t data, uint8_t deviceNumber); //Sends and gets a device data
        void select(uint8_t deviceNumber); // Selects device with main SN74HC595N
        void unselectAll(); //Turns all devices into idle state

    private:
        uint8_t busCsPin; // Pin for activating main SN74HC595N
        uint8_t interruptNumber; // Number for interrupt (not pin!) to be used in SPI.usingInterrupt()
        uint8_t transferData(uint8_t data, bool toBusCs); // Sends data to main SN74HC595N or other device
};
