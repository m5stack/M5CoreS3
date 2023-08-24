/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: TF Card. TF卡
* Date: 2023/8/24
*******************************************************************************
  In this example, we will detect the existence of a file and perform read and
  write operations on it
  在这个示例中,我们将会检测某文件是否存在,并进行读写文件操作
*/

#include <M5CoreS3.h>

void setup() {
    M5.begin(true, true, true);
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(60, 0);
    M5.Lcd.print("SD Card Example");
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.print("Pls open the serial port.");
    M5.Lcd.endWrite();

    SPI.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, TFCARD_CS_PIN);
    if (M5.Axp.isSDCardExist()) {
        // Initialize the SD card. 初始化SD卡.
        if (!SD.begin(GPIO_NUM_4, SPI, 25000000)) {
            // Print a message if the SD card initialization
            // fails orif the SD card does not exist.
            // 如果SD卡初始化失败或者SD卡不存在，则打印消息.
            USBSerial.println("Card failed, or not present");
            while (1)
                ;
        }
    } else {
        USBSerial.println("Please insert SD card");
    }

    USBSerial.println("TF card initialized.");
    // Check if the "/hello.txt" file exists.
    // 查看是否存在"/hello.txt"文件
    if (SD.exists("/hello.txt")) {
        USBSerial.println("hello.txt exists.");
    } else {
        USBSerial.println("hello.txt doesn't exist.");
    }
    USBSerial.println("Creating hello.txt");
    File myFile = SD.open("/hello.txt",
                          FILE_WRITE);  // Create a new file "/hello.txt".
                                        // 创建一个新文件"/hello.txt"
    if (myFile) {  // If the file is open, then write to it.
                   // 如果文件打开,则进行写入操作
        USBSerial.println("Writing to test.txt...");
        myFile.println("SD test.");
        myFile.close();  // Close the file. 关闭文件
        USBSerial.println("done.");
    } else {
        USBSerial.println("error opening test.txt");
    }
    delay(500);
    // Open the file "/hello.txt" in read mode.
    // 以读取模式打开文件"/hello.txt"
    myFile = SD.open("/hello.txt", FILE_READ);
    if (myFile) {
        USBSerial.println("/hello.txt Content:");
        // Read the data from the file and print it until the reading is
        // complete. 从文件里读取数据并打印到串口,直到读取完成.
        while (myFile.available()) {
            USBSerial.write(myFile.read());
        }
        myFile.close();
    } else {
        USBSerial.println(
            "error opening /hello.txt");  // If the file is not open.
                                          // 如果文件没有打开
    }
}
void loop() {
}