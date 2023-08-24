/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/unit/rgb
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/unit/rgb
*
* Describe: RGB.  多彩灯
* Date: 2023/8/24
*******************************************************************************
Please connect to Port B(8,9),Control RGB Unit to scroll through three
colors of red, green and blue.
请连接端口B(8,9),控制RGB单元滚动红、绿、蓝三种颜色.
*/

#include <M5CoreS3.h>
#include <Adafruit_NeoPixel.h>

#define PIN       9  //定义NeoPixel的控制引脚
#define NUMPIXELS 3  //定义NeoPixel控制灯灯数量

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
    NUMPIXELS, PIN,
    NEO_GRB + NEO_KHZ800);  // set number of LEDs, pin number, LED type.
                            // 设置灯的数量,控制引脚编号,灯灯类型

void setup() {
    M5.begin();  // Init M5CoreS3.  初始化M5CoreS3
    M5.Axp.powerModeSet(POWER_MODE_USB_IN_BUS_OUT);
    pixels.begin();  // Init the NeoPixel.  初始化NeoPixel
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(90, 0);
    M5.Lcd.println(("RGB Example"));
}

int i = 0, j = 1, k = 2;

void loop() {
    pixels.setPixelColor(i++, pixels.Color(100, 0, 0));  // Bright red
    pixels.setPixelColor(j++, pixels.Color(0, 100, 0));  // Bright green
    pixels.setPixelColor(k++, pixels.Color(0, 0, 100));  // Bright blue
    pixels.show();  // sends the updated color to the hardware.
                    // 将更新后的颜色发送到硬件。
    delay(100);
    if (i == 3)
        i = 0;
    else if (j == 3)
        j = 0;
    else if (k == 3)
        k = 0;
}