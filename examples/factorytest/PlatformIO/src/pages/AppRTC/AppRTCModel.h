#ifndef __APPRTC_MODEL_H
#define __APPRTC_MODEL_H

#include "lvgl.h"
#include "M5Unified.h"
#include "config.h"

namespace Page {

class AppRTCModel {
   public:
      AppRTCModel() {};
      ~AppRTCModel() {};
      void SetRtcTimer(uint8_t seconds);
      void ShutDown();
      void StartDeepSleep();
      void UpdateBrightness();
   private:
      bool brightness_increase = false;
};

}  // namespace Page

#endif
