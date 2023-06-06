#include "AppMic.h"

using namespace Page;

AppMic::AppMic() : timer(nullptr) {
    canvas[0].setPsram(true);
    canvas[0].setColorDepth(1);
    canvas[0].createSprite(128, 120);
    canvas[0].clear(0xeeeeef);

    canvas[1].setPsram(true);
    canvas[1].setColorDepth(1);
    canvas[1].createSprite(128, 120);
    canvas[1].clear(0xeeeeef);
}

AppMic::~AppMic() {
    canvas[0].deleteSprite();
    canvas[1].deleteSprite();
}

void AppMic::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void AppMic::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    AttachEvent(_root);
    AttachEvent(View.ui.imgbtn_home, LV_EVENT_CLICKED);
    AttachEvent(View.ui.imgbtn_next, LV_EVENT_CLICKED);

    Model.MicBegin();
}

void AppMic::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void AppMic::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 30, this);
}

void AppMic::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void AppMic::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void AppMic::onViewDidDisappear() {
    LV_LOG_USER(__func__);

    lv_timer_del(timer);
}

void AppMic::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
    Model.MicEnd();
}

void AppMic::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void AppMic::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void AppMic::Update() {
    if (Model.IsMicEnable()) {
        Model.ReadMicData();
        for (size_t lr = 0; lr < 2; ++lr) {
            int x = 0;
            auto rec_buf =
                Model.buf_index == 0 ? Model.mic_buf[1] : Model.mic_buf[0];
            int py           = 64 + (rec_buf[lr] >> 8);
            canvas[lr].clear(TFT_WHITE);
            for (size_t i = 2 + lr; i < MIC_BUF_SIZE; i += 2) {
                int y      = 64 + (rec_buf[i] >> 8);
                canvas[lr].drawFastVLine(x, y, py - y + 1, TFT_BLACK);
                py              = y;
                ++x;
            }
            canvas[lr].pushSprite(&M5.Display, lr * 160 + 16, 78);
        }
        Model.buf_index = (Model.buf_index + 1) % 2;
    }
}

void AppMic::onTimerUpdate(lv_timer_t* timer) {
    AppMic* instance = (AppMic*)timer->user_data;

    instance->Update();
}

extern const unsigned char select_0_5s[88738];

void AppMic::onEvent(lv_event_t* event) {
    AppMic* instance = (AppMic*)lv_event_get_user_data(event);
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
                instance->_Manager->Replace("Pages/HomeMenu");
            } else if (obj == instance->View.ui.imgbtn_next) {
                Serial.print("AppMic -> AppPower\r\n");
                instance->_Manager->Replace("Pages/AppPower");
            } else if (obj == instance->View.ui.btn_top_center) {
            }
        }
    }
}
