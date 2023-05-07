/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: WIFI TCP.
* Date: 2023/5/5
*******************************************************************************
  M5CoreS3 will sends a message to a TCP server
  M5CoreS3 将向TCP服务器发送一条数据
*/

#include <M5CoreS3.h>
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;

// Configure the name and password of the connected wifi.
// 配置所连接wifi的名称、密码
const char* ssid     = "your-wifi";
const char* password = "your-password";

void setup() {
    int sum = 0;
    M5.begin();  // Init M5CoreS3.  初始化M5CoreS3
    WiFiMulti.addAP(
        ssid,
        password);  // Add wifi configuration information.  添加wifi配置信息
    M5.lcd.print(
        "\nWaiting connect to WiFi...");  // Serial port output format string.
                                          // 串口输出格式化字符串
    while (WiFiMulti.run() !=
           WL_CONNECTED) {  // If the connection to wifi is not established
                            // successfully.  如果没有与wifi成功建立连接
        M5.lcd.print(".");
        delay(1000);
        sum += 1;
        if (sum == 8) M5.lcd.print("Conncet failed!");
    }
    M5.lcd.println("\nWiFi connected");
    M5.lcd.print("IP address: ");
    M5.lcd.println(
        WiFi.localIP());  // The serial port outputs the IP address
                          // of the M5CoreS3.  串口输出M5CoreS3的IP地址
    delay(500);
}

void loop() {
    M5.lcd.setCursor(0, 40);
    const char* host = "www.baidu.com";  // Set the IP address or DNS of the TCP
                                         // server.  设置TCP服务器的ip或dns
    const uint16_t port =
        80;  // The port of the TCP server is specified.  设置TCP服务器的端口
    M5.lcd.printf("Connecting to: %s\n", host);

    WiFiClient client;
    if (!client.connect(
            host,
            port)) {  // Connect to the server. 0 is returned if the connection
                      // fails.  连接服务器,若连接失败返回0
        M5.lcd.print(
            "Connection failed.\nWaiting 5 seconds before retrying...\n");
        delay(5000);
        return;
    }
    // send an arbitrary string to the server.  发送一个字符串到上边连接的服务器
    client.print("Send this data to the server");
    // send a basic document request to the server.
    // 向服务器发送一个基本的文档请求.
    client.print("GET /index.html HTTP/1.1\n\n");
    int maxloops = 0;

    // wait for the server's reply to become available
    //等待服务器的回复
    while (!client.available() && maxloops < 1000) {
        maxloops++;
        delay(1);  // delay 1 msec
    }
    if (client.available() >
        0) {  // Detects whether data is received.  检测是否接收到数据
        String line = client.readStringUntil(
            '\r');  // Read information from data received by the device until
                    // \r is read.  从设备接收到的数据中读取信息,直至读取到\r时
        M5.lcd.println(line);  // String received by serial port output.
                               // 串口输出接收到的字符串
    } else {
        M5.lcd.println("client.available() timed out ");
    }
    M5.lcd.println("Closing connection.");
    client.stop();
    M5.lcd.println("Waiting 5 seconds before restarting...");
    delay(5000);
    M5.lcd.fillRect(0, 40, 320, 220, BLACK);
}
