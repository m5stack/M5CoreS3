#include "I2C_PORT.h"

/* Port interface */
void I2C_PORT::init(TwoWire* wire, uint8_t address, int i2cSDA, int i2cSCL) {
    _wire    = wire;
    _address = address;
    _wire->begin(i2cSDA, i2cSCL);
}

bool I2C_PORT::checkDevAvl() {
    _wire->beginTransmission(_address);
    return (_wire->endTransmission() ? true : false);
}

void I2C_PORT::write1Byte(uint8_t subAddress, uint8_t data) {
    _wire->beginTransmission(_address);
    _wire->write(subAddress);
    _wire->write(data);
    _wire->endTransmission();
}

void I2C_PORT::write1Byte(uint8_t address, uint8_t subAddress, uint8_t data) {
    _wire->beginTransmission(address);
    _wire->write(subAddress);
    _wire->write(data);
    _wire->endTransmission();
}

uint8_t I2C_PORT::read8Bit(uint8_t subAddress) {
    _wire->beginTransmission(_address);
    _wire->write(subAddress);
    _wire->endTransmission();
    _wire->requestFrom(_address, (size_t)1);
    return _wire->read();
}

uint16_t I2C_PORT::read12Bit(uint8_t subAddress) {
    uint8_t buff[2];
    readBuff(subAddress, 2, buff);
    return (buff[0] << 4) + buff[1];
}

uint16_t I2C_PORT::read13Bit(uint8_t subAddress) {
    uint8_t buff[2];
    readBuff(subAddress, 2, buff);
    return (buff[0] << 5) + buff[1];
}

uint16_t I2C_PORT::read16Bit(uint8_t subAddress) {
    uint8_t buff[2];
    readBuff(subAddress, 2, buff);
    return (buff[0] << 8) + buff[1];
}

uint32_t I2C_PORT::read24Bit(uint8_t subAddress) {
    uint8_t buff[4];
    readBuff(subAddress, 3, buff);
    return (buff[0] << 16) + (buff[1] << 8) + buff[2];
}

uint32_t I2C_PORT::read32Bit(uint8_t subAddress) {
    uint8_t buff[4];
    readBuff(subAddress, 4, buff);
    return (buff[0] << 24) + (buff[1] << 16) + (buff[2] << 8) + buff[3];
}

void I2C_PORT::readBuff(uint8_t subAddress, int size, uint8_t buff[]) {
    _wire->beginTransmission(_address);
    _wire->write(subAddress);
    _wire->endTransmission();
    _wire->requestFrom(_address, (size_t)size);
    for (int i = 0; i < size; i++) {
        buff[i] = _wire->read();
    }
}

uint16_t I2C_PORT::read16Bit_lowFirst(uint8_t subAddress) {
    uint8_t buff[2];
    readBuff(subAddress, 2, buff);
    return buff[0] + (buff[1] << 8);
}

void I2C_PORT::write16Bit(uint8_t subAddress, uint8_t data_1, uint8_t data_2) {
    _wire->beginTransmission(_address);
    _wire->write(subAddress);
    _wire->write(data_1);
    _wire->write(data_2);
    _wire->endTransmission();
}