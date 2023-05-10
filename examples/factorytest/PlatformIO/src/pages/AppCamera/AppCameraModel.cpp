#include "AppCameraModel.h"

using namespace Page;

#define LTR553_ADDR 0x23

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
    .frame_size   = FRAMESIZE_QQVGA,
    .jpeg_quality = 0,
    .fb_count     = 2,
    .fb_location  = CAMERA_FB_IN_PSRAM,
    .grab_mode    = CAMERA_GRAB_WHEN_EMPTY,
};

bool AppCameraModel::CameraInit(void) {
    M5.In_I2C.release();
    esp_err_t err = esp_camera_init(&camera_config);
    if (err != ESP_OK) {
        Serial.printf("Camera Init Failed in AppCameraModel\r\n");
        return false;
    }
    return true;
}

void AppCameraModel::CameraDeinit(void) {
    esp_camera_deinit();
}

bool AppCameraModel::GetFramebuffer(void) {
    fb = esp_camera_fb_get();
    if (!fb) {
        Serial.printf("Camera capture failed in AppCameraModel\r\n");
        return false;
    }
    return true;
}

void AppCameraModel::ReleaseFramebuffer(void) {
    esp_camera_fb_return(fb);
}

bool AppCameraModel::LTR553Init() {
    // soft reset
    uint8_t value_r = M5.In_I2C.readRegister8(LTR553_ADDR, 0x80, 100000L);
    value_r &= (~0x02);
    uint8_t value_w = value_r | 0x02;
    M5.In_I2C.writeRegister8(LTR553_ADDR, 0x80, value_w, 100000L);

    // PS Led Pluse
    M5.In_I2C.writeRegister8(LTR553_ADDR, 0x83, 0x0F, 100000L);
    // ALS Active Mode
    value_r = M5.In_I2C.readRegister8(LTR553_ADDR, 0x80, 100000L);
    value_r &= (~0x01);
    value_w = value_r | 0x01;
    M5.In_I2C.writeRegister8(LTR553_ADDR, 0x80, value_w, 100000L);
    // PS Active Mode
    value_r = M5.In_I2C.readRegister8(LTR553_ADDR, 0x81, 100000L);
    value_r &= (~0x03);
    value_w = value_r | 0x03;
    M5.In_I2C.writeRegister8(LTR553_ADDR, 0x81, value_w, 100000L);
    return true;
}

uint32_t AppCameraModel::GetLTR553AlsCh0Value() {
    uint8_t buffer[2];
    uint32_t result;
    M5.In_I2C.readRegister(LTR553_ADDR, 0x8A, buffer, 2, 100000L);
    result = (buffer[1] << 8) | buffer[0];
    return result;
}

uint32_t AppCameraModel::GetLTR553AlsCh1Value() {
    uint8_t buffer[2];
    uint32_t result;
    M5.In_I2C.readRegister(LTR553_ADDR, 0x88, buffer, 2, 100000L);
    result = (buffer[1] << 8) | buffer[0];
    return result;
}

uint16_t AppCameraModel::GetLTR553PsValue() {
    uint8_t buffer[2];
    uint16_t result;
    M5.In_I2C.readRegister(LTR553_ADDR, 0x8D, buffer, 2, 100000L);
    buffer[0] &= 0xFF;
    buffer[1] &= 0x07;
    result = (buffer[1] << 8) | buffer[0];
    return result;
}
