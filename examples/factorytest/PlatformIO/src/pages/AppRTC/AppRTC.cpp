#include "AppRTC.h"

using namespace Page;

AppRTC::AppRTC() : timer(nullptr) {
}

AppRTC::~AppRTC() {
}

void AppRTC::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppRTC::onViewLoad() {
    LV_LOG_USER(__func__);

    View.Create(_root);

    for (size_t i = 0; i < 6; i++) {
        AttachEvent(View.ui.btn_list[i], LV_EVENT_CLICKED);
    }
}

void AppRTC::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppRTC::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void AppRTC::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppRTC::onViewWillDisappear() {
    LV_LOG_USER(__func__);
    M5.Speaker.playWav((const uint8_t*)ResourcePool::GetWav("select_0_5s"), ~0u,
                       1, 1);
}

void AppRTC::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppRTC::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
}

void AppRTC::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppRTC::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppRTC::Update() {
}

void AppRTC::onTimerUpdate(lv_timer_t* timer) {
    AppRTC* instance = (AppRTC*)timer->user_data;

    instance->Update();
}

void AppRTC::onEvent(lv_event_t* event) {
    AppRTC* instance = (AppRTC*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        if (obj == instance->View.ui.btn_list[2]) {
            Serial.print("AppRTC -> HomeMenu\r\n");
            instance->_Manager->Replace("Pages/HomeMenu");
            return;
        }
        M5.Speaker.playWav((const uint8_t*)ResourcePool::GetWav("select_0_5s"),
                           ~0u, 1, 1);
        if (obj == instance->View.ui.btn_list[0]) {
#if MONKEY_TEST_ENABLE
            // ...
#else
            instance->Model.ShutDown();
#endif
        } else if (obj == instance->View.ui.btn_list[1]) {
            instance->Model.UpdateBrightness();
        } else if (obj == instance->View.ui.btn_list[3]) {
            instance->Model.StartDeepSleep();
        } else if (obj == instance->View.ui.btn_list[4]) {
            Serial.print("Sleep & Wakeup after 5s\r\n");
            instance->Model.SetRtcTimer(5);
            instance->Model.ShutDown();
        } else if (obj == instance->View.ui.btn_list[5]) {
            Serial.print("Sleep & Wakeup after 1min\r\n");
            instance->Model.SetRtcTimer(60);
            instance->Model.ShutDown();
        }
    }
}
