#ifndef __APPRTC_VIEW_H
#define __APPRTC_VIEW_H

#include "../Page.h"

namespace Page {

class AppRTCView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* btn_list[6];
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
