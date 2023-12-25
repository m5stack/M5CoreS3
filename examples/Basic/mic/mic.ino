/**
 * @file mic.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5CoreS3 Microphone Record Test
 * @version 0.1
 * @date 2023-12-18
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

static constexpr const size_t record_number     = 256;
static constexpr const size_t record_length     = 320;
static constexpr const size_t record_size       = record_number * record_length;
static constexpr const size_t record_samplerate = 17000;
static int16_t prev_y[record_length];
static int16_t prev_h[record_length];
static size_t rec_record_idx  = 2;
static size_t draw_record_idx = 0;
static int16_t *rec_data;

void setup(void) {
    auto cfg = M5.config();

    CoreS3.begin(cfg);

    CoreS3.Display.startWrite();
    CoreS3.Display.setRotation(1);
    CoreS3.Display.setTextDatum(top_center);
    CoreS3.Display.setTextColor(WHITE);
    CoreS3.Display.setFont(&fonts::FreeSansBoldOblique12pt7b);

    rec_data = (typeof(rec_data))heap_caps_malloc(record_size *

                                                      sizeof(int16_t),
                                                  MALLOC_CAP_8BIT);
    memset(rec_data, 0, record_size * sizeof(int16_t));
    CoreS3.Speaker.setVolume(255);

    /// Since the microphone and speaker cannot be used at the same time,
    // turn
    /// off the speaker here.
    CoreS3.Speaker.end();
    CoreS3.Mic.begin();
    CoreS3.Display.fillCircle(130, 15, 8, RED);
    CoreS3.Display.drawString("REC", 180, 3);
}

void loop(void) {
    CoreS3.update();

    if (CoreS3.Mic.isEnabled()) {
        static constexpr int shift = 6;
        auto data                  = &rec_data[rec_record_idx * record_length];
        if (CoreS3.Mic.record(data, record_length, record_samplerate)) {
            data = &rec_data[draw_record_idx * record_length];

            int32_t w = CoreS3.Display.width();
            if (w > record_length - 1) {
                w = record_length - 1;
            }
            for (int32_t x = 0; x < w; ++x) {
                CoreS3.Display.writeFastVLine(x, prev_y[x], prev_h[x],
                                              TFT_BLACK);
                int32_t y1 = (data[x] >> shift);
                int32_t y2 = (data[x + 1] >> shift);
                if (y1 > y2) {
                    int32_t tmp = y1;
                    y1          = y2;
                    y2          = tmp;
                }
                int32_t y = ((CoreS3.Display.height()) >> 1) + y1;
                int32_t h = ((CoreS3.Display.height()) >> 1) + y2 + 1 - y;
                prev_y[x] = y;
                prev_h[x] = h;
                CoreS3.Display.writeFastVLine(x, prev_y[x], prev_h[x], WHITE);
            }

            CoreS3.Display.display();
            CoreS3.Display.fillCircle(130, 15, 8, RED);
            CoreS3.Display.drawString("REC", 180, 3);
            if (++draw_record_idx >= record_number) {
                draw_record_idx = 0;
            }
            if (++rec_record_idx >= record_number) {
                rec_record_idx = 0;
            }
        }
    }

    if (CoreS3.BtnPWR.wasClicked()) {
        auto cfg               = CoreS3.Mic.config();
        cfg.noise_filter_level = (cfg.noise_filter_level + 8) & 255;
        CoreS3.Mic.config(cfg);
        CoreS3.Display.clear();
        CoreS3.Display.fillCircle(130, 15, 8, GREEN);
        CoreS3.Display.drawString("NF:" + String(cfg.noise_filter_level), 180,
                                  3);
        delay(2000);
        CoreS3.Display.clear();

    } else if (M5.Touch.getCount() && M5.Touch.getDetail(0).wasClicked()) {
        if (CoreS3.Speaker.isEnabled()) {
            CoreS3.Display.clear();
            while (CoreS3.Mic.isRecording()) {
                delay(1);
            }
            /// Since the microphone and speaker cannot be used at the same
            /// time, turn off the microphone here.
            CoreS3.Mic.end();
            CoreS3.Speaker.begin();

            CoreS3.Display.fillTriangle(130 - 8, 15 - 8, 130 - 8, 15 + 8,
                                        130 + 8, 15, 0x1c9f);
            CoreS3.Display.drawString("PLAY", 180, 3);
            int start_pos = rec_record_idx * record_length;
            if (start_pos < record_size) {
                CoreS3.Speaker.playRaw(&rec_data[start_pos],
                                       record_size - start_pos,
                                       record_samplerate, false, 1, 0);
            }
            if (start_pos > 0) {
                CoreS3.Speaker.playRaw(rec_data, start_pos, record_samplerate,
                                       false, 1, 0);
            }
            do {
                delay(1);
                CoreS3.update();
            } while (CoreS3.Speaker.isPlaying());

            /// Since the microphone and speaker cannot be used at the same
            /// time, turn off the speaker here.
            CoreS3.Speaker.end();
            CoreS3.Mic.begin();

            CoreS3.Display.clear();
            CoreS3.Display.fillCircle(130, 15, 8, RED);
            CoreS3.Display.drawString("REC", 180, 3);
        }
    }
}
