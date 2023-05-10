#include <stdarg.h>
#include <stdio.h>
#include "FactoryTestView.h"

using namespace Page;

void FactoryTestView::Create(lv_obj_t* root) {
    ui.cont = lv_obj_create(root);
    lv_obj_remove_style_all(ui.cont);
    lv_obj_set_size(ui.cont, 320, 240);
    lv_obj_set_pos(ui.cont, 0, 0);
    lv_obj_set_style_bg_color(ui.cont, lv_color_white(), 0);
    lv_obj_set_style_bg_opa(ui.cont, LV_OPA_COVER, 0);
    lv_obj_set_style_border_color(ui.cont, lv_color_make(255, 0, 0), 0);
    lv_obj_set_style_border_side(ui.cont, LV_BORDER_SIDE_FULL, 0);
    lv_obj_set_style_border_width(ui.cont, 1, 0);

    ui.label_test_title = lv_label_create(ui.cont);
    lv_obj_set_size(ui.label_test_title, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_font(ui.label_test_title, ResourcePool::GetFont("alibaba_pht_26"), 0);
    lv_label_set_text(ui.label_test_title, "进入产测流程?");
    lv_obj_align(ui.label_test_title, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style_text_align(ui.label_test_title, LV_TEXT_ALIGN_CENTER, 0);

    ui.label_wifi_ip = lv_label_create(ui.cont);
    lv_obj_set_size(ui.label_wifi_ip, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_text_font(ui.label_wifi_ip, ResourcePool::GetFont("alibaba_pht_26"), 0);
    lv_label_set_text(ui.label_wifi_ip, "");
    lv_obj_align_to(ui.label_wifi_ip, ui.label_test_title, LV_ALIGN_BOTTOM_MID, 0, 30);
    lv_obj_set_style_text_align(ui.label_wifi_ip, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui.label_wifi_ip, LV_OBJ_FLAG_HIDDEN);

    ui.btn_fail = lv_btn_create(ui.cont);
    lv_obj_set_size(ui.btn_fail, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(ui.btn_fail, lv_color_make(255, 0, 0), 0);
    ui.label_prev = lv_label_create(ui.btn_fail);
    lv_obj_set_style_text_font(ui.label_prev, ResourcePool::GetFont("alibaba_pht_26"), 0);
    lv_label_set_text(ui.label_prev, "退出");
    lv_obj_align(ui.btn_fail, LV_ALIGN_BOTTOM_MID, -80, -10);

    ui.btn_next = lv_btn_create(ui.cont);
    lv_obj_set_size(ui.btn_next, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_set_style_bg_color(ui.btn_next, lv_color_make(0, 255, 0), 0);
    ui.label_next = lv_label_create(ui.btn_next);
    lv_obj_set_style_text_font(ui.label_next, ResourcePool::GetFont("alibaba_pht_26"), 0);
    lv_label_set_text(ui.label_next, "开始");
    lv_obj_align(ui.btn_next, LV_ALIGN_BOTTOM_MID, 80, -10);

    ui.img_test_result = lv_img_create(ui.cont);
    lv_img_set_src(ui.img_test_result, ResourcePool::GetImage("pass"));
    lv_obj_align_to(ui.img_test_result, ui.label_test_title, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_obj_add_flag(ui.img_test_result, LV_OBJ_FLAG_HIDDEN);

#if MONKEY_TEST_ENABLE
    ui.btn_return = lv_btn_create(ui.cont);
    lv_obj_set_size(ui.btn_return, 100, 60);
    lv_obj_align(ui.btn_return, LV_ALIGN_TOP_MID, 0, 30);
    lv_obj_add_flag(ui.btn_return, LV_OBJ_FLAG_HIDDEN);
#endif
}

void FactoryTestView::Delete() {
}
