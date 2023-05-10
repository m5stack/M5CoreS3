#ifndef __APPCAMERA_VIEW_H
#define __APPCAMERA_VIEW_H

#include "../Page.h"

namespace Page {

class AppCameraView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* imgbtn_home;
        lv_obj_t* imgbtn_next;
        lv_obj_t* btn_top_center;

        lv_obj_t* obj_ltr553_als_list[8];
        lv_obj_t* obj_ltr553_ps_list[8];

        // lv_img_dsc_t img_dsc;
        // lv_obj_t* img_camera;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
