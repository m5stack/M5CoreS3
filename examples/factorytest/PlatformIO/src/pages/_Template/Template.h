#ifndef __TEMPLATE_PRESENTER_H
#define __TEMPLATE_PRESENTER_H

#include "TemplateView.h"
#include "TemplateModel.h"

namespace Page {

class Template : public PageBase {
   public:
    typedef struct {
        uint16_t time;
        lv_color_t color;
    } Param_t;

   public:
    Template();
    virtual ~Template();

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
    TemplateView View;
    TemplateModel Model;
    lv_timer_t* timer;
};

}  // namespace Page

#endif
