#ifndef __APPSD_MODEL_H
#define __APPSD_MODEL_H

#include <SD.h>
#include "lvgl.h"
#include "M5Unified.h"
#include "config.h"

// TF Detect AW9523 P0.4

namespace Page {

class AppSDModel {
   public:
   bool SDInit();
   void SDDeinit();
   bool GetInitFlag();
   void ClearInitFlag();
   bool IsSDCardExist();
   private:
      bool init_flag = false;
};

}  // namespace Page

#endif
