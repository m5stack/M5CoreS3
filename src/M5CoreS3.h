#ifndef _M5CORES3_H_
#define _M5CORES3_H_

#if ARDUINO_USB_CDC_ON_BOOT
  #define USBSerial Serial
#else
  #include <HWCDC.h>
  // the warning produced by using the 'inline' keyword is a necessary evil as (HWCDC)USBSerial is declared extern and can't be casted as static
  inline HWCDC USBSerial;
#endif

#include <Arduino.h>
#include <Wire.h>
#include "FS.h"
#include "SD.h"

// #include <FastLED.h>
#include "M5Display.h"
#include "AXP2101.h"
// #include "utility/M5Touch.h"   // M5Touch
// #include "utility/M5Button.h"  // M5Buttons, M5Events, Button, Gesture
#include "utility/RTC.h"
// #include "utility/CommUtil.h"
#include "utility/I2C_IMU.h"

// #include "utility/Button.h"

class M5CoreS3 {
   public:
    M5CoreS3(/* args */);
    ~M5CoreS3();
    void begin(bool LCDEnable = true, bool SerialEnable = true,
               bool I2CEnable = false);
    void shutdown();
    int shutdown(int seconds);
    M5Display Lcd = M5Display();

    I2C_IMU IMU;

    AXP2101 Axp;

    RTC Rtc;
};

extern M5CoreS3 M5;
#define m5  M5
#define lcd Lcd
#define imu IMU
#define Imu IMU

#endif
