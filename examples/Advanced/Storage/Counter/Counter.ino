/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: counter.  计数器
* Date: 2023/5/5
*******************************************************************************
*/

#include <M5CoreS3.h>
#include <Preferences.h>

Preferences preferences;

void setup() {
    M5.begin();  // Init M5CoreS3.  初始化 M5CoreS3
    M5.Lcd.setTextSize(2);
    preferences.begin(
        "my-app",
        false);  // We will open storage in RW-mode (second parameter has to be
                 // false).
                 // 在perferences中创建叫my-app的空间,并以rw模式打开存储(第二个参数必须为false)

    // preferences.clear();  // Remove all preferences under the opened
    // namespace.清除preferences中所有的空间

    // preferences.remove("counter");  // Or remove the counter key only.
    // 只清除counter中的值

    unsigned int counter = preferences.getUInt(
        "counter",
        0);  // Get the counter value in current sapce, if the key does not
             // exist, return a default value of 0.
             // 在当前空间中读取counter的值(若不存在为0),并赋值给counter
    counter++;  // Increase counter by 1.  使计数器的值加一
    M5.Lcd.printf(
        "Current counter value: %u\n",
        counter);  // Print the counter to Serial Monitor.  串口输出计数器的值
    preferences.putUInt(
        "counter",
        counter);  // Store the counter to the Preferences.  存储计数器的值
    preferences.end();  // Close the Preferences.  关闭Preferences
}
void loop() {
    for (int i = 10; i > 0; i--) {
        M5.Lcd.setCursor(0, 18);
        M5.Lcd.printf("Restarting in %d seconds..", i);
        delay(1000);
        M5.Lcd.fillRect(0, 18, 320, 20, BLACK);
    }
    M5.Lcd.setCursor(0, 18);
    M5.Lcd.printf("Device will be rebooted soon");
    ESP.restart();  // Restart.  重启
}
