#include <stdarg.h>
#include <stdio.h>
#include "AppCameraView.h"

using namespace Page;

void AppCameraView::Create(lv_obj_t* root) {
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_camera"));

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

    // static lv_style_t style;
    // lv_style_init(&style);
    // lv_style_set_border_color(&style, lv_color_hex(0xff931e));
    // lv_style_set_border_side(&style, LV_BORDER_SIDE_FULL);
    // lv_style_set_border_width(&style, 2);
    // lv_style_set_border_post(&style, true);

    // ui.img_camera = lv_img_create(root);
    // lv_obj_set_pos(ui.img_camera, 25, 90);
    // lv_obj_add_style(ui.img_camera, &style, 0);

    for (size_t i = 0; i < 8; i++)
    {
        ui.obj_ltr553_als_list[i] = lv_obj_create(root);
        lv_obj_remove_style_all(ui.obj_ltr553_als_list[i]);
        lv_obj_set_size(ui.obj_ltr553_als_list[i], 20, 10);
        lv_obj_set_pos(ui.obj_ltr553_als_list[i], 226, 197 - i * 15);

        lv_obj_set_style_bg_opa(ui.obj_ltr553_als_list[i], LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(ui.obj_ltr553_als_list[i], lv_color_hex(0x008fd7), 0);
        lv_obj_add_flag(ui.obj_ltr553_als_list[i], LV_OBJ_FLAG_HIDDEN);
    }
    
    for (size_t i = 0; i < 8; i++)
    {
        ui.obj_ltr553_ps_list[i] = lv_obj_create(root);
        lv_obj_remove_style_all(ui.obj_ltr553_ps_list[i]);
        lv_obj_set_size(ui.obj_ltr553_ps_list[i], 20, 10);
        lv_obj_set_pos(ui.obj_ltr553_ps_list[i], 266, 197 - i * 15);

        lv_obj_set_style_bg_opa(ui.obj_ltr553_ps_list[i], LV_OPA_COVER, 0);
        lv_obj_set_style_bg_color(ui.obj_ltr553_ps_list[i], lv_color_hex(0xe95a6f), 0);
        lv_obj_add_flag(ui.obj_ltr553_ps_list[i], LV_OBJ_FLAG_HIDDEN);
    }

    ui.btn_top_center = lv_btn_create(root);
    lv_obj_remove_style_all(ui.btn_top_center);
    lv_obj_set_size(ui.btn_top_center, 170, 68);
    lv_obj_align(ui.btn_top_center, LV_ALIGN_TOP_MID, 0, 0);

    // lv_obj_set_style_border_color(ui.btn_top_center, lv_color_hex(0xff00ff), 0);
    // lv_obj_set_style_border_side(ui.btn_top_center, LV_BORDER_SIDE_FULL, 0);
    // lv_obj_set_style_border_width(ui.btn_top_center, 1, 0);
    // lv_obj_set_style_radius(ui.btn_top_center, 0, 0);
    // lv_obj_set_style_border_post(ui.btn_top_center, true, 0);
}

void AppCameraView::Delete() {
}
