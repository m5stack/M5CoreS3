#ifndef __APPPOWER_VIEW_H
#define __APPPOWER_VIEW_H

#include "../Page.h"

namespace Page {

class AppPowerView {
   public:
    void Create(lv_obj_t* root);
    void Delete();
    void ChangeBgImg(uint8_t mode);
    void ChangeBatImg(uint8_t index);
    void ChangeUsbImg(bool usb_in);
    void ChangeBusImg(bool bus_in);

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* imgbtn_home;
        lv_obj_t* imgbtn_next;
        lv_obj_t* btn_top_center;

        lv_obj_t* label_tdie;
        lv_obj_t* label_vbat;
        lv_obj_t* label_vbus;
        lv_obj_t* label_vmbus;
        lv_obj_t* img_bat;
        lv_obj_t* imgbtn_usb;
        lv_obj_t* imgbtn_bus;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
