/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: Display Example.  显示屏示例
* Date: 2023/5/2
*******************************************************************************
*/
#include <M5CoreS3.h>

/* After M5CoreS3 is started or reset the program in the setUp()
function will be run, and this part will only be run once.
在 M5CoreS3启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。
*/
void setup() {
    M5.begin(true, true, false);  // Init M5CoreS3.  初始化 M5CoreS3
    M5.Lcd.fillScreen(WHITE);  // Set the screen background.  设置屏幕底色为白色
    delay(500);                // Delay 500ms.  延迟500ms
    M5.Lcd.fillScreen(RED);
    delay(500);
    M5.Lcd.fillScreen(GREEN);
    delay(500);
    M5.Lcd.fillScreen(BLUE);
    delay(500);
    M5.Lcd.fillScreen(BLACK);
    delay(500);

    M5.Lcd.setCursor(
        10, 10);  // Move the cursor position to (x,y).  移动光标位置到 (x,y)处
    M5.Lcd.setTextColor(
        WHITE);  // Set the font color to white.  设置字体颜色为白色
    M5.Lcd.setTextSize(2);  // Set the font size.  设置字体大小
    M5.Lcd.printf(
        "Display Test!");  // Serial output format string.  输出格式化字符串

    // draw graphic
    delay(1000);
    M5.Lcd.drawRect(100, 100, 50, 50,
                    BLUE);  // Draw a 50x50 blue rectangle wireframe at (x,y).
    delay(1000);  //在（x,y）处画 长宽为50x50的蓝色矩形线框
    M5.Lcd.fillRect(100, 100, 50, 50,
                    BLUE);  // Draw a blue rectangle 50x50 at (x,y)
    delay(1000);            //在（x,y）处画 长宽为50x50的蓝色矩形
    M5.Lcd.drawCircle(100, 100, 50,
                      RED);  // Draw a red circle of radius 50 at (x,y)
    delay(1000);             //在（x,y）处画 半径为50的红色圆线圈
    M5.Lcd.fillCircle(100, 100, 50,
                      RED);  // Draw a red circle of radius 50 at (x,y)
    delay(1000);             //在（x,y）处画 半径为50的红色圆
    M5.Lcd.drawTriangle(30, 30, 180, 100, 80, 150,
                        YELLOW);  // Make a triangle wireframe with (x1,y1)
                                  // (x2,y2) (x3,y3) as the vertices
    delay(1000);  //以 (x1,y1) (x2,y2) (x3,y3)为顶点作三角形线框
    M5.Lcd.fillTriangle(30, 30, 180, 100, 80, 150,
                        YELLOW);  //以 (x1,y1) (x2,y2) (x3,y3)为顶点作三角形
}  // Construct a triangle with (x1,y1) (x2,y2) (x3,y3) as its vertices

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    M5.Lcd.fillTriangle(random(M5.Lcd.width() - 1), random(M5.Lcd.height() - 1),
                        random(M5.Lcd.width() - 1), random(M5.Lcd.height() - 1),
                        random(M5.Lcd.width() - 1), random(M5.Lcd.height() - 1),
                        random(0xfffe));
}