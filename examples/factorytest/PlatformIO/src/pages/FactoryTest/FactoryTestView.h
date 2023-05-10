#ifndef __FactoryTest_VIEW_H
#define __FactoryTest_VIEW_H

#include "../Page.h"

namespace Page {

class FactoryTestView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* cont;
        lv_obj_t* btn_next;
        lv_obj_t* label_next;
        lv_obj_t* btn_fail;
        lv_obj_t* label_prev;

        lv_obj_t* label_test_title;
        lv_obj_t* label_wifi_ip;
        lv_obj_t* img_test_result;
#if MONKEY_TEST_ENABLE
        lv_obj_t* btn_return;
#endif
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
