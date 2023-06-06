#include "AppCamera.h"

using namespace Page;

AppCamera::AppCamera() : timer(nullptr) {
}

AppCamera::~AppCamera() {
}

void AppCamera::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    Model.LTR553Init();
    Model.CameraInit();

    AttachEvent(_root);
    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);
}

void AppCamera::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 30, this);
}

void AppCamera::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppCamera::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppCamera::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
    Model.ReleaseFramebuffer();
    Model.CameraDeinit();
}

void AppCamera::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppCamera::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppCamera::Update() {
    if (Model.GetFramebuffer()) {
        M5.Display.startWrite();
        M5.Display.setAddrWindow(25, 90, 160, 120);
        M5.Display.writePixels((uint16_t*)Model.fb->buf,
                               int(Model.fb->len / 2));
        M5.Display.endWrite();
    }
    Model.ReleaseFramebuffer();

    uint32_t als_ch0 = Model.GetLTR553AlsCh0Value();
    uint32_t als_ch1 = Model.GetLTR553AlsCh1Value();
    uint16_t ps      = Model.GetLTR553PsValue();

    // Serial.printf("als ch0: %d, als ch1: %d, ps: %d\r\n", als_ch0, als_ch1,
    // ps);

    uint8_t als_num = map(als_ch0, 0, 0x50, 0, 9);
    uint8_t ps_num  = map(ps, 0, 0x800, 0, 9);

    // Serial.printf("als num: %d, ps num: %d\r\n", als_num, ps_num);

    for (size_t i = 0; i < 8; i++) {
        lv_obj_add_flag(View.ui.obj_ltr553_als_list[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(View.ui.obj_ltr553_ps_list[i], LV_OBJ_FLAG_HIDDEN);
    }

    for (size_t i = 0; i < (als_num > 8 ? 8 : als_num); i++) {
        lv_obj_clear_flag(View.ui.obj_ltr553_als_list[i], LV_OBJ_FLAG_HIDDEN);
    }

    for (size_t i = 0; i < (ps_num > 8 ? 8 : ps_num); i++) {
        lv_obj_clear_flag(View.ui.obj_ltr553_ps_list[i], LV_OBJ_FLAG_HIDDEN);
    }
}

void AppCamera::onTimerUpdate(lv_timer_t* timer) {
    AppCamera* instance = (AppCamera*)timer->user_data;

    instance->Update();
}

void AppCamera::onEvent(lv_event_t* event) {
    AppCamera* instance = (AppCamera*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->_root) {
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LEAVE) {
            // instance->_Manager->Pop();
        }
    } else {
        if (code == LV_EVENT_CLICKED) {
            if (obj == instance->View.ui.imgbtn_home) {
                M5.Speaker.playWav(
                    (const uint8_t*)ResourcePool::GetWav("select_0_5s"), ~0u, 1,
                    1);
                instance->_Manager->Replace("Pages/HomeMenu");
            } else if (obj == instance->View.ui.imgbtn_next) {
                Serial.print("AppCamera -> AppMic\r\n");
                instance->_Manager->Replace("Pages/AppMic");
            }
        }
    }
}
