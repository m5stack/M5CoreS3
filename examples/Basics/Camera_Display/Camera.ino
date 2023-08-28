/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: Camera example.
* Date: 2023/6/17
*******************************************************************************
*/
#include <M5CoreS3.h>
#include "esp_camera.h"
#include <WiFi.h>
#include <M5Unified.h>
#include "CoreS3_GC0308.hpp"

// Configure the name and password of the connected wifi.
// 配置所连接wifi的名称、密码
const char* ssid     = "**********";
const char* password = "**********";

uint16_t img [76800]PROGMEM = {};

#define PWDN_GPIO_NUM  -1
#define RESET_GPIO_NUM -1
#define XCLK_GPIO_NUM  -1
#define SIOD_GPIO_NUM  -1
#define SIOC_GPIO_NUM  -1

#define Y2_GPIO_NUM 39
#define Y3_GPIO_NUM 40
#define Y4_GPIO_NUM 41
#define Y5_GPIO_NUM 42
#define Y6_GPIO_NUM 15
#define Y7_GPIO_NUM 16
#define Y8_GPIO_NUM 48
#define Y9_GPIO_NUM 47

#define VSYNC_GPIO_NUM 46
#define HREF_GPIO_NUM  38
#define PCLK_GPIO_NUM  45

void startCameraServer();
void swap16Array(uint16_t *arr, size_t len);
void showingImage(void);

void setup() {
    M5.begin();
    M5.Log.setEnableColor(m5::log_target_serial, false);
    Serial.begin(115200);
    Serial.println();

    camera_config_t config;
    config.ledc_channel  = LEDC_CHANNEL_0;
    config.ledc_timer    = LEDC_TIMER_0;
    config.pin_d0        = Y2_GPIO_NUM;
    config.pin_d1        = Y3_GPIO_NUM;
    config.pin_d2        = Y4_GPIO_NUM;
    config.pin_d3        = Y5_GPIO_NUM;
    config.pin_d4        = Y6_GPIO_NUM;
    config.pin_d5        = Y7_GPIO_NUM;
    config.pin_d6        = Y8_GPIO_NUM;
    config.pin_d7        = Y9_GPIO_NUM;
    config.pin_xclk      = XCLK_GPIO_NUM;
    config.pin_pclk      = PCLK_GPIO_NUM;
    config.pin_vsync     = VSYNC_GPIO_NUM;
    config.pin_href      = HREF_GPIO_NUM;
    config.pin_sccb_sda  = SIOD_GPIO_NUM;
    config.pin_sccb_scl  = SIOC_GPIO_NUM;
    config.pin_pwdn      = PWDN_GPIO_NUM;
    config.pin_reset     = RESET_GPIO_NUM;
    config.xclk_freq_hz  = 20000000;
    config.frame_size    = FRAMESIZE_QVGA;
    config.pixel_format  = PIXFORMAT_RGB565;
    config.grab_mode     = CAMERA_GRAB_WHEN_EMPTY;
    config.fb_location   = CAMERA_FB_IN_PSRAM;
    config.jpeg_quality  = 0;
    config.fb_count      = 2;
    config.sccb_i2c_port = M5.In_I2C.getPort();

    // camera init
    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("Camera init failed with error 0x%x", err);
        return;
    }
    if (!cam::GC0308::complementDriver()) {
        M5_LOGE("Failed to complement GC0308");
    }

    WiFi.begin(ssid, password);
    WiFi.setSleep(false);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");

    startCameraServer();
    
    showingImage();

    Serial.print("Camera Ready! Use 'http://");
    Serial.print(WiFi.localIP());
    Serial.println("' to connect");
}

void loop() {
    // Do nothing. Everything is done in another task by the web server
    delay(1000);
}

void swap16Array(uint16_t *arr, size_t len) 
{
    for (size_t i = 0; i < len; i++) 
    {
        arr[i] = ((arr[i] >> 8) & 0xFF) | ((arr[i] << 8) & 0xFF00);
    }
}

void showingImage(void) 
{
    camera_fb_t *fb = NULL;
    fb = esp_camera_fb_get();
    if (!fb) 
    {
        Serial.println("Camera Capture Failed!");
        M5.Lcd.setCursor(0, 0);
        M5.Lcd.print("Camera Capture Failed!");
    } 
    else 
    {
        memcpy(img, fb->buf, fb->len);
        delay(0);
        //M5.Lcd.drawBitmap(0, 0, 320, 240, fb->buf);

        swap16Array(img,76800);
        
        M5.Lcd.drawBitmap(0, 0, 320, 240, img);
    }
    esp_camera_fb_return(fb);
}
