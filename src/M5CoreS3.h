#ifndef _M5_CORES3_H_
#define _M5_CORES3_H_

#include "M5Unified.h"
#include "M5GFX.h"
#include "./utility/GC0308.h"
#include "./utility/LTR5XX.h"

namespace m5 {
class M5CoreS3 {
   private:
    /* data */
   public:
    void begin();
    void begin(m5::M5Unified::config_t cfg);

    M5GFX &Display = M5.Display;
    M5GFX &Lcd     = Display;

    IMU_Class &Imu     = M5.Imu;
    Power_Class &Power = M5.Power;
    RTC8563_Class &Rtc = M5.Rtc;
    Touch_Class &Touch = M5.Touch;

    Speaker_Class &Speaker = M5.Speaker;

    Mic_Class &Mic = M5.Mic;

    Button_Class &BtnPWR = M5.BtnPWR;

    /// for internal I2C device
    I2C_Class &In_I2C = m5::In_I2C;

    /// for external I2C device (Port.A)
    I2C_Class &Ex_I2C = m5::Ex_I2C;

    GC0308 Camera;
    LTR5XX Ltr553;

    void update(void);
    void delay(uint32_t msec);
};
}  // namespace m5

extern m5::M5CoreS3 CoreS3;

#endif
