// Copyright (c) M5Stack. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full
// license information.

#include "M5CoreS3.h"

M5CoreS3::M5CoreS3() {
}

M5CoreS3::~M5CoreS3() {
}

void M5CoreS3::begin(bool LCDEnable, bool USBSerialEnable, bool I2CEnable) {
    if (USBSerialEnable) {
        USBSerial.begin(115200);
        USBSerial.flush();
        delay(1500);
        USBSerial.println("M5CoreS3 initializing...OK");
    }

    USBSerial.printf("APX initial:%d\n", Axp.begin(&Wire1));

    if (LCDEnable) {
        Axp.coreS3_init();
        Lcd.clear();
        Lcd.begin();
    }

    if (I2CEnable) {
        Wire.begin(2, 1, 100000UL);
    }
}

void M5CoreS3::shutdown() {
    Axp.powerOFF();
}

int M5CoreS3::shutdown(int seconds) {
    Rtc.clearIRQ();
    Rtc.SetAlarmIRQ(seconds);
    delay(10);
    Axp.powerOFF();
    return 0;
}

M5CoreS3 M5;
