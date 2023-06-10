#include <Arduino.h>
#include <BMI270_Sensor.h>

I2C_IMU IMU;

/* After ESP32 is started or reset the program in the setUp()
function will be run, and this part will only be run once.
在 ESP32启动或者复位后，即会开始执行setup()函数中的程序，该部分只会执行一次。
*/
void setup() {
    USBSerial.begin(115200);
    USBSerial.flush();
    delay(1500);
    Wire1.begin(12, 11, 100000UL);
    IMU.Init();  // Init IMU. 初始化IMU
}

/* After the program in setup() runs, it runs the program in loop()
The loop() function is an infinite loop in which the program runs repeatedly
在setup()函数中的程序执行完后，会接着执行loop()函数中的程序
loop()函数是一个死循环，其中的程序会不断的重复运行 */
void loop() {
    IMU.Update();  // Update data from IMU. 更新IMU数据
    USBSerial.printf("\nAcc_X = %4.2f\t Acc_Y = %4.2f\t Acc_Z = %4.2f\n",
                     IMU.accel_data.x, IMU.accel_data.y, IMU.accel_data.z);
    USBSerial.printf("\nGyro_X = %4.2f\t Gyro_Y = %4.2f\t Gyro_Z = %4.2f\n\n",
                     IMU.gyro_data.x, IMU.gyro_data.y, IMU.gyro_data.z);

    delay(10);
}