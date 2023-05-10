#ifndef __TEMPLATE_VIEW_H
#define __TEMPLATE_VIEW_H

#include "../Page.h"

namespace Page {

class TemplateView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* labelTitle;
        lv_obj_t* labelTick;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
