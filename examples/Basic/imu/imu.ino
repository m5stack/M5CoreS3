/*
 * SPDX-FileCopyrightText: 2024 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */

#include <M5CoreS3.h>

void setup() {
    auto cfg = M5.config();
    CoreS3.begin(cfg);
    CoreS3.Display.setTextSize(2);   // Set text size.
    CoreS3.Display.setCursor(0, 0);  // Set the cursor.
    delay(200);                      // Delay 200ms.
    CoreS3.Imu.begin();              // Init IMU.
}

void loop() {
    auto imu_update = M5.Imu.update();
    if (imu_update) {
        auto data = M5.Imu.getImuData();

        // The data obtained by getImuData can be used as follows.
        data.accel.x;      // accel x-axis value.
        data.accel.y;      // accel y-axis value.
        data.accel.z;      // accel z-axis value.
        data.accel.value;  // accel 3values array [0]=x / [1]=y / [2]=z.

        data.gyro.x;      // gyro x-axis value.
        data.gyro.y;      // gyro y-axis value.
        data.gyro.z;      // gyro z-axis value.
        data.gyro.value;  // gyro 3values array [0]=x / [1]=y / [2]=z.

        data.mag.x;      // mag x-axis value.
        data.mag.y;      // mag y-axis value.
        data.mag.z;      // mag z-axis value.
        data.mag.value;  // mag 3values array [0]=x / [1]=y / [2]=z.

        data.value;  // all sensor 9values array [0~2]=accel / [3~5]=gyro /
                     // [6~8]=mag

        // gyroscope output related.
        CoreS3.Display.setCursor(0, 20);
        CoreS3.Display.printf(
            "gyroX,  gyroY, gyroZ");  // Screen printingformatted string.
        CoreS3.Display.setCursor(0, 42);
        CoreS3.Display.fillRect(0, 42, 320, 20, BLACK);
        CoreS3.Display.printf("%2.2f\t   %2.2f\t   %2.2f", data.gyro.x,
                              data.gyro.y, data.gyro.z);

        // Accelerometer output is related
        CoreS3.Display.setCursor(0, 70);
        CoreS3.Display.printf("accX,   accY,  accZ");
        CoreS3.Display.setCursor(0, 92);
        CoreS3.Display.fillRect(0, 92, 320, 20, BLACK);
        CoreS3.Display.printf("%2.2f\t   %2.2f\t   %2.2f", data.accel.x,
                              data.accel.y, data.accel.z);

        // Pose output is related
        CoreS3.Display.setCursor(0, 120);
        CoreS3.Display.printf("pitch,  roll,  yaw");
        CoreS3.Display.setCursor(0, 142);
        CoreS3.Display.fillRect(0, 142, 320, 20, BLACK);
        CoreS3.Display.printf("%2.1f  %2.1f  %2.1f", data.mag.x, data.mag.y,
                              data.mag.z);

        delay(10);
    }
}