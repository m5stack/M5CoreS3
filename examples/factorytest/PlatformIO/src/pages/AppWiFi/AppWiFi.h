#ifndef __APPWIFI_PRESENTER_H
#define __APPWIFI_PRESENTER_H

#include "AppWiFiView.h"
#include "AppWiFiModel.h"

namespace Page {

class AppWiFi : public PageBase {
   public:
    bool scan_done = false;

   public:
    AppWiFi();
    virtual ~AppWiFi();

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
    AppWiFiView View;
    AppWiFiModel Model;
    lv_timer_t* timer;
};

}  // namespace Page

#endif
