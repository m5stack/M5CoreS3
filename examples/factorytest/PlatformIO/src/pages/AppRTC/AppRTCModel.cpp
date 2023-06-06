#include "AppRTCModel.h"

using namespace Page;

void AppRTCModel::SetRtcTimer(uint8_t seconds) {
    M5.In_I2C.writeRegister8(BM8563_ADDR, 0x0e, 0b10000010, 100000L);
    M5.In_I2C.writeRegister8(BM8563_ADDR, 0x0f, seconds, 100000L);
    M5.In_I2C.writeRegister8(BM8563_ADDR, 0x01, 0b01, 100000L);
}

void AppRTCModel::ShutDown() {
    M5.In_I2C.bitOn(AXP2101_ADDR, 0x41, 1 << 1, 100000L);
    M5.In_I2C.writeRegister8(AXP2101_ADDR, 0x25, 0b00011011, 100000L);
    M5.In_I2C.writeRegister8(AXP2101_ADDR, 0x10, 0b00110001, 100000L);
}

void AppRTCModel::StartDeepSleep() {
    // INTEN_P0 TF_DETECT ES7210 EN[0] DIS[1]
    M5.In_I2C.writeRegister8(AW9523_ADDR, 0x06, 0b11111111, 100000L);
    // INTEN_P1 AW88298 FT6336 EN[0] DIS[1] Clear INT
    M5.In_I2C.writeRegister8(AW9523_ADDR, 0x07, 0b11111011, 100000L);
    M5.In_I2C.readRegister8(AW9523_ADDR, 0x00, 100000L);
    M5.In_I2C.readRegister8(AW9523_ADDR, 0x01, 100000L);
    pinMode(21, INPUT_PULLUP);
    time_t start = millis();
    while (true) {
        delay(10);
        if (millis() - start > 1000) {
            Serial.println("Touch INT Timeout");
            break;
        }
        M5.update();
    }
    delay(300);
    // GPIO21 <- AW9523 INT <- AW9523 P1.2 <- Touch INT
    esp_sleep_enable_ext0_wakeup(GPIO_NUM_21, 0);
    M5.Lcd.fillScreen(TFT_BLACK);
    M5.Lcd.sleep();
    M5.Lcd.waitDisplay();
    esp_deep_sleep_start();
}

void AppRTCModel::UpdateBrightness() {
    if (brightness_increase) {
        M5.Display.setBrightness(M5.Display.getBrightness() + 15);
        if (M5.Display.getBrightness() >= 100) {
            brightness_increase = false;
        }
    } else {
        M5.Display.setBrightness(M5.Display.getBrightness() - 15);
        if (M5.Display.getBrightness() <= 55) {
            brightness_increase = true;
        }
    }
}