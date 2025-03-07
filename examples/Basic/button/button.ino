/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

/*
 * @file button.ino
 * @author tinyu (tinyu@m5stack.com)
 * @brief M5CoreS3 Touch Button / PWR Button Test
 * @version 0.2
 * @date 2025-03-07
 *
 *
 * @Hardwares: M5CoreS3
 * @Platform Version: Arduino M5Stack Board Manager v2.1.3
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5CoreS3: https://github.com/m5stack/M5CoreS3
 */

#include <M5CoreS3.h>

static m5::touch_state_t prev_state;

void setup(void)
{
    auto cfg = M5.config();
    CoreS3.begin(cfg);

    CoreS3.Display.setTextColor(RED);
    CoreS3.Display.setTextDatum(middle_center);
    CoreS3.Display.setFont(&fonts::Orbitron_Light_24);
    CoreS3.Display.setTextSize(1);

    CoreS3.Display.drawString("Touch Button Test", CoreS3.Display.width() / 2, 15);
    CoreS3.Display.fillRect(0, CoreS3.Display.height() - 40, CoreS3.Display.width() / 3, 40, WHITE);
    CoreS3.Display.fillRect(CoreS3.Display.width() / 3, CoreS3.Display.height() - 40, CoreS3.Display.width() / 3, 40,
                            GREEN);
    CoreS3.Display.fillRect((CoreS3.Display.width() / 3) * 2, CoreS3.Display.height() - 40, CoreS3.Display.width() / 3,
                            40, YELLOW);
    CoreS3.Display.drawString("Btn A    Btn B    Btn C", CoreS3.Display.width() / 2, CoreS3.Display.height() - 20);
}

void loop(void)
{
    CoreS3.update();
    auto touchPoint = CoreS3.Touch.getDetail();
    if (prev_state != touchPoint.state) {
        prev_state = touchPoint.state;
    }
    if ((CoreS3.Display.height() > touchPoint.y && touchPoint.y > CoreS3.Display.height() - 40) &&
        touchPoint.state == m5::touch_state_t::touch_begin) {
        CoreS3.Display.fillRect(0, 40, CoreS3.Display.width(), 70, BLACK);
        if (CoreS3.Display.width() / 3 > touchPoint.x && touchPoint.x > 0)
            CoreS3.Display.drawString("Btn A", CoreS3.Display.width() / 2, CoreS3.Display.height() / 2 - 30);
        if ((CoreS3.Display.width() / 3) * 2 > touchPoint.x && touchPoint.x > CoreS3.Display.width() / 3)
            CoreS3.Display.drawString("Btn B", CoreS3.Display.width() / 2, CoreS3.Display.height() / 2 - 30);
        if (CoreS3.Display.width() > touchPoint.x && touchPoint.x > (CoreS3.Display.width() / 3) * 2)
            CoreS3.Display.drawString("Btn C", CoreS3.Display.width() / 2, CoreS3.Display.height() / 2 - 30);
        Serial.printf("x:%d ,y:%d", touchPoint.x, touchPoint.y);
    }
    int state = CoreS3.BtnPWR.wasClicked();
    if (state) {
        CoreS3.Display.fillRect(0, 40, CoreS3.Display.width(), 70, BLACK);
        CoreS3.Display.drawString("Btn PWR", CoreS3.Display.width() / 2, CoreS3.Display.height() / 2 - 30);
    }
}
