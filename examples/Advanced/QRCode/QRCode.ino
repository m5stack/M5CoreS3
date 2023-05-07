/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: QRcode.  创建二维码
* Date: 2023/5/5
*******************************************************************************
*/

#include <M5CoreS3.h>

void setup() {
    M5.begin();  // Init M5CoreS3.  初始化M5CoreS3
    M5.Lcd.qrcode(
        "http://www.m5stack.com", 0, 0, 150,
        6);  // Create a QR code with a width of 150 QR code with version 6 at
             // (0, 0).  在(0,0)处创建一个宽为150二维码版本为6的二维码
    // Please select the appropriate QR code version according to the number of
    // characters.  请根据字符数量选择合适的二维码版本
}

void loop() {
}
