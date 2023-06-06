#ifndef __HOMEMENU_VIEW_H
#define __HOMEMENU_VIEW_H

#include "../Page.h"

namespace Page {

class HomeMenuView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* btn_factory;
        lv_obj_t* imgbtn_list[9];
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
