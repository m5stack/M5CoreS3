#ifndef _I2C_IMU_H_
#define _I2C_IMU_H_
#include <Arduino.h>
#include <driver/i2s.h>
#include <driver/i2c.h>
#include "BMI270_Sensor.h"

#define ACCEL UINT8_C(0x00)
#define GYRO  UINT8_C(0x01)
#define AUX   UINT8_C(0x02)

#define GRAVITY_EARTH (9.80665f)

class I2C_IMU {
   public:
    struct Accel {
        float x;
        float y;
        float z;
    } accel_data;
    struct Gyro {
        float x;
        float y;
        float z;
    } gyro_data;
    struct Mag {
        int16_t x;
        int16_t y;
        int16_t z;
        struct Raw {
            int16_t x;
            int16_t y;
            int16_t z;
        } raw;
        struct Offset {
            int16_t x;
            int16_t y;
            int16_t z;
        } offset;
    } mag_data;

   public:
    I2C_IMU();
    ~I2C_IMU();

    void Init();
    void Update();
    float CalcuDir();
    void MagCalibration();
    /*     bool ReadCalibration();
        bool SaveCalibration();
    void read_bmi_bmm_data(struct bmi2_sens_data *accel_gyro_data,
                           struct bmm150_mag_data *mag_data,
                           struct bmm150_raw_mag_data *raw_mag_data);
    */
   private:
    const uint8_t BMI270_ADDR = BMI2_I2C_SEC_ADDR;
    const uint8_t BMM150_ADDR = BMM150_DEFAULT_I2C_ADDRESS;
    uint8_t sensor_list[3]    = {BMI2_ACCEL, BMI2_GYRO, BMI2_AUX};
    uint16_t bmi_bmm_init_status;

    bmi2_sens_config config[3];
    bmi2_sens_data bmi_sensor_data = {{0}};

    bmm150_settings bmm_settings;
    bmm150_mag_data bmm_mag_data;
    bmm150_raw_mag_data bmm_raw_mag_data;

    int _deviceAddress;

    static int8_t bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data,
                                uint32_t len, void *intf_ptr);
    static int8_t bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data,
                                 uint32_t len, void *intf_ptr);
    static void bmi2_delay_us(uint32_t period, void *intf_ptr);

    static int8_t aux_i2c_read(uint8_t reg_addr, uint8_t *reg_data,
                               uint32_t length, void *intf_ptr);
    static int8_t aux_i2c_write(uint8_t reg_addr, const uint8_t *reg_data,
                                uint32_t length, void *intf_ptr);

    float lsb_to_mps2(int16_t val, float g_range, uint8_t bit_width);

    float lsb_to_dps(int16_t val, float dps, uint8_t bit_width);
};

#endif