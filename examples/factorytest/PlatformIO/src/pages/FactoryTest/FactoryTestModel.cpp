#include "FactoryTestModel.h"

using namespace Page;

static camera_config_t camera_config = {
    .pin_pwdn     = -1,
    .pin_reset    = -1,
    .pin_xclk     = 2,
    .pin_sscb_sda = 12,
    .pin_sscb_scl = 11,

    .pin_d7 = 47,
    .pin_d6 = 48,
    .pin_d5 = 16,
    .pin_d4 = 15,
    .pin_d3 = 42,
    .pin_d2 = 41,
    .pin_d1 = 40,
    .pin_d0 = 39,

    .pin_vsync = 46,
    .pin_href  = 38,
    .pin_pclk  = 45,

    .xclk_freq_hz = 20000000,
    .ledc_timer   = LEDC_TIMER_0,
    .ledc_channel = LEDC_CHANNEL_0,

    .pixel_format = PIXFORMAT_RGB565,
    .frame_size   = FRAMESIZE_QVGA,
    .jpeg_quality = 0,
    .fb_count     = 2,
    .fb_location  = CAMERA_FB_IN_PSRAM,
    .grab_mode    = CAMERA_GRAB_WHEN_EMPTY,
};

bool FactoryTestModel::CameraInit(void) {
    M5.In_I2C.release();
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        Serial.printf("Camera Init Failed in FactoryTestModel\r\n");
        return false;
    }
    return true;
}

void FactoryTestModel::CameraDeinit(void) {
    esp_camera_deinit();
}

bool FactoryTestModel::GetFramebuffer(void) {
    fb = esp_camera_fb_get();
    if (!fb) {
        Serial.printf("Camera capture failed in FactoryTestModel\r\n");
        return false;
    }
    return true;
}

void FactoryTestModel::ReleaseFramebuffer(void) {
    esp_camera_fb_return(fb);
}

bool FactoryTestModel::IsPowerBtnClicked() {
    if (M5.In_I2C.readRegister8(AXP2101_ADDR, 0x49, 100000L) & 0b1000) {
        // RW1C
        M5.In_I2C.bitOn(AXP2101_ADDR, 0x49, 1 << 3, 100000L);
        return true;
    }
    return false;
}

void FactoryTestModel::PortIoInit() {
    pinMode(PORTA_PIN_0, OUTPUT);
    pinMode(PORTA_PIN_1, OUTPUT);
    pinMode(PORTB_PIN_0, OUTPUT);
    pinMode(PORTB_PIN_1, OUTPUT);
    pinMode(PORTC_PIN_0, OUTPUT);
    pinMode(PORTC_PIN_1, OUTPUT);

    digitalWrite(PORTA_PIN_0, LOW);
    digitalWrite(PORTA_PIN_1, LOW);
    digitalWrite(PORTB_PIN_0, LOW);
    digitalWrite(PORTB_PIN_1, LOW);
    digitalWrite(PORTC_PIN_0, LOW);
    digitalWrite(PORTC_PIN_1, LOW);
}

void FactoryTestModel::PortIoBlink() {
    if (millis() - last_blink_time > 500) {
        last_blink_time = millis();
        digitalWrite(PORTA_PIN_0, !digitalRead(PORTA_PIN_0));
        digitalWrite(PORTA_PIN_1, !digitalRead(PORTA_PIN_1));
        digitalWrite(PORTB_PIN_0, !digitalRead(PORTB_PIN_0));
        digitalWrite(PORTB_PIN_1, !digitalRead(PORTB_PIN_1));
        digitalWrite(PORTC_PIN_0, !digitalRead(PORTC_PIN_0));
        digitalWrite(PORTC_PIN_1, !digitalRead(PORTC_PIN_1));
    }
}