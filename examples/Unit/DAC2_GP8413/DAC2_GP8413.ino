/**
 * @file DAC2_GP8413.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief CoreS3 Unit DAC2 Test
 * @version 0.1
 * @date 2024-01-09
 *
 *
 * @Hardwares: CoreS3 + Unit DAC2(GP8413)
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * DFRobot_GP8XXX: https://github.com/DFRobot/DFRobot_GP8XXX
 */

#include <M5CoreS3.h>
#include <DFRobot_GP8XXX.h>

DFRobot_GP8XXX_IIC GP8413(RESOLUTION_15_BIT, 0x59, &Wire);

// range is 0~10000mv
void setDacVoltage(uint16_t vol, uint8_t ch) {
    uint16_t setting_vol = 0;
    if (vol > 10000) {
        vol = 10000;
    }
    if (ch > 1) ch = 1;
    setting_vol = (int16_t)((float)vol / 10000.0f * 32767.0f);
    if (setting_vol > 32767) {
        setting_vol = 32767;
    }
    GP8413.setDACOutVoltage(setting_vol, ch);
}

void AllOutputCtl(uint16_t vol) {
    CoreS3.Display.fillRect(0, 0, CoreS3.Display.width(), 30,
                            vol > 0 ? GREEN : ORANGE);
    CoreS3.Display.drawString("OUTPUT " + String(vol) + "mv",
                              CoreS3.Display.width() / 2, 0);
    // set channel0
    setDacVoltage(vol, 0);
    // set channel1
    setDacVoltage(vol, 1);
}

void setup(void) {
    auto cfg = M5.config();

    CoreS3.begin(cfg);
    CoreS3.Display.setRotation(1);
    CoreS3.Display.setTextDatum(top_center);
    CoreS3.Display.setTextColor(WHITE);
    CoreS3.Display.setFont(&fonts::FreeSansBoldOblique12pt7b);
    CoreS3.Display.setTextSize(1);
    CoreS3.Display.drawString("DAC2", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2 - 20);
    Wire.end();
    Wire.begin(2, 1);

    while (GP8413.begin() != 0) {
        Serial.println("Init Fail!");
        CoreS3.Display.drawString("Init Fail!", CoreS3.Display.width() / 2,
                                  CoreS3.Display.height() / 2);
        delay(1000);
    }
    CoreS3.Display.clear();
    CoreS3.Display.drawString("DAC2", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2 - 20);
    GP8413.setDACOutRange(GP8413.eOutputRange10V);
    CoreS3.Display.drawString("BtnA En/Dis Output", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2 + 20);

    AllOutputCtl(0);
}

bool output = false;

void loop(void) {
    CoreS3.update();
    if (CoreS3.Touch.getCount() && CoreS3.Touch.getDetail().wasPressed()) {
        output = !output;
        if (output) {
            AllOutputCtl(3300);
            // AllOutputCtl(10000);
        } else {
            AllOutputCtl(0);
        }
    }
}
