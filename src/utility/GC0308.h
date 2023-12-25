#ifndef GC0308_H
#define GC0308_H

#include "M5Unified.h"
#include "esp_camera.h"

class GC0308 {
   private:
   public:
    camera_fb_t* fb;
    sensor_t* sensor;
    camera_config_t* config;
    bool begin();
    bool get();
    bool free();
};

#endif