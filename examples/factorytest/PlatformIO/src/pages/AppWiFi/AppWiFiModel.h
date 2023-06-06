#ifndef __APPWIFI_MODEL_H
#define __APPWIFI_MODEL_H

#include <WiFi.h>
#include "lvgl.h"

namespace Page {

class AppWiFiModel {
   public:
    void Init();
    void Scan();
    int16_t GetScanCount();
    char* GetSSID(uint8_t index);
    int32_t GetRSSI(uint8_t index);

   private:
    uint8_t scan_count = 0;
};

}  // namespace Page

#endif
