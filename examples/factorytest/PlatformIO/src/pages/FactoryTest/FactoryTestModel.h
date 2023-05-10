#ifndef __FactoryTest_MODEL_H
#define __FactoryTest_MODEL_H

#include <esp_camera.h>
#include "config.h"
#include "lvgl.h"
#include "M5Unified.h"

namespace Page {

class FactoryTestModel {
   public:
    camera_fb_t *fb;
   public:
    bool CameraInit();
    void CameraDeinit();
    bool GetFramebuffer(void);
    void ReleaseFramebuffer(void);
    bool IsPowerBtnClicked();
    void PortIoInit();
    void PortIoBlink();

   private:
      time_t last_blink_time;
};

}  // namespace Page

#endif
