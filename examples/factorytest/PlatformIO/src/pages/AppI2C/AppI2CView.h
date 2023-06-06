#ifndef __APPI2C_VIEW_H
#define __APPI2C_VIEW_H

#include "../Page.h"

namespace Page {

class AppI2CView {
   public:
    void Create(lv_obj_t* root);
    void Delete();
    void ChangeBgImg(uint8_t index);

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* imgbtn_home;
        lv_obj_t* imgbtn_next;
        lv_obj_t* btn_top_center;

        lv_obj_t* cont_addr;
        lv_obj_t* label_notice;
        lv_obj_t* btn_scan_again;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
