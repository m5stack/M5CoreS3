/**
 * @file wakeup.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5CoreS3 Timer Wakeup Test
 * @version 0.1
 * @date 2023-12-25
 *
 *
 * @Hardwares: M5CoreS3
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5CoreS3: https://github.com/m5stack/M5CoreS3
 */

#include <M5CoreS3.h>

void setup(void) {
    auto cfg = M5.config();
    CoreS3.begin(cfg);

    CoreS3.Display.setTextColor(GREEN);
    CoreS3.Display.setTextDatum(middle_center);
    CoreS3.Display.setFont(&fonts::FreeSerifItalic18pt7b);
    CoreS3.Display.setTextSize(1);

    CoreS3.Display.drawString("Touch", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2 - 60);
    CoreS3.Display.drawString("to sleep", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2 - 20);
    CoreS3.Display.drawString("After 5s", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2 + 20);
    CoreS3.Display.drawString("Wakeup", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2 + 60);
}

void loop(void) {
    CoreS3.update();

    if (CoreS3.Touch.getCount() && CoreS3.Touch.getDetail(0).wasClicked()) {
        CoreS3.Power.timerSleep(5);
        // CoreS3.Power.timerSleep(const rtc_time_t& time);
        // CoreS3.Power.timerSleep(const rtc_date_t& date, const rtc_time_t&
        // time);
        // CoreS3.Power.powerOff(); shutdown
    }
}
