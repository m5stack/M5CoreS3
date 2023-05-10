#include <stdarg.h>
#include <stdio.h>
#include "HomeMenuView.h"

using namespace Page;

/*
    width: 60px
    height: 73px
*/

LV_IMG_DECLARE(menu_wifi);
LV_IMG_DECLARE(menu_cam);
LV_IMG_DECLARE(menu_mic);
LV_IMG_DECLARE(menu_power);
LV_IMG_DECLARE(menu_imu);
LV_IMG_DECLARE(menu_sd);
LV_IMG_DECLARE(menu_touch);
LV_IMG_DECLARE(menu_i2c);
LV_IMG_DECLARE(menu_sys);

static const lv_img_dsc_t* menu_img_pressed_list[] = {
    &menu_wifi,
    &menu_cam,
    &menu_mic,
    &menu_power,
    &menu_imu,
    &menu_sd,
    &menu_touch,
    &menu_i2c,
    &menu_sys,
};

void HomeMenuView::Create(lv_obj_t* root) {

    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("menu_bg"));

    for (size_t i = 0; i < 8; i++)
    {
        ui.imgbtn_list[i] = lv_imgbtn_create(root);
        // lv_obj_remove_style_all(ui.imgbtn_list[i]);
        lv_obj_set_size(ui.imgbtn_list[i], 60, 73);
        lv_obj_set_pos(ui.imgbtn_list[i], 10 + 80 * (i % 4), 75 + 80 * (i / 4));


        lv_imgbtn_set_src(ui.imgbtn_list[i], LV_IMGBTN_STATE_PRESSED, NULL, menu_img_pressed_list[i], NULL);
        lv_imgbtn_set_src(ui.imgbtn_list[i], LV_IMGBTN_STATE_RELEASED, NULL, menu_img_pressed_list[i], NULL);

        // lv_obj_set_style_border_color(ui.imgbtn_list[i], lv_color_hex(0xff00ff), 0);
        // lv_obj_set_style_border_side(ui.imgbtn_list[i], LV_BORDER_SIDE_FULL, 0);
        // lv_obj_set_style_border_width(ui.imgbtn_list[i], 1, 0);
        // lv_obj_set_style_radius(ui.imgbtn_list[i], 0, 0);
        // lv_obj_set_style_border_post(ui.imgbtn_list[i], true, 0);
    }

    ui.imgbtn_list[8] = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_list[8], 60, 73);
    lv_obj_set_pos(ui.imgbtn_list[8], 250, 10);

    lv_imgbtn_set_src(ui.imgbtn_list[8], LV_IMGBTN_STATE_PRESSED, NULL, menu_img_pressed_list[8], NULL);
    lv_imgbtn_set_src(ui.imgbtn_list[8], LV_IMGBTN_STATE_RELEASED, NULL, menu_img_pressed_list[8], NULL);

    // lv_obj_set_style_border_color(ui.imgbtn_list[8], lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.imgbtn_list[8], LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.imgbtn_list[8], 1, 0);
    // lv_obj_set_style_radius(ui.imgbtn_list[8], 0, 0);
    // lv_obj_set_style_border_post(ui.imgbtn_list[8], true, 0);

    ui.btn_factory = lv_obj_create(root);
    lv_obj_remove_style_all(ui.btn_factory);
    lv_obj_set_size(ui.btn_factory, 210, 40);
    lv_obj_set_pos(ui.btn_factory, 24, 17);

    // lv_obj_set_style_border_color(ui.btn_factory, lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.btn_factory, LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.btn_factory, 1, 0);
    // lv_obj_set_style_radius(ui.btn_factory, 0, 0);
    // lv_obj_set_style_border_post(ui.btn_factory, true, 0);
}

void HomeMenuView::Delete() {
}
