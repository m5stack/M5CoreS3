#ifndef __APPCAMERA_PRESENTER_H
#define __APPCAMERA_PRESENTER_H

#include "AppCameraView.h"
#include "AppCameraModel.h"

namespace Page {

class AppCamera : public PageBase {
   public:
    AppCamera();
    virtual ~AppCamera();

    virtual void onCustomAttrConfig();
    virtual void onViewLoad();
    virtual void onViewDidLoad();
    virtual void onViewWillAppear();
    virtual void onViewDidAppear();
    virtual void onViewWillDisappear();
    virtual void onViewDidDisappear();
    virtual void onViewUnload();
    virtual void onViewDidUnload();

   private:
    void Update();
    void AttachEvent(lv_obj_t* obj) {
        AttachEvent(obj, LV_EVENT_ALL);
    }
    void AttachEvent(lv_obj_t* obj, lv_event_code_t code);
    static void onTimerUpdate(lv_timer_t* timer);
    static void onEvent(lv_event_t* event);

   private:
    AppCameraView View;
    AppCameraModel Model;
    lv_timer_t* timer;
};

}  // namespace Page

#endif
