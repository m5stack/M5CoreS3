/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "M5CoreS3.h"

void setup()
{
    auto cfg = M5.config();
    // cfg.output_power = false;  // if using ext power input(Grove Port or DC input power supply) needs to be set to
    // false.
    CoreS3.begin(cfg);
    CoreS3.Display.setTextSize(2);
}

void loop()
{
    CoreS3.Display.clear();
    int bat_vol = CoreS3.Power.getBatteryVoltage();
    CoreS3.Display.setCursor(10, 30);
    CoreS3.Display.printf("BAT: %dmv", bat_vol);
    int bat_level = CoreS3.Power.getBatteryLevel();
    CoreS3.Display.setCursor(10, 50);
    CoreS3.Display.printf("BAT Level: %d", bat_level);
    delay(1000);
}
