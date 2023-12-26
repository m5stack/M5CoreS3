/**
 * @file ltr553.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5CoreS3 LTR553 Test
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
#include "M5CoreS3.h"

Ltr5xx_Init_Basic_Para device_init_base_para = LTR5XX_BASE_PARA_CONFIG_DEFAULT;

uint16_t read_ps_value;
uint16_t read_als_value;

void setup() {
    auto cfg = M5.config();
    CoreS3.begin(cfg);
    CoreS3.Display.setTextColor(GREEN);
    CoreS3.Display.setTextDatum(middle_center);
    CoreS3.Display.setFont(&fonts::Orbitron_Light_24);
    CoreS3.Display.setTextSize(1);

    device_init_base_para.ps_led_pulse_freq   = LTR5XX_LED_PULSE_FREQ_40KHZ;
    device_init_base_para.ps_measurement_rate = LTR5XX_PS_MEASUREMENT_RATE_50MS;
    device_init_base_para.als_gain            = LTR5XX_ALS_GAIN_48X;

    if (!CoreS3.Ltr553.begin(&device_init_base_para)) {
        CoreS3.Display.drawString("Ltr553 Init Fail",
                                  CoreS3.Display.width() / 2,
                                  CoreS3.Display.height() / 2);
        while (1) {
            delay(10);
        }
    }

    CoreS3.Display.drawString("Ltr553 Init Success", CoreS3.Display.width() / 2,
                              CoreS3.Display.height() / 2);
    // active ps
    CoreS3.Ltr553.setPsMode(LTR5XX_PS_ACTIVE_MODE);

    // active als
    CoreS3.Ltr553.setAlsMode(LTR5XX_ALS_ACTIVE_MODE);
    // not active ps
    // CoreS3.Ltr553.setPsMode(LTR5XX_PS_STAND_BY_MODE);

    // not active als
    // CoreS3.Ltr553.setAlsMode(LTR5XX_ALS_STAND_BY_MODE);
}

void loop() {
    CoreS3.Display.clear();
    read_ps_value  = CoreS3.Ltr553.getPsValue();
    read_als_value = CoreS3.Ltr553.getAlsValue();

    CoreS3.Display.drawString(
        "PS:" + String(read_ps_value) + " / " + "ALS:" + String(read_als_value),
        CoreS3.Display.width() / 2, CoreS3.Display.height() / 2);

    Serial.printf("ps value = %d\r\n", read_ps_value);
    Serial.printf("als value = %d\r\n", read_als_value);
    delay(100);
}
