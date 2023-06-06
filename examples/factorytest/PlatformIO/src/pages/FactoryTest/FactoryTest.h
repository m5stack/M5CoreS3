#ifndef __FactoryTest_PRESENTER_H
#define __FactoryTest_PRESENTER_H

#include "FactoryTestView.h"
#include "FactoryTestModel.h"

namespace Page {

class FactoryTest : public PageBase {
   public:
    FactoryTest();
    virtual ~FactoryTest();

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
    FactoryTestView View;
    FactoryTestModel Model;
    lv_timer_t* timer;

    int8_t factory_test_step = -1;
    bool ui_update_flag = false;
    uint16_t test_fail_flag = 0;
    m5gfx::touch_point_t t_prev;

};

}  // namespace Page

#endif
