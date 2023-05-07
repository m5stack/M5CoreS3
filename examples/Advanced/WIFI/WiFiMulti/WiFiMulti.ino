/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: WIFI Multi.  多wifi择优
* Date: 2023/5/5
*******************************************************************************
*  Connect to the best AP based on a given wifi list
*  根据给定wifi的列表连接到最好的AP
*/

#include <M5CoreS3.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti wifiMulti;

void setup() {
    M5.begin();  // Init M5CoreS3.  初始化 M5CoreS3
    wifiMulti.addAP("wifi1",
                    "12345566");  // Storage wifi configuration information 1.
                                  // 存储wifi配置信息1
    wifiMulti.addAP("wifi2", "12345566");
    wifiMulti.addAP("aaa", "sadf");
    M5.lcd.print("Connecting Wifi...");  // Serial port format output string.
                                         // 串口格式化输出字符串
}

void loop() {
    if (wifiMulti.run() ==
        WL_CONNECTED) {  // If the connection to wifi is established
                         // successfully.  如果与wifi成功建立连接
        M5.lcd.setCursor(0, 20);
        M5.lcd.print("WiFi connected\n\nSSID:");
        M5.lcd.println(WiFi.SSID());  // Output Network name.  输出网络名称
        M5.lcd.print("RSSI: ");
        M5.lcd.println(WiFi.RSSI());  // Output signal strength.  输出信号强度
        M5.lcd.print("IP address: ");
        M5.lcd.println(WiFi.localIP());  // Output IP Address.  输出IP地址
        delay(1000);
        M5.lcd.fillRect(0, 20, 180, 300,
                        BLACK);  // It's equivalent to partial screen clearance.
                                 // 相当于部分清屏
    } else {
        // If the connection to wifi is not established successfully.
        // 如果没有与wifi成功建立连接
        M5.lcd.print(".");
        delay(1000);
    }
}