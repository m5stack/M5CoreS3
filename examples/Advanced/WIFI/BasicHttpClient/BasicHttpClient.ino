/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: BasicHTTPClient.
* Date: 2023/5/5
******************************************************************************
*/
#include <M5CoreS3.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

WiFiMulti wifiMulti;
HTTPClient http;

// Configure the name and password of the connected wifi.
// 配置所连接wifi的名称、密码
const char* ssid     = "your-wifi";
const char* password = "your-password";

void setup() {
    M5.begin();  // Init M5CoreS3.  初始化 M5CoreS3
    wifiMulti.addAP(ssid,
                    password);  // Storage wifi configuration information.
                                // 存储wifi配置信息
    M5.Lcd.print("\nConnecting Wifi...\n");  // print format output string on
                                             // lcd.  串口格式化输出字符串
}

void loop() {
    M5.Lcd.setCursor(0, 0);  // Set the cursor at (0,0).  设置光标位于(0,0)处
    if ((wifiMulti.run() ==
         WL_CONNECTED)) {  // wait for WiFi connection.  等待连接至wifi
        M5.Lcd.print("[HTTP] begin...\n");
        http.begin(
            "http://example.com/index.html");  // configure traged server and
                                               // url.  配置被跟踪的服务器和URL
        M5.Lcd.print("[HTTP] GET...\n");
        int httpCode = http.GET();  // start connection and send HTTP header.
                                    // 开始连接服务器并发送HTTP的标头
        if (httpCode >
            0) {  // httpCode will be negative on error.  出错时httpCode将为负值
            M5.Lcd.printf("[HTTP] GET... code: %d\n", httpCode);

            if (httpCode ==
                HTTP_CODE_OK) {  // file found at server.  在服务器上找到文件
                String payload = http.getString();
                M5.Lcd.println(payload);  //打印在服务器上读取的文件.  Print
                                          // files read on the server
            }
        } else {
            M5.Lcd.printf("[HTTP] GET... failed, error: %s\n",
                          http.errorToString(httpCode).c_str());
        }
        http.end();
    } else {
        M5.Lcd.print("connect failed");
    }
    delay(5000);
    M5.Lcd.clear();  // clear the screen.  清除屏幕
}
