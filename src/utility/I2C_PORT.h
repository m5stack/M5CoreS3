#ifndef _I2C_PORT_H_
#define _I2C_PORT_H_

#include <Arduino.h>
#include "Wire.h"

/* I2C device scan function */
#define ENABLE_I2C_DEV_SCAN 0

/* I2C_PORT base class */
class I2C_PORT {
   private:
    uint8_t _address;
    TwoWire* _wire;

   protected:
    /* Port interface */
    void init(TwoWire* wire, uint8_t address, int i2cSDA, int i2cSCL);
    bool checkDevAvl();
    void write1Byte(uint8_t subAddress, uint8_t data);
    void write1Byte(uint8_t address, uint8_t subAddress, uint8_t data);
    void write16Bit(uint8_t subAddress, uint8_t data_1, uint8_t data_2);
    uint8_t read8Bit(uint8_t subAddress);
    uint16_t read12Bit(uint8_t subAddress);
    uint16_t read13Bit(uint8_t subAddress);
    uint16_t read16Bit(uint8_t subAddress);
    uint16_t read16Bit_lowFirst(uint8_t subAddress);
    uint32_t read24Bit(uint8_t subAddress);
    uint32_t read32Bit(uint8_t subAddress);
    void readBuff(uint8_t subAddress, int size, uint8_t buff[]);

    //    public:
    //     int I2C_dev_scan();
};

#endif