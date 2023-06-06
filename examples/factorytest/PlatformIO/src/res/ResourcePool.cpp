#include "ResourcePool.h"
#include "ResourceManager.h"

static ResourceManager Font_;
static ResourceManager Image_;
static ResourceManager Wav_;

extern "C" {
#define IMPORT_FONT(name)                       \
    do {                                        \
        LV_FONT_DECLARE(name)                   \
        Font_.AddResource(#name, (void*)&name); \
    } while (0)

#define IMPORT_IMG(name)                         \
    do {                                         \
        LV_IMG_DECLARE(name)                     \
        Image_.AddResource(#name, (void*)&name); \
    } while (0)

#define IMPORT_WAV(name, size)                 \
    do {                                       \
        extern const unsigned char name[size]; \
        Wav_.AddResource(#name, (void*)&name); \
    } while (0)

static void Resource_Init() {
    /* Import Fonts */
    IMPORT_FONT(ubuntu_mono_8);
    IMPORT_FONT(alibaba_pht_26);

    /* Import Images */
    IMPORT_IMG(app_camera);
    IMPORT_IMG(app_camera_als);
    IMPORT_IMG(app_camera_als_ps);
    IMPORT_IMG(app_camera_ps);
    IMPORT_IMG(app_i2c_internal);
    IMPORT_IMG(app_i2c_pa);
    IMPORT_IMG(app_i2c_pb);
    IMPORT_IMG(app_i2c_pc);
    IMPORT_IMG(app_imu_graphic);
    IMPORT_IMG(app_imu_raw);
    IMPORT_IMG(app_mic);
    IMPORT_IMG(app_power_ii);
    IMPORT_IMG(app_power_io);
    IMPORT_IMG(app_power_oi);
    IMPORT_IMG(app_power_oo);
    IMPORT_IMG(app_power_bat0);
    IMPORT_IMG(app_power_bat1);
    IMPORT_IMG(app_power_bat2);
    IMPORT_IMG(app_power_busin);
    IMPORT_IMG(app_power_busout);
    IMPORT_IMG(app_power_usbin);
    IMPORT_IMG(app_power_usbout);
    IMPORT_IMG(app_rtc);
    IMPORT_IMG(app_sd);
    IMPORT_IMG(app_touch_min);
    IMPORT_IMG(app_touch);
    IMPORT_IMG(app_wifi);
    IMPORT_IMG(background);
    IMPORT_IMG(ball);
    IMPORT_IMG(compass_face);
    IMPORT_IMG(core_text);
    IMPORT_IMG(cores3_diagram);
    IMPORT_IMG(cross);
    IMPORT_IMG(failed);
    // IMPORT_IMG(home_p);
    IMPORT_IMG(home_r);
    IMPORT_IMG(info_text);
    IMPORT_IMG(menu_bg);
    IMPORT_IMG(menu);
    // IMPORT_IMG(next_p);
    IMPORT_IMG(next_r);
    IMPORT_IMG(pass);
    IMPORT_IMG(s3_text);

    /* Import WAV */
    IMPORT_WAV(poweron_2_5s, 441538);
    IMPORT_WAV(select_0_5s, 88738);
}

} /* extern "C" */

void ResourcePool::Init() {
    Resource_Init();
    Font_.SetDefault((void*)LV_FONT_DEFAULT);
}

lv_font_t* ResourcePool::GetFont(const char* name) {
    return (lv_font_t*)Font_.GetResource(name);
}
const void* ResourcePool::GetImage(const char* name) {
    return Image_.GetResource(name);
}
const void* ResourcePool::GetWav(const char* name) {
    return Wav_.GetResource(name);
}
