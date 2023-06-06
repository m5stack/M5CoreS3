#include "AppPower.h"

using namespace Page;

AppPower::AppPower() : timer(nullptr) {
}

AppPower::~AppPower() {
}

void AppPower::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppPower::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    AttachEvent(_root);
    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_top_center, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_usb, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_bus, LV_EVENT_CLICKED);

    Model.AxpAdcEnable();
    Model.AxpCHGLedEnable();

    Model.GetPowerMode();
    View.ChangeBgImg(Model.power_mode);
    View.ChangeUsbImg(Model.mode_bit.usb);
    View.ChangeBusImg(Model.mode_bit.bus);
}

void AppPower::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppPower::onViewWillAppear() {
    LV_LOG_USER(__func__);
    timer = lv_timer_create(onTimerUpdate, 1000, this);
}

void AppPower::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppPower::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppPower::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);

    Model.AxpCHGLedDisable();
}

void AppPower::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
}

void AppPower::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppPower::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppPower::Update() {
    Model.AxpAdcSampling();
    View.ChangeBatImg(Model.AxpBatIsCharging());

    char buf[32];
    if (Model.AxpBatIsCharging() == 0) {
        sprintf(buf, "%01.01fV", 0.0f);
    } else {
        sprintf(buf, "%01.01fV", Model.vbat / 1000.0f);
    }
    lv_label_set_text(View.ui.label_vbat, buf);

    sprintf(buf, "%01.01fV", Model.vbus / 1000.0f);
    lv_label_set_text(View.ui.label_vbus, buf);

    sprintf(buf, "%01.01f", Model.tdie);
    lv_label_set_text(View.ui.label_tdie, buf);

    float vts = ((Model.ts - 250.0f) *2) / 1000.0f;
    if (vts < 1.0f) {
        vts = 0.0f;
    }
    sprintf(buf, "%01.01fV", vts);
    lv_label_set_text(View.ui.label_vmbus, buf);

    // Serial.printf("vbus:%f, vbat:%f, tdie:%f, ts:%f\r\n", Model.vbus, Model.vbat,
    //               Model.tdie, Model.ts);
}

void AppPower::onTimerUpdate(lv_timer_t* timer) {
    AppPower* instance = (AppPower*)timer->user_data;

    instance->Update();
}

void AppPower::onEvent(lv_event_t* event) {
    AppPower* instance = (AppPower*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->_root) {
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LEAVE) {
            // instance->_Manager->Pop();
        }
    } else {
        if (code == LV_EVENT_CLICKED) {
            M5.Speaker.playWav(
                (const uint8_t*)ResourcePool::GetWav("select_0_5s"), ~0u, 1, 1);
            if (obj == instance->View.ui.imgbtn_home) {
                instance->_Manager->Replace("Pages/HomeMenu");
            } else if (obj == instance->View.ui.imgbtn_next) {
                Serial.print("AppPower -> AppIMU\r\n");
                instance->_Manager->Replace("Pages/AppIMU");
            } else if (obj == instance->View.ui.imgbtn_usb) {
                instance->Model.mode_bit.usb = !instance->Model.mode_bit.usb;
                instance->Model.SetPowerMode(instance->Model.power_mode);
                instance->View.ChangeUsbImg(instance->Model.mode_bit.usb);
                instance->View.ChangeBgImg(instance->Model.power_mode);
            } else if (obj == instance->View.ui.imgbtn_bus) {
                instance->Model.mode_bit.bus = !instance->Model.mode_bit.bus;
                instance->Model.SetPowerMode(instance->Model.power_mode);
                instance->View.ChangeBusImg(instance->Model.mode_bit.bus);
                instance->View.ChangeBgImg(instance->Model.power_mode);
            }
        }
    }
}
