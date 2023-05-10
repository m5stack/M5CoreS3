#include "AppSDModel.h"

using namespace Page;

bool AppSDModel::SDInit() {
    init_flag = SD.begin(GPIO_NUM_4, SPI, 25000000);
    return init_flag;
}

void AppSDModel::SDDeinit() {
    SD.end();
    init_flag = false;
}

bool AppSDModel::GetInitFlag() {
    return init_flag;
}

void AppSDModel::ClearInitFlag() {
    init_flag = false;
}

bool AppSDModel::IsSDCardExist() {
    return (bool)!((M5.In_I2C.readRegister8(AW9523_ADDR, 0x00, 100000L) >> 4) & 0x01);
}
