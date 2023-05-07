/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: RTC--实时时钟示例
* Date: 2023/5/1
*******************************************************************************
*/
#include <M5CoreS3.h>

RTC_TimeTypeDef RTCtime;
RTC_DateTypeDef RTCDate;

char timeStrbuff[64];

void flushTime() {
    M5.Rtc.GetTime(&RTCtime);  // Gets the time in the real-time clock.
                               // 获取实时时钟内的时间
    M5.Rtc.GetDate(&RTCDate);
    sprintf(timeStrbuff, "%d/%02d/%02d %02d:%02d:%02d", RTCDate.Year,
            RTCDate.Month, RTCDate.Date, RTCtime.Hours, RTCtime.Minutes,
            RTCtime.Seconds);
    // Stores real-time time and date data
    // to timeStrbuff.
    // 将实时时间、日期数据存储至timeStrbuff
    M5.Lcd.setCursor(40, 100);
    // Move the cursor position to (x,y).  移动光标位置到(x,y)处
    M5.Lcd.println(timeStrbuff);
    // Output the contents of.  输出timeStrbuff中的内容
}

void setupTime() {
    RTCtime.Hours   = 16;  // Set the time.  设置时间
    RTCtime.Minutes = 51;
    RTCtime.Seconds = 20;
    if (!M5.Rtc.SetTime(&RTCtime)) Serial.println("wrong time set!");
    // and writes the set time to the real
    // time clock. 并将设置的时间写入实时时钟
    RTCDate.Year  = 2023;  // Set the date.  设置日期
    RTCDate.Month = 5;
    RTCDate.Date  = 4;
    if (!M5.Rtc.SetDate(&RTCDate)) Serial.println("wrong date set!");
}

/* After M5CoreS3 is started or reset the program in the setUp ()
function will be run, and this part will only be run once.
在M5CoreS3启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。
*/
void setup() {
    M5.begin(true, true, false);  // Init M5CoreS3.  初始化 M5CoreS3
    delay(1000);
    setupTime();
    M5.Lcd.setTextSize(2);  // Set the text size.  设置文本大小
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    flushTime();
    delay(1000);
}