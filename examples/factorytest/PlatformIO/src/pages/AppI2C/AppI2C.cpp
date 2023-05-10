#include "AppI2C.h"

using namespace Page;

AppI2C::AppI2C() : timer(nullptr) {
}

AppI2C::~AppI2C() {
}

void AppI2C::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppI2C::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    AttachEvent(_root);
    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_top_center, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_scan_again, LV_EVENT_CLICKED);

    port_index = 0;
}

void AppI2C::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppI2C::onViewWillAppear() {
    LV_LOG_USER(__func__);

    scan_flag = true;
    timer     = lv_timer_create(onTimerUpdate, 1000, this);

    M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b100000, 100000L);
    M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b000010, 100000L);
    M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN
}

void AppI2C::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppI2C::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppI2C::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppI2C::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
}

void AppI2C::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppI2C::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppI2C::Update() {
    if (scan_flag) {
        bool addrs[120];

        switch (port_index) {
            case 0:
                M5.In_I2C.scanID(addrs);
                break;
            case 1:
                M5.Ex_I2C.begin(EXT_I2C_PORT, PORTA_PIN_1, PORTA_PIN_0);
                M5.Ex_I2C.scanID(addrs);
                M5.Ex_I2C.release();
                break;
            case 2:
                M5.Ex_I2C.begin(EXT_I2C_PORT, PORTB_PIN_1, PORTB_PIN_0);
                M5.Ex_I2C.scanID(addrs);
                M5.Ex_I2C.release();
                break;
            case 3:
                M5.Ex_I2C.begin(EXT_I2C_PORT, PORTC_PIN_1, PORTC_PIN_0);
                M5.Ex_I2C.scanID(addrs);
                M5.Ex_I2C.release();
                break;
            default:
                break;
        }

        bool has_addr = false;
        for (size_t i = 0; i < 120; i++) {
            if (addrs[i]) {
                lv_obj_t* label = lv_label_create(View.ui.cont_addr);
                lv_label_set_text_fmt(label, "%02X", i);
                lv_obj_set_pos(label, 33 + 18 * (i % 0x10),
                               29 + 18 * (i / 0x10));
                has_addr = true;
            }
        }

        if (has_addr) {
            lv_obj_add_flag(View.ui.label_notice, LV_OBJ_FLAG_HIDDEN);
        } else {
            lv_label_set_text(View.ui.label_notice,
                              "No device found, click to "
                              "scan again");
            lv_obj_clear_flag(View.ui.label_notice, LV_OBJ_FLAG_HIDDEN);
        }
        scan_flag = false;
    }
}

void AppI2C::onTimerUpdate(lv_timer_t* timer) {
    AppI2C* instance = (AppI2C*)timer->user_data;

    instance->Update();
}

void AppI2C::onEvent(lv_event_t* event) {
    AppI2C* instance = (AppI2C*)lv_event_get_user_data(event);
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
                Serial.print("AppI2C -> AppWiFi\r\n");
                instance->_Manager->Replace("Pages/AppWiFi");
            } else if (obj == instance->View.ui.btn_top_center) {
                instance->port_index += 1;
                if (instance->port_index >= 4) {
                    instance->port_index = 0;
                }
                instance->View.ChangeBgImg(instance->port_index);
                lv_label_set_text(instance->View.ui.label_notice,
                                  "Scan I2C Devices...");
                lv_obj_clear_flag(instance->View.ui.label_notice,
                                  LV_OBJ_FLAG_HIDDEN);
                lv_obj_clean(instance->View.ui.cont_addr);
                instance->scan_flag = true;
            } else if (obj == instance->View.ui.btn_scan_again) {
                instance->scan_flag = true;
                lv_label_set_text(instance->View.ui.label_notice,
                                  "Scan I2C Devices...");
                lv_obj_clear_flag(instance->View.ui.label_notice,
                                  LV_OBJ_FLAG_HIDDEN);
                lv_obj_clean(instance->View.ui.cont_addr);
            }
        }
    }
}
