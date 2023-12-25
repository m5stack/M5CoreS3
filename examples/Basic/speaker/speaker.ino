/**
 * @file speaker.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief M5CoreS3 Speaker Test
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
#include "audio_file.h"

//----------------------------------------------------------------

/// 8bit unsigned 44.1kHz mono (exclude wav header)
extern const uint8_t wav_unsigned_8bit_click[46000];

/// wav data (include wav header)
extern const uint8_t wav_with_header[230432];

static int menu_x       = 2;
static int menu_y       = 20;
static int menu_w       = 120;
static int menu_h       = 30;
static int menu_padding = 36;

static void tone_up(bool holding) {
    static int tone_hz;
    if (!holding) {
        tone_hz = 100;
    }
    CoreS3.Speaker.tone(++tone_hz, 1000, 1);
}

static void bgm_play_stop(bool holding = false) {
    if (holding) {
        return;
    }
    if (CoreS3.Speaker.isPlaying(0)) {
        CoreS3.Speaker.stop(0);
    } else {
        CoreS3.Speaker.playWav(wav_with_header, sizeof(wav_with_header), ~0u, 0,
                               true);
    }
}

static void m_volume_up(bool) {
    int v = CoreS3.Speaker.getVolume() + 1;
    if (v < 256) {
        CoreS3.Speaker.setVolume(v);
    }
}

static void m_volume_down(bool) {
    int v = CoreS3.Speaker.getVolume() - 1;
    if (v >= 0) {
        CoreS3.Speaker.setVolume(v);
    }
}

static void c_volume_up(bool) {
    int v = CoreS3.Speaker.getChannelVolume(0) + 1;
    if (v < 256) {
        CoreS3.Speaker.setChannelVolume(0, v);
    }
}

static void c_volume_down(bool) {
    int v = CoreS3.Speaker.getChannelVolume(0) - 1;
    if (v >= 0) {
        CoreS3.Speaker.setChannelVolume(0, v);
    }
}

struct menu_item_t {
    const char* title;
    void (*func)(bool);
};

static const menu_item_t menus[] = {
    {"tone", tone_up},         {"play/stop", bgm_play_stop},
    {"ms vol u", m_volume_up}, {"ms vol d", m_volume_down},
    {"ch vol u", c_volume_up}, {"ch vol d", c_volume_down},
};
static constexpr const size_t menu_count = sizeof(menus) / sizeof(menus[0]);

size_t cursor_index = 0;

void draw_menu(size_t index, bool focus) {
    CoreS3.Display.startWrite();
    auto baseColor = CoreS3.Display.getBaseColor();
    CoreS3.Display.setColor(focus ? baseColor : ~baseColor);
    CoreS3.Display.drawRect(menu_x, menu_y + index * menu_padding, menu_w,
                            menu_h);
    CoreS3.Display.drawRect(menu_x + 1, menu_y + index * menu_padding + 1,
                            menu_w - 2, menu_h - 2);
    CoreS3.Display.setColor(focus ? ~baseColor : baseColor);
    CoreS3.Display.fillRect(menu_x + 2, menu_y + index * menu_padding + 2,
                            menu_w - 4, menu_h - 4);
    CoreS3.Display.setTextDatum(textdatum_t::middle_center);
    CoreS3.Display.setTextColor(focus ? baseColor : ~baseColor,
                                focus ? ~baseColor : baseColor);
    CoreS3.Display.drawString(menus[index].title, menu_x + (menu_w >> 1),
                              menu_y + index * menu_padding + (menu_h >> 1));
    CoreS3.Display.endWrite();
}

void select_menu(size_t index) {
    CoreS3.Speaker.playRaw(
        wav_unsigned_8bit_click,
        sizeof(wav_unsigned_8bit_click) / sizeof(wav_unsigned_8bit_click[0]),
        44100, false);
    CoreS3.Display.startWrite();
    draw_menu(cursor_index, false);
    cursor_index = index;
    draw_menu(cursor_index, true);
    CoreS3.Display.endWrite();
}

void move_menu(bool back = false) {
    if (back) {
        select_menu((cursor_index ? cursor_index : menu_count) - 1);
    } else {
        select_menu((cursor_index + 1) % menu_count);
    }
}

void hold_menu(bool holding) {
    if (menus[cursor_index].func != nullptr) {
        menus[cursor_index].func(holding);
    }
}

void setup(void) {
    auto cfg = M5.config();

    CoreS3.begin(cfg);

    {  /// I2S Custom configurations are available if you desire.
        auto spk_cfg = CoreS3.Speaker.config();

        if (spk_cfg.use_dac || spk_cfg.buzzer) {
            /// Increasing the sample_rate will improve the sound quality
            /// instead of increasing the CPU load.
            spk_cfg.sample_rate =
                192000;  // default:64000 (64kHz)  e.g. 48000 , 50000 , 80000 ,
                         // 96000 , 100000 , 128000 , 144000 , 192000 , 200000
        }
        /*
            spk_cfg.pin_data_out=8;
            spk_cfg.pin_bck=7;
            spk_cfg.pin_ws=10;     // LRCK

            /// use single gpio buzzer, ( need only pin_data_out )
            spk_cfg.buzzer = false;

            /// use DAC speaker, ( need only pin_data_out ) ( only GPIO_NUM_25
        or GPIO_NUM_26 ) spk_cfg.use_dac = false;
            // spk_cfg.dac_zero_level = 64; // for Unit buzzer with DAC.

            /// Volume Multiplier
            spk_cfg.magnification = 16;
        //*/
        CoreS3.Speaker.config(spk_cfg);
    }
    CoreS3.Speaker.begin();

    if (CoreS3.Display.width() > CoreS3.Display.height()) {
        CoreS3.Display.setRotation(CoreS3.Display.getRotation() ^ 1);
    }

    if (CoreS3.Display.width() < 100) {
        menu_x = 0;
        menu_y = 10;
        menu_w = CoreS3.Display.width() - 8;
    } else {
        CoreS3.Display.setFont(&fonts::DejaVu18);
    }
    menu_padding = (CoreS3.Display.height() - menu_y) / menu_count;
    menu_h       = menu_padding - 2;

    if (!CoreS3.Speaker.isEnabled()) {
        CoreS3.Display.print("Speaker not found...");
        for (;;) {
            CoreS3.delay(1);
        }
    }

    CoreS3.Display.setEpdMode(epd_mode_t::epd_fastest);
    CoreS3.Display.fillScreen(TFT_DARKGRAY);
    CoreS3.Display.print("SOUND TEST");

    /// The setVolume function can be set the master volume in the range of
    /// 0-255. (default : 64)
    CoreS3.Speaker.setVolume(64);

    /// The setAllChannelVolume function can be set the all virtual channel
    /// volume in the range of 0-255. (default : 255)
    CoreS3.Speaker.setAllChannelVolume(255);

    /// The setChannelVolume function can be set the specified virtual channel
    /// volume in the range of 0-255. (default : 255)
    CoreS3.Speaker.setChannelVolume(0, 255);

    /// play 2000Hz tone sound, 100 msec.
    CoreS3.Speaker.tone(2000, 100);

    CoreS3.delay(100);

    /// play 1000Hz tone sound, 100 msec.
    CoreS3.Speaker.tone(1000, 100);

    CoreS3.delay(100);

    /// stop output sound.
    CoreS3.Speaker.stop();

    CoreS3.delay(500);

    /// The playRaw function can play raw wave data.
    /// 1st argument : data pointer, (supported  int8_t / uint8_t / int16_t)
    /// 2nd argument : Number of data array elements.
    /// 3rd argument : the sampling rate (Hz) (default = 44100)
    /// 4th argument : true=stereo / false=monaural (default = false)
    /// 5th argument : repeat count (default = 1)
    /// 6th argument : virtual channel number (If omitted, use an available
    /// channel.)
    CoreS3.Speaker.playRaw(
        wav_unsigned_8bit_click,
        sizeof(wav_unsigned_8bit_click) / sizeof(wav_unsigned_8bit_click[0]),
        44100, false);

    while (CoreS3.Speaker.isPlaying()) {
        CoreS3.delay(1);
    }  // Wait for the output to finish.

    CoreS3.delay(500);

    // The 2nd argument of the tone function can be used to specify the output
    // time (milliseconds).
    CoreS3.Speaker.tone(440, 1000);  // 440Hz sound  output for 1 seconds.

    while (CoreS3.Speaker.isPlaying()) {
        CoreS3.delay(1);
    }  // Wait for the output to finish.

    CoreS3.delay(500);

    CoreS3.Speaker.setVolume(0);
    CoreS3.Speaker.tone(
        880);  // tone 880Hz sound output. (Keeps output until it stops.)
    for (int i = 0; i <= 64; i++) {
        CoreS3.Speaker.setVolume(
            i);  // Volume can be changed during sound output.
        CoreS3.delay(25);
    }
    CoreS3.Speaker.stop();  // stop sound output.

    CoreS3.delay(500);

    // The tone function can specify a virtual channel number as its 3rd
    // argument. If the tone function is used on the same channel number, the
    // previous tone will be stopped and a new tone will be played.
    CoreS3.Speaker.tone(
        261.626, 1000,
        1);  // tone 261.626Hz  output for 1 seconds, use channel 1
    CoreS3.delay(200);
    CoreS3.Speaker.tone(
        329.628, 1000,
        1);  // tone 329.628Hz  output for 1 seconds, use channel 1
    CoreS3.delay(200);
    CoreS3.Speaker.tone(
        391.995, 1000,
        1);  // tone 391.995Hz  output for 1 seconds, use channel 1

    while (CoreS3.Speaker.isPlaying()) {
        CoreS3.delay(1);
    }  // Wait for the output to finish.

    CoreS3.delay(500);

    // By specifying different channels, multiple sounds can be output
    // simultaneously.
    CoreS3.Speaker.tone(
        261.626, 1000,
        1);  // tone 261.626Hz  output for 1 seconds, use channel 1
    CoreS3.delay(200);
    CoreS3.Speaker.tone(
        329.628, 1000,
        2);  // tone 329.628Hz  output for 1 seconds, use channel 2
    CoreS3.delay(200);
    CoreS3.Speaker.tone(
        391.995, 1000,
        3);  // tone 391.995Hz  output for 1 seconds, use channel 3

    while (CoreS3.Speaker.isPlaying()) {
        CoreS3.delay(1);
    }  // Wait for the output to finish.

    CoreS3.delay(500);

    /// tone data (8bit unsigned wav)
    const uint8_t wavdata[64] = {
        132, 138, 143, 154, 151, 139, 138, 140, 144, 147, 147, 147, 151,
        159, 184, 194, 203, 222, 228, 227, 210, 202, 197, 181, 172, 169,
        177, 178, 172, 151, 141, 131, 107, 96,  87,  77,  73,  66,  42,
        28,  17,  10,  15,  25,  55,  68,  76,  82,  80,  74,  61,  66,
        79,  107, 109, 103, 81,  73,  86,  94,  99,  112, 121, 129};

    /// Using a single wave of data, you can change the tone.
    CoreS3.Speaker.tone(261.626, 1000, 1, true, wavdata, sizeof(wavdata));
    CoreS3.delay(200);
    CoreS3.Speaker.tone(329.628, 1000, 2, true, wavdata, sizeof(wavdata));
    CoreS3.delay(200);
    CoreS3.Speaker.tone(391.995, 1000, 3, true, wavdata, sizeof(wavdata));
    CoreS3.delay(200);

    while (CoreS3.Speaker.isPlaying()) {
        CoreS3.delay(1);
    }  // Wait for the output to finish.

    CoreS3.Display.startWrite();
    for (size_t i = 0; i < menu_count; i++) {
        draw_menu(i, i == cursor_index);
    }
    CoreS3.Display.endWrite();

    bgm_play_stop(false);
}

void loop(void) {
    if (!CoreS3.Display.displayBusy()) {
        static int32_t prev_channelvolume;
        static int32_t prev_mastervolume;
        int32_t m_vol =
            (CoreS3.Speaker.getVolume() * (CoreS3.Display.height() - menu_y)) >>
            8;
        int32_t c_vol = (CoreS3.Speaker.getChannelVolume(0) *
                         (CoreS3.Display.height() - menu_y)) >>
                        8;
        if (prev_mastervolume != m_vol || prev_channelvolume != c_vol) {
            int32_t b         = (255 * (CoreS3.Display.height() - menu_y)) >> 8;
            prev_mastervolume = m_vol;
            prev_channelvolume = c_vol;
            CoreS3.Display.startWrite();
            CoreS3.Display.fillRect(menu_x + menu_w + 1, menu_y, 3, b - m_vol,
                                    CoreS3.Display.getBaseColor());
            CoreS3.Display.fillRect(menu_x + menu_w + 5, menu_y, 3, b - c_vol,
                                    CoreS3.Display.getBaseColor());
            CoreS3.Display.fillRect(menu_x + menu_w + 1, menu_y + b, 3, -m_vol,
                                    ~CoreS3.Display.getBaseColor());
            CoreS3.Display.fillRect(menu_x + menu_w + 5, menu_y + b, 3, -c_vol,
                                    ~CoreS3.Display.getBaseColor());
            CoreS3.Display.endWrite();
        }
    }

    CoreS3.delay(5);
    CoreS3.update();

    auto touch_count = CoreS3.Touch.getCount();
    for (size_t i = 0; i < touch_count; i++) {
        auto detail = CoreS3.Touch.getDetail(i);
        if (((size_t)detail.x - menu_x) < menu_w) {
            size_t index = (detail.y - menu_y) / menu_padding;
            if (index < menu_count) {
                if (detail.wasPressed()) {
                    select_menu(index);
                } else if (index == cursor_index) {
                    if (detail.wasClicked()) {
                        hold_menu(false);
                    } else if (detail.isHolding()) {
                        hold_menu(true);
                    }
                }
            }
        }
    }
}
