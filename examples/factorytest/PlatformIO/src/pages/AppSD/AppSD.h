#ifndef __APPSD_PRESENTER_H
#define __APPSD_PRESENTER_H

#include "AppSDView.h"
#include "AppSDModel.h"

namespace Page {

class AppSD : public PageBase {
   public:
    bool scan_flag = true;

   public:
    AppSD();
    virtual ~AppSD();

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

    void ListSDCard(fs::FS& fs, const char* dirname, uint8_t levels);

   private:
    AppSDView View;
    AppSDModel Model;
    lv_timer_t* timer;
};

}  // namespace Page

#endif
