#include "FactoryTest.h"
#include <WiFi.h>

using namespace Page;

extern bool bmm150_init_flag;

static char label_notcie[11][64] = {"屏幕测试 红",                     // 0
                                    "屏幕测试 绿",                     // 1
                                    "屏幕测试 蓝",                     // 2
                                    "屏幕测试 黑",                     // 3
                                    "I2C设备测试",                     // 4
                                    "触摸测试",                        // 5
                                    "PORT A/B/C测试\rLED灯是否闪烁?",  // 6
                                    "摄像头测试",                      // 7
                                    "麦克风测试",                      // 8
                                    "WiFi连接测试",                    // 9
                                    "测试结果"};                       // 10

static lv_color_t text_color[11] = {
    lv_color_black(), lv_color_black(), lv_color_black(), lv_color_white(),
    lv_color_black(), lv_color_black(), lv_color_black(), lv_color_black(),
    lv_color_black(), lv_color_black(), lv_color_black()};

static lv_color_t bg_color[11] = {
    lv_color_make(255, 0, 0),     lv_color_make(0, 255, 0),
    lv_color_make(0, 0, 255),     lv_color_make(0, 0, 0),
    lv_color_make(255, 255, 255), lv_color_make(255, 255, 255),
    lv_color_make(255, 255, 255), lv_color_make(255, 255, 255),
    lv_color_make(255, 255, 255), lv_color_make(255, 255, 255),
    lv_color_make(255, 255, 255)};

static lv_color_t border_color[11] = {
    lv_color_make(0, 255, 0), lv_color_make(255, 0, 0),
    lv_color_make(255, 0, 0), lv_color_make(255, 255, 255),
    lv_color_make(255, 0, 0), lv_color_make(255, 0, 0),
    lv_color_make(255, 0, 0), lv_color_make(255, 0, 0),
    lv_color_make(255, 0, 0), lv_color_make(255, 0, 0),
    lv_color_make(255, 0, 0)};

FactoryTest::FactoryTest() : timer(nullptr) {
}

FactoryTest::~FactoryTest() {
}

void FactoryTest::onCustomAttrConfig() {
    LV_LOG_USER(__func__);
}

void FactoryTest::onViewLoad() {
    LV_LOG_USER(__func__);
    View.Create(_root);

    Model.CameraInit();
    Model.PortIoInit();

    factory_test_step = -1;
    ui_update_flag    = false;
    test_fail_flag    = 0;

    AttachEvent(_root);
    AttachEvent(View.ui.btn_next, LV_EVENT_CLICKED);
    AttachEvent(View.ui.btn_fail, LV_EVENT_CLICKED);

#if MONKEY_TEST_ENABLE
    AttachEvent(View.ui.btn_return, LV_EVENT_CLICKED);
#endif
    M5.Speaker.end();
    M5.Mic.begin();
}

void FactoryTest::onViewDidLoad() {
    LV_LOG_USER(__func__);
}

void FactoryTest::onViewWillAppear() {
    LV_LOG_USER(__func__);

    timer = lv_timer_create(onTimerUpdate, 30, this);

    M5.In_I2C.bitOff(AW9523_ADDR, 0x02, 0b100000, 100000L);
    M5.In_I2C.bitOn(AW9523_ADDR, 0x02, 0b000010, 100000L);
    M5.In_I2C.bitOn(AW9523_ADDR, 0x03, 0b10000000, 100000L);  // BOOST_EN

    WiFi.begin("M5-FA-Test-01", "M5FactoryTest??");
    // WiFi.begin("M5-R&D", "echo\"password\">/dev/null?");
}

void FactoryTest::onViewDidAppear() {
    LV_LOG_USER(__func__);
}

void FactoryTest::onViewWillDisappear() {
    LV_LOG_USER(__func__);
}

void FactoryTest::onViewDidDisappear() {
    LV_LOG_USER(__func__);
    lv_timer_del(timer);
}

void FactoryTest::onViewUnload() {
    LV_LOG_USER(__func__);

    View.Delete();
    Model.ReleaseFramebuffer();
    Model.CameraDeinit();

    M5.Mic.end();
    M5.Speaker.begin();
}

void FactoryTest::onViewDidUnload() {
    LV_LOG_USER(__func__);
}

void FactoryTest::AttachEvent(lv_obj_t* obj, lv_event_code_t code) {
    lv_obj_set_user_data(obj, this);
    lv_obj_add_event_cb(obj, onEvent, code, this);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_GESTURE_BUBBLE);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_SCROLLABLE);
}

void FactoryTest::Update() {
    if (ui_update_flag) {
        ui_update_flag = false;

        lv_label_set_text(View.ui.label_test_title,
                          label_notcie[factory_test_step]);
        lv_obj_set_style_text_color(View.ui.label_test_title,
                                    text_color[factory_test_step], 0);
        lv_obj_set_style_bg_color(View.ui.cont, bg_color[factory_test_step], 0);
        lv_obj_set_style_border_color(View.ui.cont,
                                      border_color[factory_test_step], 0);
        lv_label_set_text(View.ui.label_prev, "失败");
        lv_label_set_text(View.ui.label_next, "通过");

        if (factory_test_step == 4) {
            // FIXME: 0x36 扫描不到?
            // 内部设备测试, 内部共有10个I2C设备, 9 + 1
            bool addrs[120];
            M5.In_I2C.scanID(addrs);
            uint8_t count = 0;
            for (size_t i = 0; i < 120; i++) {
                if (addrs[i]) {
                    count++;
                }
            }
            if (bmm150_init_flag && count >= 8) {
                lv_label_set_text(View.ui.label_test_title, "I2C设备测试通过");

            } else {
                lv_label_set_text(View.ui.label_test_title,
                                  "I2C设备测试不通过");
                test_fail_flag |= (1 << factory_test_step);
            }
            lv_label_set_text(View.ui.label_next, "下一步");
        } else {
            lv_label_set_text(View.ui.label_next, "通过");
        }

        if (factory_test_step == 8) {
            lv_obj_align(View.ui.label_test_title, LV_ALIGN_CENTER, 0, 30);
        } else {
            lv_obj_align(View.ui.label_test_title, LV_ALIGN_CENTER, 0, 0);
        }

        if (factory_test_step == 9) {
            lv_obj_clear_flag(View.ui.label_wifi_ip, LV_OBJ_FLAG_HIDDEN);
            lv_label_set_text(View.ui.label_next, "下一步");
        } else {
            lv_obj_add_flag(View.ui.label_wifi_ip, LV_OBJ_FLAG_HIDDEN);
        }

#if MONKEY_TEST_ENABLE
        if (factory_test_step == 10) {
            lv_obj_clear_flag(View.ui.btn_return, LV_OBJ_FLAG_HIDDEN);
        }
#endif
    }

    switch (factory_test_step) {
        case 5: {  // 触摸测试
            static std::uint32_t color = 0;
            auto count                 = M5.Touch.getCount();
            if (!count) {
                t_prev.x = 0;
                t_prev.y = 0;
                return;
            }
            auto t = M5.Touch.getTouchPointRaw(0);
            M5.Display.fillRect(t.x - 1, t.y - 1, 2, 2, color);
            if (t_prev.x != 0 && t_prev.y != 0) {
                M5.Display.drawLine(t_prev.x, t_prev.y, t.x, t.y, color);
            }
            t_prev = t;
            if (color % 65536 == 0) {
                M5.Display.clear(TFT_WHITE);
                lv_label_set_text(View.ui.label_test_title, "触摸测试");
                lv_label_set_text(View.ui.label_prev, "失败");
                lv_label_set_text(View.ui.label_next, "通过");
            }
            color += 32;
        } break;
        case 6:  // 端口IO测试
            Model.PortIoBlink();
            break;
        case 7:  // 摄像头测试
            if (Model.GetFramebuffer()) {
                M5.Display.startWrite();
                M5.Display.setAddrWindow(0, 0, 320, 240);
                M5.Display.writePixels((uint16_t*)Model.fb->buf,
                                       int(Model.fb->len / 2));
                M5.Display.endWrite();
            }
            Model.ReleaseFramebuffer();
            break;
        case 8:  // 麦克风测试
        {
            if (M5.Mic.isEnabled()) {
                int16_t mic_buf[MIC_BUF_SIZE];
                M5.Mic.record(mic_buf, MIC_BUF_SIZE, 16000);
                for (size_t lr = 0; lr < 2; ++lr) {
                    int x = lr * 160 + 16;
                    M5.Display.fillRect(0, 0, 320, 128, TFT_WHITE);
                    int py = 64 + (mic_buf[lr] >> 8);
                    for (size_t i = 2 + lr; i < MIC_BUF_SIZE; i += 2) {
                        int y = 64 + (mic_buf[i] >> 8);
                        M5.Display.drawFastVLine(x, y, py - y + 1, TFT_BLACK);
                        py = y;
                        ++x;
                    }
                }
            }
        } break;
        case 9:
            if (WiFi.status() == WL_CONNECTED) {
                lv_label_set_text(View.ui.label_test_title,
                                  "WiFi连接成功,测试通过");
                lv_label_set_text_fmt(View.ui.label_wifi_ip, "%s",
                                      WiFi.localIP().toString().c_str());
            } else if (WiFi.status() == WL_CONNECT_FAILED ||
                       WiFi.status() == WL_NO_SSID_AVAIL ||
                       WiFi.status() == WL_DISCONNECTED) {
                lv_label_set_text(View.ui.label_test_title, "WiFi测试不通过");
                lv_label_set_text(View.ui.label_wifi_ip, "连接失败");
                test_fail_flag |= (1 << factory_test_step);
            } else {
                lv_label_set_text(View.ui.label_wifi_ip, "WiFi连接中...");
                // Serial.println(WiFi.status());
            }
            lv_obj_align_to(View.ui.label_wifi_ip, View.ui.label_test_title,
                            LV_ALIGN_BOTTOM_MID, 0, 30);
            break;
        case 10:  // 测试结果
            lv_obj_align(View.ui.label_test_title, LV_ALIGN_CENTER, 0, 0);
            if (test_fail_flag) {
                lv_label_set_text(View.ui.label_test_title, "测试不通过");
                lv_obj_set_style_text_color(View.ui.label_test_title,
                                            lv_color_make(255, 0, 0), 0);
                lv_img_set_src(View.ui.img_test_result,
                               ResourcePool::GetImage("failed"));
            } else {
                lv_label_set_text(View.ui.label_test_title, "测试通过");
                lv_obj_set_style_text_color(View.ui.label_test_title,
                                            lv_color_make(0, 255, 0), 0);
            }
            lv_obj_clear_flag(View.ui.img_test_result, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(View.ui.btn_next, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(View.ui.btn_fail, LV_OBJ_FLAG_HIDDEN);
            break;
        default:
            break;
    }

    if (M5.BtnPWR.wasClicked()) {
        _Manager->Replace("Pages/HomeMenu");
    }
}

void FactoryTest::onTimerUpdate(lv_timer_t* timer) {
    FactoryTest* instance = (FactoryTest*)timer->user_data;

    instance->Update();
}

void FactoryTest::onEvent(lv_event_t* event) {
    FactoryTest* instance = (FactoryTest*)lv_event_get_user_data(event);
    LV_ASSERT_NULL(instance);

    lv_obj_t* obj        = lv_event_get_current_target(event);
    lv_event_code_t code = lv_event_get_code(event);

    if (code == LV_EVENT_CLICKED) {
        if (obj == instance->View.ui.btn_fail) {
            if (instance->factory_test_step == -1) {
                instance->_Manager->Replace("Pages/HomeMenu");
                return;
            }
            instance->factory_test_step++;
            if (instance->factory_test_step > 10) {
                instance->factory_test_step = 0;
            }
            instance->ui_update_flag = true;
            instance->test_fail_flag |= (1 << instance->factory_test_step);
        } else if (obj == instance->View.ui.btn_next) {
            instance->factory_test_step++;
            if (instance->factory_test_step > 10) {
                instance->factory_test_step = 0;
            }
            instance->ui_update_flag = true;
        }
#if MONKEY_TEST_ENABLE
        else if (obj == instance->View.ui.btn_return) {
            instance->_Manager->Replace("Pages/HomeMenu");
        }
#endif
    }
}
