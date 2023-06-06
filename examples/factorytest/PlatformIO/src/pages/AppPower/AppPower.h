#ifndef __APPPOWER_PRESENTER_H
#define __APPPOWER_PRESENTER_H

#include "AppPowerView.h"
#include "AppPowerModel.h"

namespace Page {

class AppPower : public PageBase {
   public:
    uint8_t mode_index = 0;

   public:
    AppPower();
    virtual ~AppPower();

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
    AppPowerView View;
    AppPowerModel Model;
    lv_timer_t* timer;
};

}  // namespace Page

#endif
