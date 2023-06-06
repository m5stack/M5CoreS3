#ifndef __APPI2C_PRESENTER_H
#define __APPI2C_PRESENTER_H

#include "AppI2CView.h"
#include "AppI2CModel.h"

namespace Page {

class AppI2C : public PageBase {
   public:
    uint8_t port_index = 0;
    bool scan_flag = false;
   public:
    AppI2C();
    virtual ~AppI2C();

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
    AppI2CView View;
    AppI2CModel Model;
    lv_timer_t* timer;
};

}  // namespace Page

#endif
