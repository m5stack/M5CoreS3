/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include "M5CoreS3.h"

void setup()
{
    auto cfg = M5.config();
    // if using ext power input(Grove Port or DC input power supply) needs to be set to false.
    // cfg.output_power = false;
    CoreS3.begin(cfg);
    CoreS3.Display.setTextSize(2);

    CoreS3.Power.setChargeCurrent(200);
}

void loop()
{
    CoreS3.Display.clear();

    bool bat_ischarging = CoreS3.Power.isCharging();
    CoreS3.Display.setCursor(10, 30);
    CoreS3.Display.printf("Bat Charging: %d", bat_ischarging);

    int bat_vol = CoreS3.Power.getBatteryVoltage();
    CoreS3.Display.setCursor(10, 50);
    CoreS3.Display.printf("Bat Voltage: %dmv", bat_vol);

    int bat_level = CoreS3.Power.getBatteryLevel();
    CoreS3.Display.setCursor(10, 70);
    CoreS3.Display.printf("Bat Level: %d", bat_level);

    int vbus_vol = CoreS3.Power.getVBUSVoltage();
    CoreS3.Display.setCursor(10, 90);
    CoreS3.Display.printf("VBus Voltage: %dmv", vbus_vol);
    delay(1000);
}
