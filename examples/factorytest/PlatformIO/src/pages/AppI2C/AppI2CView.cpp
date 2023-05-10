#include <stdarg.h>
#include <stdio.h>
#include "AppI2CView.h"

using namespace Page;

void AppI2CView::Create(lv_obj_t* root) {
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_i2c_internal"));

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

    ui.cont_addr = lv_obj_create(root);
    lv_obj_remove_style_all(ui.cont_addr);
    lv_obj_set_size(ui.cont_addr, 320, 172);
    lv_obj_clear_flag(ui.cont_addr, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(ui.cont_addr, 0, 68);

    // lv_obj_set_style_border_color(ui.cont_addr, lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.cont_addr, LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.cont_addr, 1, 0);
    // lv_obj_set_style_radius(ui.cont_addr, 0, 0);
    // lv_obj_set_style_border_post(ui.cont_addr, true, 0);

    ui.btn_scan_again = lv_btn_create(root);
    lv_obj_remove_style_all(ui.btn_scan_again);
    lv_obj_set_size(ui.btn_scan_again, 320, 172);
    lv_obj_clear_flag(ui.btn_scan_again, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_pos(ui.btn_scan_again, 0, 68);

    ui.label_notice = lv_label_create(root);
    lv_label_set_text(ui.label_notice, "Scan I2C Devices...");
    lv_obj_align(ui.label_notice, LV_ALIGN_CENTER, 15, 40);
}

void AppI2CView::Delete() {
}

void AppI2CView::ChangeBgImg(uint8_t index) {
    switch (index) {
        case 0:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_i2c_internal"));
            break;
        case 1:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_i2c_pa"));
            break;
        case 2:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_i2c_pb"));
            break;
        case 3:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_i2c_pc"));
            break;
        default:
            break;
    }
}