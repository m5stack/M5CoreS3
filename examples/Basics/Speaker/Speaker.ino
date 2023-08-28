#include <Arduino.h>
#include <Wire.h>
#include <driver/i2c.h>
#include <driver/i2s.h>
#include "driver/gpio.h"
#include "esp_system.h"
#include "esp_log.h"
#include <math.h>
#include <stdio.h>

#define LITTLETOBIG(x)          ((x<<8)|(x>>8))

#define SAMPLE_RATE     (36000)
#define I2S_NUM         (I2S_NUM_0)
#define WAVE_FREQ_HZ    (100)
// #define PI              (3.14159265)
#define I2S_BCK_IO      (GPIO_NUM_34)
#define I2S_WS_IO       (GPIO_NUM_33)
#define I2S_DO_IO       (GPIO_NUM_13)
#define I2S_DI_IO       (GPIO_NUM_14)

#define SAMPLE_PER_CYCLE (SAMPLE_RATE/WAVE_FREQ_HZ)

extern "C" void aw88298_init(void);
extern "C" int aw88298_i2c_write_16(uint8_t slv_addr, uint8_t reg, uint16_t data);
extern "C" void setup_triangle_sine_waves(int bits);
void speaker_test(void);

void setup(void) 
{
    Serial.begin(115200);
    Wire.begin(12, 11, 100000L);
    aw88298_init();

    speaker_test();
}

void loop(void) 
{
    
}

extern "C" int aw88298_i2c_write_16(uint8_t slv_addr, uint8_t reg, uint16_t data)
{
    esp_err_t ret = ESP_FAIL;
    uint16_t data_htons = LITTLETOBIG(data);
    uint8_t *data_u8 = (uint8_t *)&data_htons;
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, ( slv_addr << 1 ) | I2C_MASTER_WRITE, 0x01);
    i2c_master_write_byte(cmd, reg, 0x01);
    i2c_master_write_byte(cmd, data_u8[0], 0x01);
    i2c_master_write_byte(cmd, data_u8[1], 0x01);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);
    if(ret != ESP_OK) {
        ESP_LOGI(TAG, "W [%04x]=%04x fail\n", reg, data);
    }
    return ret == ESP_OK ? 0 : -1;
}

extern "C" void aw88298_init(void) 
{
    aw88298_i2c_write_16(0x36, 0x61, 0x0673);
    aw88298_i2c_write_16(0x36, 0x04, 0x4040);
    aw88298_i2c_write_16(0x36, 0x05, 0x0008);
    aw88298_i2c_write_16(0x36, 0x06, 0x14C8);
    aw88298_i2c_write_16(0x36, 0x0C, 0x0064);
}

extern "C" void setup_triangle_sine_waves(int bits)
{
    int *samples_data = (int*) malloc(((bits+8)/16)*SAMPLE_PER_CYCLE*4);
    unsigned int i, sample_val;
    double sin_float, triangle_float, triangle_step = (double) pow(2, bits) / SAMPLE_PER_CYCLE;
    size_t i2s_bytes_write = 0;

    printf("\r\nTest bits=%d free mem=%d, written data=%d\n", bits, esp_get_free_heap_size(), ((bits+8)/16)*SAMPLE_PER_CYCLE*4);

    triangle_float = -(pow(2, bits)/2 - 1);

    for(i = 0; i < SAMPLE_PER_CYCLE; i++) {
        sin_float = sin(i * 2 * PI / SAMPLE_PER_CYCLE);
        if(sin_float >= 0)
            triangle_float += triangle_step;
        else
            triangle_float -= triangle_step;

        sin_float *= (pow(2, bits)/2 - 1);

        if (bits == 16) {
            sample_val = 0;
            sample_val += (short)triangle_float;
            sample_val = sample_val << 16;
            sample_val += (short) sin_float;
            samples_data[i] = sample_val;
        } else if (bits == 24) { //1-bytes unused
            samples_data[i*2] = ((int) triangle_float) << 8;
            samples_data[i*2 + 1] = ((int) sin_float) << 8;
        } else {
            samples_data[i*2] = ((int) triangle_float);
            samples_data[i*2 + 1] = ((int) sin_float);
        }

    }
    ESP_LOGI(TAG, "set clock");
    i2s_set_clk(I2S_NUM, SAMPLE_RATE, bits, I2S_CHANNEL_MONO);
    //Using push
    // for(i = 0; i < SAMPLE_PER_CYCLE; i++) {
    //     if (bits == 16)
    //         i2s_push_sample(0, &samples_data[i], 100);
    //     else
    //         i2s_push_sample(0, &samples_data[i*2], 100);
    // }
    // or write
    ESP_LOGI(TAG, "write data");
    i2s_write(I2S_NUM, samples_data, ((bits+8)/16)*SAMPLE_PER_CYCLE*4, &i2s_bytes_write, 100);

    free(samples_data);
}

void speaker_test(void)
{
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_MSB,
        .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
        .dma_buf_count = 6,
        .dma_buf_len = 60,
        .use_apll = false                                //Interrupt level 1
    };

    i2s_pin_config_t pin_config = {
        .mck_io_num = I2S_PIN_NO_CHANGE,
        .bck_io_num = I2S_BCK_IO,
        .ws_io_num = I2S_WS_IO,
        .data_out_num = I2S_DO_IO,
        .data_in_num = I2S_DI_IO                                               //Not used
    };

    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);

    int test_bits = 16;
    while (1) {
        setup_triangle_sine_waves(test_bits);
        vTaskDelay(5000/portTICK_RATE_MS);
        test_bits += 8;
        if(test_bits > 32)
            test_bits = 16;

    }
}
