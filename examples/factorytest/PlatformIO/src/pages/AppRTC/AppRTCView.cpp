#include <stdarg.h>
#include <stdio.h>
#include "AppRTCView.h"

using namespace Page;

void AppRTCView::Create(lv_obj_t* root) {
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_rtc"));

    for (size_t i = 0; i < 6; i++)
    {
        ui.btn_list[i] = lv_btn_create(root);
        lv_obj_remove_style_all(ui.btn_list[i]);
        lv_obj_set_size(ui.btn_list[i], 102, 118);
        lv_obj_set_pos(ui.btn_list[i], 109 * (i % 3), 122 * (i / 3));

        // lv_obj_set_style_border_color(ui.btn_list[i], lv_color_hex(0xff00ff), 0);
        // lv_obj_set_style_border_side(ui.btn_list[i], LV_BORDER_SIDE_FULL, 0);
        // lv_obj_set_style_border_width(ui.btn_list[i], 1, 0);
        // lv_obj_set_style_radius(ui.btn_list[i], 0, 0);
        // lv_obj_set_style_border_post(ui.btn_list[i], true, 0);
    }
}

void AppRTCView::Delete() {
}