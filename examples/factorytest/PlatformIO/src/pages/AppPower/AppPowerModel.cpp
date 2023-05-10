#include "AppPowerModel.h"

using namespace Page;

// P0.2  BUS       LOW[IN]   HIGH[OUT]
// P0.5  USB       LOW[IN]   HIGH[OUT]
// P1.7  BOOST_EN  LOW[OFF]  HIGH[ON]

void AppPowerModel::SetPowerMode(uint8_t mode) {
    switch (mode) {
        case POWER_MODE_USB_IN_BUS_IN:
            M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b100010, 100000L);
            M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b10000000, 100000L); // BOOST_DIS
            break;
        case POWER_MODE_USB_IN_BUS_OUT:
            M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b100000, 100000L);
            M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b000010, 100000L);
            M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN
            break;
        case POWER_MODE_USB_OUT_BUS_IN:
            M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b100000, 100000L);
            M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b000010, 100000L);
            M5.In_I2C.bitOff(AW9523_ADDR, 0x03, 0b10000000,
                             100000L);  // BOOST_DIS
            break;
        case POWER_MODE_USB_OUT_BUS_OUT:
            M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b100010, 100000L);
            M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN
            break;
        default:
            break;
    }

    GetPowerMode();
}

uint8_t AppPowerModel::GetPowerMode() {
    uint8_t data = 0;
    M5.In_I2C.readRegister(AW9523_ADDR, 0x02, &data, 1, 100000L);
    mode_bit.bus = ((data >> 1) & 0b1);
    mode_bit.usb = ((data >> 5) & 0b1);
    // Serial.printf("power mode data raw: %d  bus: %d  usb: %d  mode: %d\r\n",
    //               data, mode_bit.bus, mode_bit.usb, power_mode);
    return power_mode;
}

void AppPowerModel::AxpCHGLedEnable() {
    M5.In_I2C.writeRegister8(AXP2101_ADDR, 0x69, 0b00110101, 100000L);
}

void AppPowerModel::AxpCHGLedDisable() {
    M5.In_I2C.bitOff(AXP2101_ADDR, 0x69, 0b01, 100000L);
}

void AppPowerModel::AxpAdcEnable() {
    M5.In_I2C.writeRegister8(AXP2101_ADDR, 0x30, 0b111111, 100000L);
}

void AppPowerModel::AxpAdcSampling() {
    uint8_t reg     = 0x34;
    uint8_t data[2] = {0};
    M5.In_I2C.readRegister(AXP2101_ADDR, reg, data, 2, 100000L);
    vbat = ((data[0] & 0x3f) << 8) | data[1];
    reg += 2;
    M5.In_I2C.readRegister(AXP2101_ADDR, reg, data, 2, 100000L);
    ts = (((data[0] & 0x3f) << 8) | data[1]) * 0.5f;
    reg += 2;
    M5.In_I2C.readRegister(AXP2101_ADDR, reg, data, 2, 100000L);
    vbus = ((data[0] & 0x3f) << 8) | data[1];
    reg += 2;
    M5.In_I2C.readRegister(AXP2101_ADDR, reg, data, 2, 100000L);
    vsys = (((data[0] & 0x3f) << 8) | data[1]);

    reg += 2;
    M5.In_I2C.readRegister(AXP2101_ADDR, reg, data, 2, 100000L);
    tdie = 22 + ((7274 - ((data[0] << 8) | data[1])) / 20);

    data[0] = M5.In_I2C.readRegister8(AXP2101_ADDR, 0x00, 100000L);

    if (!(data[0] & 0b100000)) {
        vbus = 0.0f;
    }

    if (vbus >= 16375) {
        vbus = 0.0f;
    }
}

uint8_t AppPowerModel::AxpBatIsCharging() {
    uint8_t reg     = 0x01;
    uint8_t data[1] = {0};
    M5.In_I2C.readRegister(AXP2101_ADDR, reg, data, 1, 100000L);
    return (data[0] >> 5) & 0b11;
}
