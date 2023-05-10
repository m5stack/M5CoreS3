#include <stdarg.h>
#include <stdio.h>
#include "AppWiFiView.h"

using namespace Page;

void AppWiFiView::Create(lv_obj_t* root) {
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_wifi"));

    ui.imgbtn_home = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_home, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_imgbtn_set_src(ui.imgbtn_home, LV_IMGBTN_STATE_RELEASED, NULL, ResourcePool::GetImage("home_r"), NULL);
    lv_imgbtn_set_src(ui.imgbtn_home, LV_IMGBTN_STATE_PRESSED, NULL, ResourcePool::GetImage("home_p"), NULL);
    lv_obj_align(ui.imgbtn_home, LV_ALIGN_TOP_LEFT, 0, 0);

    ui.imgbtn_next = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_next, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_imgbtn_set_src(ui.imgbtn_next, LV_IMGBTN_STATE_RELEASED, NULL, ResourcePool::GetImage("next_r"), NULL);
    lv_imgbtn_set_src(ui.imgbtn_next, LV_IMGBTN_STATE_PRESSED, NULL, ResourcePool::GetImage("next_p"), NULL);
    lv_obj_align(ui.imgbtn_next, LV_ALIGN_TOP_RIGHT, 5, 0);

    ui.btn_top_center = lv_btn_create(root);
    lv_obj_remove_style_all(ui.btn_top_center);
    lv_obj_set_size(ui.btn_top_center, 170, 68);
    lv_obj_align(ui.btn_top_center, LV_ALIGN_TOP_MID, 0, 0);

    // lv_obj_set_style_border_color(ui.btn_top_center, lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.btn_top_center, LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.btn_top_center, 1, 0);
    // lv_obj_set_style_radius(ui.btn_top_center, 0, 0);
    // lv_obj_set_style_border_post(ui.btn_top_center, true, 0);

    ui.cont_wifi = lv_obj_create(root);
    lv_obj_remove_style_all(ui.cont_wifi);
    lv_obj_set_size(ui.cont_wifi, 320, 172);
    lv_obj_clear_flag(ui.cont_wifi, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(ui.cont_wifi, 0, 68);

    // lv_obj_set_style_border_color(ui.cont_wifi, lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.cont_wifi, LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.cont_wifi, 1, 0);
    // lv_obj_set_style_radius(ui.cont_wifi, 0, 0);
    // lv_obj_set_style_border_post(ui.cont_wifi, true, 0);

    ui.wifi_ssid_list = lv_list_create(ui.cont_wifi);
    lv_obj_set_style_radius(ui.wifi_ssid_list, 0, 0);
    lv_obj_set_size(ui.wifi_ssid_list, 300, 160);
    lv_obj_set_pos(ui.wifi_ssid_list, 10, 6);

    ui.label_scaning = lv_label_create(root);
    lv_label_set_text(ui.label_scaning, "Scanning...");
    lv_obj_align(ui.label_scaning, LV_ALIGN_CENTER, 0, 30);
    lv_obj_add_flag(ui.label_scaning, LV_OBJ_FLAG_HIDDEN);
}

void AppWiFiView::Delete() {
}
