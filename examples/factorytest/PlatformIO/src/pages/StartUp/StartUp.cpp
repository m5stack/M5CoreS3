#include "StartUp.h"

using namespace Page;

StartUp::StartUp() : timer(nullptr) {
}

StartUp::~StartUp() {
}

void StartUp::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void StartUp::onViewLoad() {
    LV_LOG_USER(__func__);

    View.Create(_root);
    AttachEvent(_root);
}

void StartUp::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void StartUp::onViewWillAppear() {
    LV_LOG_USER(__func__);

    M5.Speaker.playWav((const uint8_t*)ResourcePool::GetWav("poweron_2_5s"), ~0u, 1, 1);

    timer = lv_timer_create(onTimerUpdate, 50, this);
    lv_anim_timeline_start(View.ui.anim_timeline);
}

void StartUp::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void StartUp::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void StartUp::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void StartUp::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
}

void StartUp::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void StartUp::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void StartUp::Update() {
    if (M5.Display.getBrightness() < 100) {
        M5.Display.setBrightness(M5.Display.getBrightness() + 5);
    }

    if (count > 50) {
        lv_obj_clear_flag(View.ui.img_cores3_diagram, LV_OBJ_FLAG_HIDDEN);
    }
    count++;
}

void StartUp::onTimerUpdate(lv_timer_t* timer) {
    StartUp* instance = (StartUp*)timer->user_data;

    instance->Update();
}

void StartUp::onEvent(lv_event_t* event) {
    StartUp* instance = (StartUp*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->_root) {
        if (code == LV_EVENT_GESTURE) {
            lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
            if (dir == LV_DIR_TOP) {
                // lv_obj_clear_flag(instance->View.ui.img_cores3_diagram,
                //                   LV_OBJ_FLAG_HIDDEN);
            }
#if MONKEY_TEST_ENABLE
        } else if (code == LV_EVENT_LONG_PRESSED || code == LV_EVENT_CLICKED) {
#else
        } else if (code == LV_EVENT_CLICKED) {
#endif
            M5.Speaker.playWav((const uint8_t*)ResourcePool::GetWav("select_0_5s"), ~0u, 1, 1);
            instance->_Manager->Replace("Pages/HomeMenu");
        }
    }
}
