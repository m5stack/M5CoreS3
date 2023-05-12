/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: Hello World
* Date: 2023/5/3
*******************************************************************************
*/
#include <M5CoreS3.h>

/* After M5CoreS3 is started or reset the program in the setUp()
function will be run, and this part will only be run once.
在 M5CoreS3启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。
*/
void setup() {
    M5.begin(true, true, false);  // Init M5CoreS3.  初始化 M5CoreS3
    M5.Lcd.setTextSize(2);        // Set text size. 设置文字大小
    M5.Lcd.setCursor(100, 120);   // Set the cursor. 设置光标位置
    M5.Lcd.print("Hello World");  // Print text on the screen (string)
                                  // 在屏幕上打印文本(字符串)
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    USBSerial.println(
        "Hello World");  // Print text on the serial port.在串口输出文本
    delay(500);          // Delay 500ms.  延迟500ms
}