#ifndef __APPCAMERA_MODEL_H
#define __APPCAMERA_MODEL_H

#include "lvgl.h"
#include "../Page.h"

namespace Page {

class AppCameraModel {
   public:
    camera_fb_t *fb;

   public:
    bool CameraInit(void);
    void CameraDeinit(void);
    bool GetFramebuffer(void);
    void ReleaseFramebuffer(void);

    bool LTR553Init();
    uint32_t GetLTR553AlsCh0Value();
    uint32_t GetLTR553AlsCh1Value();
    uint16_t GetLTR553PsValue();

   private:
};

}  // namespace Page

#endif
