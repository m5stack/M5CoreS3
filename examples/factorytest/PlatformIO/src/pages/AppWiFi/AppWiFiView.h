#ifndef __APPWIFI_VIEW_H
#define __APPWIFI_VIEW_H

#include "../Page.h"

namespace Page {

class AppWiFiView {
   public:
    void Create(lv_obj_t* root);
    void Delete();

   public:
    struct {
        lv_obj_t* img_bg;
        lv_obj_t* imgbtn_home;
        lv_obj_t* imgbtn_next;

        lv_obj_t* btn_top_center;

        lv_obj_t* cont_wifi;
        lv_obj_t* wifi_ssid_list;

        lv_obj_t* label_scaning;
    } ui;

   private:
};

}  // namespace Page

#endif  // !__VIEW_H
