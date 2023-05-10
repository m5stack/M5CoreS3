#include "AppTouch.h"

using namespace Page;

AppTouch::AppTouch() : timer(nullptr) {
}

AppTouch::~AppTouch() {
}

void AppTouch::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppTouch::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_top_center, LV_EVENT_CLICKED);

    M5.Touch.getCount();
    M5.Touch.getTouchPointRaw(0);
    ClearTouchPoint();
}

void AppTouch::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppTouch::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 10, this);
}

void AppTouch::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppTouch::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppTouch::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppTouch::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
}

void AppTouch::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppTouch::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppTouch::Update() {
    static std::uint32_t color = 0;
    auto count                 = M5.Touch.getCount();
    if (!count) {
        ClearTouchPoint();
        return;
    }
    auto t = M5.Touch.getTouchPointRaw(0);
    if (t.y > 68 && t.y < 240) {
        M5.Display.fillRect(t.x - 1, t.y - 1, 2, 2, color);
        if (t_prev.x != 0 && t_prev.y != 0) {
            M5.Display.drawLine(t_prev.x, t_prev.y, t.x, t.y, color);
        }
        t_prev = t;
    }
    if (color % 65536 == 0) {
        M5.Display.fillRect(0, 68, 320, 172, TFT_WHITE);
        ClearTouchPoint();
    }
    color += 32;
}

void AppTouch::onTimerUpdate(lv_timer_t* timer) {
    AppTouch* instance = (AppTouch*)timer->user_data;

    instance->Update();
}

void AppTouch::onEvent(lv_event_t* event) {
    AppTouch* instance = (AppTouch*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        M5.Speaker.playWav(
            (const uint8_t*)ResourcePool::GetWav("select_0_5s"), ~0u, 1, 1);
        if (obj == instance->View.ui.imgbtn_home) {
            instance->_Manager->Replace("Pages/HomeMenu");
        } else if (obj == instance->View.ui.imgbtn_next) {
            instance->_Manager->Replace("Pages/AppI2C");
        } else if (obj == instance->View.ui.btn_top_center) {
            M5.Display.fillRect(0, 68, 320, 172, TFT_WHITE);
            instance->ClearTouchPoint();
        }
    }
}
