/*
*******************************************************************************
* Copyright (c) 2023 by M5Stack
*                  Equipped with M5CoreS3 sample source code
*                          配套  M5CoreS3 示例源代码
* Visit for more information: https://docs.m5stack.com/en/core/CoreS3
* 获取更多资料请访问: https://docs.m5stack.com/zh_CN/core/CoreS3
*
* Describe: BMI270 example.  IMU
* Date: 2023/5/5
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
    M5.Lcd.setCursor(0, 0);       // Set the cursor. 设置光标位置
    delay(200);                   // Delay 200ms.  延迟200ms
    M5.IMU.Init();                // Init IMU. 初始化IMU
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    M5.IMU.Update();  // Update data from IMU. 更新IMU数据
    M5.Lcd.setCursor(30, 70);

    // gyroscope output related.  陀螺仪输出相关
    M5.Lcd.printf("gyroX,  gyroY, gyroZ");  // Screen printingformatted string.
                                            // 输出格式化字符串
    M5.Lcd.setCursor(30, 92);
    M5.Lcd.fillRect(30, 92, 320, 20, BLACK);
    M5.Lcd.printf("%4.2f\t   %4.2f\t   %4.2f", M5.IMU.gyro_data.x,
                  M5.IMU.gyro_data.y, M5.IMU.gyro_data.z);

    // Accelerometer output is related
    //加速度计输出相关
    M5.Lcd.setCursor(30, 120);
    M5.Lcd.printf("accX,   accY,  accZ");
    M5.Lcd.setCursor(30, 142);
    M5.Lcd.fillRect(30, 142, 320, 20, BLACK);
    M5.Lcd.printf("%4.2f\t   %4.2f\t   %4.2f", M5.IMU.accel_data.x,
                  M5.IMU.accel_data.y, M5.IMU.accel_data.z);

    USBSerial.printf("\nGyro_X = %4.2f\t Gyro_Y = %4.2f\t Gyro_Z = %4.2f\n\n",
                     M5.IMU.gyro_data.x, M5.IMU.gyro_data.y,
                     M5.IMU.gyro_data.z);
    USBSerial.printf("\nAcc_X = %4.2f\t Acc_Y = %4.2f\t Acc_Z = %4.2f\n",
                     M5.IMU.accel_data.x, M5.IMU.accel_data.y,
                     M5.IMU.accel_data.z);

    delay(10);
}