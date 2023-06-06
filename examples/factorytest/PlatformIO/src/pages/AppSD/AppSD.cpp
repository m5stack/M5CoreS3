#include "AppSD.h"

using namespace Page;

AppSD::AppSD() : timer(nullptr) {
}

AppSD::~AppSD() {
}

void AppSD::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppSD::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    if (Model.IsSDCardExist()) {
        lv_label_set_text(View.ui.label_notice, "Initialize SD Card...");
        Model.SDInit();
    }

    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_top_center, LV_EVENT_CLICKED);
}

void AppSD::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppSD::onViewWillAppear() {
    LV_LOG_USER(__func__);
    timer = lv_timer_create(onTimerUpdate, 100, this);
}

void AppSD::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppSD::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppSD::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void AppSD::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
    scan_flag = true;
    Model.SDDeinit();
}

void AppSD::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppSD::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppSD::ListSDCard(fs::FS& fs, const char* dirname, uint8_t levels) {
    File root = fs.open(dirname);
    if (!root) {
        lv_obj_clean(View.ui.file_list);
        lv_label_set_text(View.ui.label_notice,
                          "Failed to open root directory");
        lv_obj_clear_flag(View.ui.label_notice, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    if (!root.isDirectory()) {
        return;
    }

    File file = root.openNextFile();
    while (file) {
        if (file.isDirectory()) {
            lv_obj_t* label = lv_label_create(View.ui.file_list);
            lv_label_set_text_fmt(label, "DIR: %-31.31s", file.name());
            if (levels) {
                ListSDCard(fs, file.path(), levels - 1);
            }
        } else {
            lv_obj_t* label = lv_label_create(View.ui.file_list);
            lv_label_set_text_fmt(label, "  F: %-24.24s %05dKB", file.name(),
                                  file.size());
        }
        file = root.openNextFile();
    }
}

void AppSD::Update() {
    if (Model.IsSDCardExist()) {
        if (!Model.GetInitFlag()) {
            lv_obj_clean(View.ui.file_list);
            lv_label_set_text(View.ui.label_notice,
                              "Reinitialize the SD Card...");
            lv_obj_clear_flag(View.ui.label_notice, LV_OBJ_FLAG_HIDDEN);
            if (!Model.SDInit()) {
                lv_label_set_text(View.ui.label_notice,
                                  "SD Card initialization failed!\r\nPlease "
                                  "try reinsert SD card...");
            }
        } else {
            lv_label_set_text(View.ui.label_notice, "SD Card is ready");
            lv_obj_add_flag(View.ui.label_notice, LV_OBJ_FLAG_HIDDEN);
            if (scan_flag) {
                lv_obj_clean(View.ui.file_list);
                ListSDCard(SD, "/", 2);
                scan_flag = false;
            }
        }
    } else {
        Model.ClearInitFlag();
        scan_flag = true;
        lv_obj_clean(View.ui.file_list);
        lv_label_set_text(View.ui.label_notice, "Please insert SD card...");
        lv_obj_clear_flag(View.ui.label_notice, LV_OBJ_FLAG_HIDDEN);
    }
}

void AppSD::onTimerUpdate(lv_timer_t* timer) {
    AppSD* instance = (AppSD*)timer->user_data;

    instance->Update();
}

void AppSD::onEvent(lv_event_t* event) {
    AppSD* instance = (AppSD*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        M5.Speaker.playWav((const uint8_t*)ResourcePool::GetWav("select_0_5s"),
                           ~0u, 1, 1);
        if (obj == instance->View.ui.imgbtn_home) {
            instance->_Manager->Replace("Pages/HomeMenu");
        } else if (obj == instance->View.ui.imgbtn_next) {
            Serial.print("AppSD -> AppTouch\r\n");
            instance->_Manager->Replace("Pages/AppTouch");
        } else if (obj == instance->View.ui.btn_top_center) {
            instance->scan_flag = true;
        }
    }
}
