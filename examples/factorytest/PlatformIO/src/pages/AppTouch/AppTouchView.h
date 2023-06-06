#ifndef __APPTOUCH_VIEW_H
#define __APPTOUCH_VIEW_H

#include "../Page.h"

namespace Page {

class AppTouchView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* imgbtn_home;
        lv_obj_t* imgbtn_next;

        lv_obj_t* canvas;

        lv_obj_t* btn_top_center;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
