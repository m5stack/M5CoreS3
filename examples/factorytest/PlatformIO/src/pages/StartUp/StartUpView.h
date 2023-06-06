#ifndef __STARTUP_VIEW_H
#define __STARTUP_VIEW_H

#include "../Page.h"

namespace Page {

class StartUpView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* img_core_text;
        lv_obj_t* img_s3_text;
        lv_obj_t* btn_info;

        lv_obj_t* img_cores3_diagram;
        // lv_obj_t* btn_next;

        lv_anim_timeline_t* anim_timeline;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
