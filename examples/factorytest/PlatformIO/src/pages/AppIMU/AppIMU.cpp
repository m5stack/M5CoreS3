#include "AppIMU.h"

using namespace Page;

AppIMU::AppIMU() : timer(nullptr) {
    Model.Init();
    Model.filter.begin(20);  // 20hz
}

AppIMU::~AppIMU() {
}

void AppIMU::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppIMU::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    AttachEvent(_root);
    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_top_center, LV_EVENT_CLICKED);

    if (!Model.ReadCalibration()) {
        lv_obj_clear_flag(View.ui.label_notice, LV_OBJ_FLAG_HIDDEN);
    }
}

void AppIMU::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppIMU::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 30, this);
}

void AppIMU::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppIMU::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppIMU::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppIMU::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
}

void AppIMU::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppIMU::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppIMU::Update() {
    Model.Update();

    float dir = Model.CalcuDir();

    if (calibration_flag) {
        Model.MagCalibration();
        calibration_flag = false;
        lv_label_set_text(View.ui.label_notice,
                          "Calibration is complete, if you need to calibrate "
                          "again, please click the top icon again.");
        Model.SaveCalibration();
    }

    Model.filter.updateIMU(Model.gyro_data.x, Model.gyro_data.y,
                           Model.gyro_data.z, Model.accel_data.x,
                           Model.accel_data.y, Model.accel_data.z);

    float roll  = Model.filter.getRoll();
    float pitch = Model.filter.getPitch();
    float yaw   = Model.filter.getYaw();

    if (abs(roll) > 90) {
        if (roll < -90) {
            roll = -90;
        } else {
            roll = 90;
        }
    }
    if (abs(pitch) > 90) {
        if (pitch < -90) {
            pitch = -90;
        } else {
            pitch = 90;
        }
    }

    uint16_t x = (uint16_t)map(pitch, -90.0f, 90.0f, -48, 48);
    uint16_t y = (uint16_t)map(roll, -90.0f, 90.0f, -48, 48);

    lv_obj_align_to(View.ui.img_ball, View.ui.img_compass, LV_ALIGN_CENTER, x,
                    y);

    float angle = ((360 - dir) + 90) * 10;
    lv_img_set_angle(View.ui.img_compass, angle);
}

void AppIMU::onTimerUpdate(lv_timer_t* timer) {
    AppIMU* instance = (AppIMU*)timer->user_data;

    instance->Update();
}

void AppIMU::onEvent(lv_event_t* event) {
    AppIMU* instance = (AppIMU*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (obj == instance->_root) {
        if (code == LV_EVENT_SHORT_CLICKED || code == LV_EVENT_LEAVE) {
            // instance->_Manager->Pop();
        }
    } else {
        if (code == LV_EVENT_CLICKED) {
            if (obj == instance->View.ui.btn_top_center) {
                instance->calibration_flag = true;
                return;
            }
            M5.Speaker.playWav(
                (const uint8_t*)ResourcePool::GetWav("select_0_5s"), ~0u, 1, 1);
            if (obj == instance->View.ui.imgbtn_home) {
                instance->_Manager->Replace("Pages/HomeMenu");
            } else if (obj == instance->View.ui.imgbtn_next) {
                Serial.print("AppIMU -> AppSD\r\n");
                instance->_Manager->Replace("Pages/AppSD");
            }
        }
    }
}
