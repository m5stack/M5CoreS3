/*
 * MIT License
 * Copyright (c) 2021 _VIFEXTech
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#ifndef __PAGE_H
#define __PAGE_H

#include <Arduino.h>
#include <Wire.h>
#include "esp_camera.h"
#include "M5Unified.h"
#include "M5GFX.h"
#include "lvgl.h"
#include "config.h"

#include "PageManager.h"
#include "lv_obj_ext_func.h"
#include "lv_anim_timeline_wrapper.h"
#include "lv_anim_label.h"

#include "res/ResourcePool.h"

#define ANIM_DEF(start_time, obj, attr, start, end, time)      \
    {                                                          \
        start_time, obj, LV_ANIM_EXEC(attr), start, end, time, \
            lv_anim_path_ease_out, true                        \
    }

#endif
