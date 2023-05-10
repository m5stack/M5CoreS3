#ifndef __APPIMU_PRESENTER_H
#define __APPIMU_PRESENTER_H

#include "AppIMUView.h"
#include "AppIMUModel.h"

namespace Page {

class AppIMU : public PageBase {
    public:
        struct ball_t {
        uint16_t x = 0;
        uint16_t y = 0;
        uint16_t r = 0;
        float dir = 0;
    }ball;
    bool calibration_flag = false;
   public:
    AppIMU();
    virtual ~AppIMU();

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

    float CalcuDir(void);
    void MagCalibration(void);

   private:
    AppIMUView View;
    AppIMUModel Model;
    lv_timer_t* timer;

    M5Canvas canvas;
};

}  // namespace Page

#endif
