#ifndef __APPPOWER_MODEL_H
#define __APPPOWER_MODEL_H

#include "lvgl.h"
#include "M5Unified.h"
#include "config.h"

namespace Page {

class AppPowerModel {
   public:
    union {
        struct {
            uint8_t bus : 1;
            uint8_t usb : 1;
            uint8_t reserve : 6;
        } mode_bit;
        uint8_t power_mode = 0x00;
    };

   float vbat, ts, vbus, vsys, tdie;

   public:
   void SetPowerMode(uint8_t mode);
   uint8_t GetPowerMode();
   void AxpCHGLedEnable();
   void AxpCHGLedDisable();
   void AxpAdcEnable();;
   void AxpAdcSampling();
   uint8_t AxpBatIsCharging();  // 0: not charging, 1: charge 2: discharg
   private:
};

}  // namespace Page

#endif
