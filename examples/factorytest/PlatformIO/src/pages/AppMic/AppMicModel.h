#ifndef __APPMIC_MODEL_H
#define __APPMIC_MODEL_H

#include "lvgl.h"
#include "config.h"

namespace Page {

class AppMicModel {
   public:
    int16_t mic_buf[2][MIC_BUF_SIZE];
    int16_t prev_y[MIC_BUF_SIZE];
    uint8_t buf_index = 0;
   public:
      bool ReadMicData();
      bool IsMicEnable();
      bool IsSpeakerEnable();
      void MicBegin();
      void MicEnd();
   private:
};

}  // namespace Page

#endif
