#include "AppWiFi.h"

using namespace Page;

AppWiFi::AppWiFi() : timer(nullptr) {
}

AppWiFi::~AppWiFi() {
}

void AppWiFi::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppWiFi::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    Model.Init();

    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_top_center, LV_EVENT_CLICKED);
}

void AppWiFi::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppWiFi::onViewWillAppear() {
    LV_LOG_USER(__func__);
    timer = lv_timer_create(onTimerUpdate, 100, this);

    Model.Scan();
    lv_obj_clear_flag(View.ui.label_scaning, LV_OBJ_FLAG_HIDDEN);
}

void AppWiFi::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppWiFi::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppWiFi::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppWiFi::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
    scan_done = false;
    WiFi.scanDelete();
}

void AppWiFi::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppWiFi::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppWiFi::Update() {
    if (Model.GetScanCount() >= 0 && !scan_done) {
        lv_obj_add_flag(View.ui.label_scaning, LV_OBJ_FLAG_HIDDEN);
        scan_done = true;

        for (size_t i = 0; i < Model.GetScanCount(); i++) {
            lv_obj_t* label = lv_label_create(View.ui.wifi_ssid_list);
            lv_label_set_text_fmt(label, "%02d. %-27.27s [%-4d]", i + 1,
                                  Model.GetSSID(i), Model.GetRSSI(i));
        }
    }
}

void AppWiFi::onTimerUpdate(lv_timer_t* timer) {
    AppWiFi* instance = (AppWiFi*)timer->user_data;

    instance->Update();
}

void AppWiFi::onEvent(lv_event_t* event) {
    AppWiFi* instance = (AppWiFi*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        M5.Speaker.playWav(
            (const uint8_t*)ResourcePool::GetWav("select_0_5s"), ~0u, 1, 1);
        if (obj == instance->View.ui.imgbtn_home) {
            instance->_Manager->Replace("Pages/HomeMenu");
        } else if (obj == instance->View.ui.imgbtn_next) {
            Serial.print("AppWiFi -> AppCamera\r\n");
            instance->_Manager->Replace("Pages/AppCamera");
        } else if (obj == instance->View.ui.btn_top_center) {
            instance->Model.Scan();
            instance->scan_done = false;
            lv_obj_clear_flag(instance->View.ui.label_scaning,
                                LV_OBJ_FLAG_HIDDEN);
            lv_obj_clean(instance->View.ui.wifi_ssid_list);
        }
    }
}
