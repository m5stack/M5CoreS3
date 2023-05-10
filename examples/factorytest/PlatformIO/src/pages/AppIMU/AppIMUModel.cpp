#include "AppIMUModel.h"

using namespace Page;

bmi2_dev aux_bmi2_dev;
bmm150_dev aux_bmm150_dev;

bool bmm150_init_flag = false;  // FIXME: dirty code 

AppIMUModel::AppIMUModel() {
}

AppIMUModel::~AppIMUModel() {
}

void AppIMUModel::Init() {
    config[ACCEL].type = BMI2_ACCEL;
    config[GYRO].type  = BMI2_GYRO;
    config[AUX].type   = BMI2_AUX;

    /* To enable the i2c interface settings for bmi270. */
    aux_bmi2_dev.intf            = BMI2_I2C_INTF;
    aux_bmi2_dev.read            = bmi2_i2c_read;
    aux_bmi2_dev.write           = bmi2_i2c_write;
    aux_bmi2_dev.delay_us        = bmi2_delay_us;
    aux_bmi2_dev.read_write_len  = 30;
    aux_bmi2_dev.config_file_ptr = NULL;
    aux_bmi2_dev.intf_ptr        = (void *)&bmi270_addr;

    /* To enable the i2c interface settings for bmm150. */
    aux_bmm150_dev.intf_ptr = (void *)&bmm150_addr;
    aux_bmm150_dev.read     = aux_i2c_read;
    aux_bmm150_dev.write    = aux_i2c_write;
    aux_bmm150_dev.delay_us = bmi2_delay_us;
    /* As per datasheet, aux interface with bmi270 will support only for I2C */
    aux_bmm150_dev.intf = BMM150_I2C_INTF;

    /* Initialize bmi270. */
    int8_t ret = bmi270_init(&aux_bmi2_dev);

    /* Pull-up resistor 2k is set to the trim regiter */
    uint8_t regdata = BMI2_ASDA_PUPSEL_2K;
    ret = bmi2_set_regs(BMI2_AUX_IF_TRIM, &regdata, 1, &aux_bmi2_dev);

    /* Get default configurations for the type of feature selected. */
    ret = bmi270_get_sensor_config(config, 3, &aux_bmi2_dev);

    /* Configurations for accel. */
    config[ACCEL].cfg.acc.filter_perf = BMI2_PERF_OPT_MODE;
    config[ACCEL].cfg.acc.bwp         = BMI2_ACC_OSR2_AVG2;
    config[ACCEL].cfg.acc.odr         = BMI2_ACC_ODR_100HZ;
    config[ACCEL].cfg.acc.range       = BMI2_ACC_RANGE_2G;

    /* Configurations for gyro. */
    config[GYRO].cfg.gyr.filter_perf = BMI2_PERF_OPT_MODE;
    config[GYRO].cfg.gyr.noise_perf  = BMI2_GYR_RANGE_2000;
    config[GYRO].cfg.gyr.bwp         = BMI2_GYR_OSR2_MODE;
    config[GYRO].cfg.gyr.odr         = BMI2_GYR_ODR_100HZ;
    config[GYRO].cfg.gyr.range       = BMI2_GYR_RANGE_2000;
    config[GYRO].cfg.gyr.ois_range   = BMI2_GYR_OIS_2000;

    /* Configurations for aux. */
    config[AUX].cfg.aux.odr             = BMI2_AUX_ODR_100HZ;
    config[AUX].cfg.aux.aux_en          = BMI2_ENABLE;
    config[AUX].cfg.aux.i2c_device_addr = BMM150_DEFAULT_I2C_ADDRESS;
    config[AUX].cfg.aux.fcu_write_en    = BMI2_ENABLE;
    config[AUX].cfg.aux.man_rd_burst    = BMI2_AUX_READ_LEN_3;
    config[AUX].cfg.aux.read_addr       = BMM150_REG_DATA_X_LSB;

    /* Set new configurations for accel, gyro and aux. */
    ret = bmi270_set_sensor_config(config, 3, &aux_bmi2_dev);

    /* NOTE:
     * Accel and gyro enable must be done after setting configurations
     */
    ret = bmi270_sensor_enable(sensor_list, 3, &aux_bmi2_dev);

    /* Initialize bmm150. */
    ret = bmm150_init(&aux_bmm150_dev);

    /* Set the power mode to normal mode. */
    bmm_settings.pwr_mode = BMM150_POWERMODE_NORMAL;
    ret                   = bmm150_set_op_mode(&bmm_settings, &aux_bmm150_dev);

    ret = bmi270_get_sensor_config(config, 3, &aux_bmi2_dev);

    /* Disable manual mode so that the data mode is enabled. */
    config[AUX].cfg.aux.manual_en = BMI2_DISABLE;

    /* Set the aux configurations. */
    ret = bmi270_set_sensor_config(config, 3, &aux_bmi2_dev);

    /* Map data ready interrupt to interrupt pin. */
    ret = bmi2_map_data_int(BMI2_DRDY_INT, BMI2_INT1, &aux_bmi2_dev);

    // Serial.printf("Valid BMM150 (Aux) sensor - Chip ID : 0x%x\r\n",
    //               aux_bmm150_dev.chip_id);

    if (aux_bmm150_dev.chip_id == BMM150_CHIP_ID) {
        bmm150_init_flag = true;
    }
}

void AppIMUModel::Update() {
    aux_bmi2_dev.delay_us(50000, aux_bmi2_dev.intf_ptr);

    /* To get the data ready interrupt status of accel, gyro and aux */
    bmi2_get_int_status(&bmi_bmm_init_status, &aux_bmi2_dev);

    /* To check the data ready interrupt status and print the status for 20
     * samples. */
    if ((bmi_bmm_init_status & BMI2_AUX_DRDY_INT_MASK)) {
        int8_t ret = bmi2_get_sensor_data(&bmi_sensor_data, &aux_bmi2_dev);

        /* Converting lsb to meter per second squared for 16 bit accelerometer
         * at 2G range. */
        accel_data.x =
            lsb_to_mps2(bmi_sensor_data.acc.x, 2, aux_bmi2_dev.resolution);
        accel_data.y =
            lsb_to_mps2(bmi_sensor_data.acc.y, 2, aux_bmi2_dev.resolution);
        accel_data.z =
            lsb_to_mps2(bmi_sensor_data.acc.z, 2, aux_bmi2_dev.resolution);

        /* Converting lsb to degree per second for 16 bit gyro at 2000dps range.
         */
        gyro_data.x =
            lsb_to_dps(bmi_sensor_data.gyr.x, 2000, aux_bmi2_dev.resolution);
        gyro_data.y =
            lsb_to_dps(bmi_sensor_data.gyr.y, 2000, aux_bmi2_dev.resolution);
        gyro_data.z =
            lsb_to_dps(bmi_sensor_data.gyr.z, 2000, aux_bmi2_dev.resolution);

        if (ret == BMI2_OK) {
            /* To read the mag data */
            bmm150_aux_raw_mag_data(bmi_sensor_data.aux_data, &bmm_mag_data,
                                    &bmm_raw_mag_data, &aux_bmm150_dev);
            mag_data.raw.x = bmm_raw_mag_data.raw_datax;
            mag_data.raw.y = bmm_raw_mag_data.raw_datay;
            mag_data.raw.z = bmm_raw_mag_data.raw_dataz;
        }
    }
}

float AppIMUModel::CalcuDir(void) {
    mag_data.x = mag_data.raw.x - mag_data.offset.x;
    mag_data.y = mag_data.raw.y - mag_data.offset.y;
    mag_data.z = mag_data.raw.z - mag_data.offset.z;

    float xyHeading = atan2(mag_data.x, mag_data.y);
    float zxHeading = atan2(mag_data.z, mag_data.x);
    float heading   = xyHeading;

    if (heading < 0) {
        heading += 2 * PI;
    }
    if (heading > 2 * PI) {
        heading -= 2 * PI;
    }
    return (heading * 180 / M_PI);
}

void AppIMUModel::MagCalibration() {
    int16_t value_x_min = 0;
    int16_t value_x_max = 0;
    int16_t value_y_min = 0;
    int16_t value_y_max = 0;
    int16_t value_z_min = 0;
    int16_t value_z_max = 0;

    Update();
    value_x_min = mag_data.raw.x;
    value_x_max = mag_data.raw.x;
    value_y_min = mag_data.raw.y;
    value_y_max = mag_data.raw.y;
    value_z_min = mag_data.raw.z;
    value_z_max = mag_data.raw.z;

    time_t start = millis();
    M5.Speaker.tone(5000, 100);
    while ((millis() - start) < 10000) {
        Update();
        if (value_x_min > mag_data.raw.x) {
            value_x_min = mag_data.raw.x;
        } else if (value_x_max < mag_data.raw.x) {
            value_x_max = mag_data.raw.x;
        }

        if (value_y_min > mag_data.raw.y) {
            value_y_min = mag_data.raw.y;
        } else if (value_y_max < mag_data.raw.y) {
            value_y_max = mag_data.raw.y;
        }

        if (value_z_min > mag_data.raw.z) {
            value_z_min = mag_data.raw.z;
        } else if (value_z_max < mag_data.raw.z) {
            value_z_max = mag_data.raw.z;
        }
        delay(100);
    }
    M5.Speaker.tone(5000, 100);

    mag_data.offset.x = value_x_min + (value_x_max - value_x_min) / 2;
    mag_data.offset.y = value_y_min + (value_y_max - value_y_min) / 2;
    mag_data.offset.z = value_z_min + (value_z_max - value_z_min) / 2;
}

bool AppIMUModel::ReadCalibration() {
    esp_err_t err = ESP_OK;

    nvs_handle_t nvs_handle;
    size_t len;

    err = nvs_open("storage", NVS_READONLY, &nvs_handle);
    if (err == ESP_OK) {
        len = sizeof(mag_data.offset);
        err = nvs_get_blob(nvs_handle, "compass", &mag_data.offset, &len);
        if (err != ESP_OK) {
            Serial.printf("Read compass calibration data failed <%s>\r\n",
                          esp_err_to_name(err));
            return err == ESP_OK ? true : false;
        }
        nvs_close(nvs_handle);
    }
    return err == ESP_OK ? true : false;
}

bool AppIMUModel::SaveCalibration() {
    esp_err_t err = ESP_OK;
    nvs_handle_t nvs_handle;

    err = nvs_open("storage", NVS_READWRITE, &nvs_handle);
    if (err == ESP_OK) {
        err = nvs_set_blob(nvs_handle, "compass", &mag_data.offset,
                           sizeof(mag_data.offset));
        if (err != ESP_OK) {
            Serial.printf("Set compass calibration data failed <%s>\r\n",
                          esp_err_to_name(err));
            return err == ESP_OK ? true : false;
        }

        err = nvs_commit(nvs_handle);
        if (err != ESP_OK) {
            Serial.printf(
                "Commit compass calibration data change failed <%s>\r\n",
                esp_err_to_name(err));
            return err == ESP_OK ? true : false;
        }
        nvs_close(nvs_handle);
    }
    return err == ESP_OK ? true : false;
}

/******************************************************************************/
int8_t AppIMUModel::bmi2_i2c_read(uint8_t reg_addr, uint8_t *reg_data,
                                  uint32_t len, void *intf_ptr) {
    if ((reg_data == NULL) || (len == 0) || (len > 32)) {
        return -1;
    }
    uint8_t dev_addr = *(uint8_t *)intf_ptr;
    M5.In_I2C.readRegister(dev_addr, reg_addr, reg_data, len, 400000L);
    return 0;
}
int8_t AppIMUModel::bmi2_i2c_write(uint8_t reg_addr, const uint8_t *reg_data,
                                   uint32_t len, void *intf_ptr) {
    if ((reg_data == NULL) || (len == 0) || (len > 32)) {
        return -1;
    }
    uint8_t dev_addr = *(uint8_t *)intf_ptr;
    M5.In_I2C.writeRegister(dev_addr, reg_addr, reg_data, len, 400000L);
    return 0;
}
void AppIMUModel::bmi2_delay_us(uint32_t period, void *intf_ptr) {
    delayMicroseconds(period);
}

int8_t AppIMUModel::aux_i2c_read(uint8_t reg_addr, uint8_t *reg_data,
                                 uint32_t length, void *intf_ptr) {
    int8_t ret;
    ret = bmi2_read_aux_man_mode(reg_addr, reg_data, length, &aux_bmi2_dev);
    return ret;
}
int8_t AppIMUModel::aux_i2c_write(uint8_t reg_addr, const uint8_t *reg_data,
                                  uint32_t length, void *intf_ptr) {
    int8_t ret;
    ret = bmi2_write_aux_man_mode(reg_addr, reg_data, length, &aux_bmi2_dev);
    return ret;
}
