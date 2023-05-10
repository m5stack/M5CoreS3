#ifndef __APPIMU_VIEW_H
#define __APPIMU_VIEW_H

#include "../Page.h"

namespace Page {

class AppIMUView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* imgbtn_home;
        lv_obj_t* imgbtn_next;
        lv_obj_t* btn_top_center;

        lv_obj_t* btn_calibration;
        lv_obj_t* label_notice;
        lv_obj_t* img_compass;
        lv_obj_t* img_cross;
        lv_obj_t* img_ball;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
