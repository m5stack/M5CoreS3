#ifndef __HOMEMENU_PRESENTER_H
#define __HOMEMENU_PRESENTER_H

#include "HomeMenuView.h"
#include "HomeMenuModel.h"

namespace Page {

class HomeMenu : public PageBase {
   public:
    HomeMenu();
    virtual ~HomeMenu();

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
    HomeMenuView View;
    HomeMenuModel Model;
    lv_timer_t* timer;

    uint8_t factory_click_cout = 0;
};

}  // namespace Page

#endif
