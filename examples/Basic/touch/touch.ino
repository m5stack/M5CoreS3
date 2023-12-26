/**
 * @file touch.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5CoreS3 Touch Test
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
    CoreS3.Display.setFont(&fonts::Orbitron_Light_24);
    CoreS3.Display.setTextSize(1);

    CoreS3.Display.drawString("Touch Test", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2);
}

int prev_x = -1;
int prev_y = -1;

static m5::touch_state_t prev_state;

void loop(void) {
    CoreS3.update();

    auto t = CoreS3.Touch.getDetail();
    if (prev_state != t.state) {
        prev_state                                  = t.state;
        static constexpr const char* state_name[16] = {
            "none", "touch", "touch_end", "touch_begin",
            "___",  "hold",  "hold_end",  "hold_begin",
            "___",  "flick", "flick_end", "flick_begin",
            "___",  "drag",  "drag_end",  "drag_begin"};
        M5_LOGI("%s", state_name[t.state]);
        CoreS3.Display.fillRect(0, 0, CoreS3.Display.width(), 140, BLACK);

        CoreS3.Display.drawString(state_name[t.state],
                                  CoreS3.Display.width() / 2,
                                  CoreS3.Display.height() / 2 - 30);
    }
    if (prev_x != t.x || prev_y != t.y) {
        CoreS3.Display.fillRect(0, 140, CoreS3.Display.width(), 100, BLACK);
        CoreS3.Display.drawString(
            "X:" + String(t.x) + " / " + "Y:" + String(t.y),
            CoreS3.Display.width() / 2, 200);
        prev_x = t.x;
        prev_y = t.y;
        CoreS3.Display.fillCircle(prev_x, prev_y, 4, GREEN);
    }
}
