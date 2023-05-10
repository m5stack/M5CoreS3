#ifndef __APPMIC_PRESENTER_H
#define __APPMIC_PRESENTER_H

#include "AppMicView.h"
#include "AppMicModel.h"
#include "M5Unified.h"

namespace Page {

class AppMic : public PageBase {
   public:
    AppMic();
    virtual ~AppMic();

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
    static void draw_mic_wave_event(lv_event_t* event);

   private:
    AppMicView View;
    AppMicModel Model;
    lv_timer_t* timer;

    M5Canvas canvas[2];
};

}  // namespace Page

#endif
