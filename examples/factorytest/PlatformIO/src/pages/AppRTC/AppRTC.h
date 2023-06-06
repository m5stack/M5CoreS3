#ifndef __APPRTC_PRESENTER_H
#define __APPRTC_PRESENTER_H

#include "AppRTCView.h"
#include "AppRTCModel.h"

namespace Page {

class AppRTC : public PageBase {
   public:
    AppRTC();
    virtual ~AppRTC();

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
    AppRTCView View;
    AppRTCModel Model;
    lv_timer_t* timer;
    bool brightness_flag = false;
};

}  // namespace Page

#endif
