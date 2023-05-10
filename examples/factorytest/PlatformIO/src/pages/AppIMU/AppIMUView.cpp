#include <stdarg.h>
#include <stdio.h>
#include "AppIMUView.h"

using namespace Page;

void AppIMUView::Create(lv_obj_t* root) {
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_imu_graphic"));

    ui.imgbtn_home = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_home, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_imgbtn_set_src(ui.imgbtn_home, LV_IMGBTN_STATE_RELEASED, NULL,
                      ResourcePool::GetImage("home_r"), NULL);
    lv_imgbtn_set_src(ui.imgbtn_home, LV_IMGBTN_STATE_PRESSED, NULL,
                      ResourcePool::GetImage("home_p"), NULL);
    lv_obj_align(ui.imgbtn_home, LV_ALIGN_TOP_LEFT, 0, 0);

    ui.imgbtn_next = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_next, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_imgbtn_set_src(ui.imgbtn_next, LV_IMGBTN_STATE_RELEASED, NULL,
                      ResourcePool::GetImage("next_r"), NULL);
    lv_imgbtn_set_src(ui.imgbtn_next, LV_IMGBTN_STATE_PRESSED, NULL,
                      ResourcePool::GetImage("next_p"), NULL);
    lv_obj_align(ui.imgbtn_next, LV_ALIGN_TOP_RIGHT, 5, 0);

    ui.btn_top_center = lv_btn_create(root);
    lv_obj_remove_style_all(ui.btn_top_center);
    lv_obj_set_size(ui.btn_top_center, 170, 68);
    lv_obj_align(ui.btn_top_center, LV_ALIGN_TOP_MID, 0, 0);

    // lv_obj_set_style_border_color(ui.btn_top_center, lv_color_hex(0xff00ff),
    // 0); lv_obj_set_style_border_side(ui.btn_top_center, LV_BORDER_SIDE_FULL,
    // 0); lv_obj_set_style_border_width(ui.btn_top_center, 1, 0);
    // lv_obj_set_style_radius(ui.btn_top_center, 0, 0);
    // lv_obj_set_style_border_post(ui.btn_top_center, true, 0);

    ui.img_compass = lv_img_create(root);
    lv_img_set_src(ui.img_compass, ResourcePool::GetImage("compass_face"));
    lv_obj_align(ui.img_compass, LV_ALIGN_BOTTOM_MID, 0, -25);

    ui.img_cross = lv_img_create(root);
    lv_img_set_src(ui.img_cross, ResourcePool::GetImage("cross"));
    lv_obj_align_to(ui.img_cross, ui.img_compass, LV_ALIGN_CENTER, 0, -24);

    ui.img_ball = lv_img_create(root);
    lv_img_set_src(ui.img_ball, ResourcePool::GetImage("ball"));
    lv_obj_align_to(ui.img_ball, ui.img_compass, LV_ALIGN_CENTER, 0, 0);

    ui.label_notice = lv_label_create(root);
    lv_obj_set_width(ui.label_notice, 310);
    lv_label_set_text(
        ui.label_notice,
        "Sorry, the calibration data of the compass is not found. Please click "
        "the icon in the middle of the top to calibrate. The calibration takes "
        "a total of 10s. It starts after the beep sounds and ends after the "
        "beep sounds again. Please use the standard figure-8 method for "
        "calibration.");
    lv_obj_align(ui.label_notice, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_label_set_long_mode(ui.label_notice, LV_LABEL_LONG_SCROLL_CIRCULAR);
    lv_obj_add_flag(ui.label_notice, LV_OBJ_FLAG_HIDDEN);
}

void AppIMUView::Delete() {
}