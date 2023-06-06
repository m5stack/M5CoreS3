#include <stdarg.h>
#include <stdio.h>
#include "AppPowerView.h"

using namespace Page;

void AppPowerView::Create(lv_obj_t* root) {
    ui.img_bg = lv_img_create(root);
    lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_power_ii"));

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

    ui.img_bat = lv_img_create(root);
    lv_img_set_src(ui.img_bat, ResourcePool::GetImage("app_power_bat0"));
    lv_obj_set_pos(ui.img_bat, 134, 142);

    ui.imgbtn_usb = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_usb, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_imgbtn_set_src(ui.imgbtn_usb, LV_IMGBTN_STATE_RELEASED, NULL,
                      ResourcePool::GetImage("app_power_usbin"), NULL);
    lv_imgbtn_set_src(ui.imgbtn_usb, LV_IMGBTN_STATE_PRESSED, NULL,
                      ResourcePool::GetImage("app_power_usbin"), NULL);
    lv_obj_set_pos(ui.imgbtn_usb, 20, 164);

    ui.imgbtn_bus = lv_imgbtn_create(root);
    lv_obj_set_size(ui.imgbtn_bus, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_imgbtn_set_src(ui.imgbtn_bus, LV_IMGBTN_STATE_RELEASED, NULL,
                      ResourcePool::GetImage("app_power_busin"), NULL);
    lv_imgbtn_set_src(ui.imgbtn_bus, LV_IMGBTN_STATE_PRESSED, NULL,
                      ResourcePool::GetImage("app_power_busin"), NULL);
    lv_obj_set_pos(ui.imgbtn_bus, 250, 164);

    ui.label_vbat = lv_label_create(ui.img_bat);
    lv_label_set_text(ui.label_vbat, "0.0V");
    lv_obj_align(ui.label_vbat, LV_ALIGN_BOTTOM_MID, 3, -6);

    ui.label_vbus = lv_label_create(root);
    lv_label_set_text(ui.label_vbus, "0.0V");
    lv_obj_set_pos(ui.label_vbus, 88, 102);

    ui.label_tdie = lv_label_create(root);
    lv_label_set_text(ui.label_tdie, "0.0");
    lv_obj_set_pos(ui.label_tdie, 146, 78);

    ui.label_vmbus = lv_label_create(root);
    lv_label_set_text(ui.label_vmbus, "0.0V");
    lv_obj_set_pos(ui.label_vmbus, 200, 120);
}

void AppPowerView::Delete() {
}

void AppPowerView::ChangeBgImg(uint8_t mode) {
    switch (mode) {
        case POWER_MODE_USB_IN_BUS_IN:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_power_ii"));
            break;
        case POWER_MODE_USB_IN_BUS_OUT:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_power_io"));
            break;
        case POWER_MODE_USB_OUT_BUS_IN:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_power_oi"));
            break;
        case POWER_MODE_USB_OUT_BUS_OUT:
            lv_img_set_src(ui.img_bg, ResourcePool::GetImage("app_power_oo"));
            break;
        default:
            break;
    }
}

void AppPowerView::ChangeBatImg(uint8_t index) {
    switch (index) {
        case 0:
            lv_img_set_src(ui.img_bat,
                           ResourcePool::GetImage("app_power_bat0"));
            break;
        case 1:
            lv_img_set_src(ui.img_bat,
                           ResourcePool::GetImage("app_power_bat1"));
            break;
        case 2:
            lv_img_set_src(ui.img_bat,
                           ResourcePool::GetImage("app_power_bat2"));
            break;
        default:
            break;
    }
}

void AppPowerView::ChangeUsbImg(bool usb_out) {
    if (usb_out) {
        lv_imgbtn_set_src(ui.imgbtn_usb, LV_IMGBTN_STATE_RELEASED, NULL,
                          ResourcePool::GetImage("app_power_usbout"), NULL);
        lv_imgbtn_set_src(ui.imgbtn_usb, LV_IMGBTN_STATE_PRESSED, NULL,
                          ResourcePool::GetImage("app_power_usbout"), NULL);
    } else {
        lv_imgbtn_set_src(ui.imgbtn_usb, LV_IMGBTN_STATE_RELEASED, NULL,
                          ResourcePool::GetImage("app_power_usbin"), NULL);
        lv_imgbtn_set_src(ui.imgbtn_usb, LV_IMGBTN_STATE_PRESSED, NULL,
                          ResourcePool::GetImage("app_power_usbin"), NULL);
    }
}

void AppPowerView::ChangeBusImg(bool bus_out) {
    if (bus_out) {
        lv_imgbtn_set_src(ui.imgbtn_bus, LV_IMGBTN_STATE_RELEASED, NULL,
                          ResourcePool::GetImage("app_power_busout"), NULL);
        lv_imgbtn_set_src(ui.imgbtn_bus, LV_IMGBTN_STATE_PRESSED, NULL,
                          ResourcePool::GetImage("app_power_busout"), NULL);
    } else {
        lv_imgbtn_set_src(ui.imgbtn_bus, LV_IMGBTN_STATE_RELEASED, NULL,
                          ResourcePool::GetImage("app_power_busin"), NULL);
        lv_imgbtn_set_src(ui.imgbtn_bus, LV_IMGBTN_STATE_PRESSED, NULL,
                          ResourcePool::GetImage("app_power_busin"), NULL);
    }
}