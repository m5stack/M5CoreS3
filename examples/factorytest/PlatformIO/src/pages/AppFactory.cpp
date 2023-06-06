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
#include "AppFactory.h"
// #include "_Template/Template.h"
#include "StartUp/StartUp.h"
#include "FactoryTest/FactoryTest.h"
#include "HomeMenu/HomeMenu.h"
#include "AppWiFi/AppWiFi.h"
#include "AppCamera/AppCamera.h"
#include "AppMic/AppMic.h"
#include "AppPower/AppPower.h"
#include "AppIMU/AppIMU.h"
#include "AppSD/AppSD.h"
#include "AppTouch/AppTouch.h"
#include "AppI2C/AppI2C.h"
#include "AppRTC/AppRTC.h"

#define APP_CLASS_MATCH(className)           \
    do {                                     \
        if (strcmp(name, #className) == 0) { \
            return new Page::className;      \
        }                                    \
    } while (0)

PageBase* AppFactory::CreatePage(const char* name) {
    APP_CLASS_MATCH(StartUp);
    APP_CLASS_MATCH(FactoryTest);
    APP_CLASS_MATCH(HomeMenu);
    APP_CLASS_MATCH(AppWiFi);
    APP_CLASS_MATCH(AppCamera);
    APP_CLASS_MATCH(AppMic);
    APP_CLASS_MATCH(AppPower);
    APP_CLASS_MATCH(AppIMU);
    APP_CLASS_MATCH(AppSD);
    APP_CLASS_MATCH(AppTouch);
    APP_CLASS_MATCH(AppI2C);
    APP_CLASS_MATCH(AppRTC);

    return nullptr;
}
