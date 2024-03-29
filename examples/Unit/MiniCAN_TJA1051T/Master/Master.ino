/**
 * @file Slave.ino
 * @author SeanKwok (shaoxiang@m5stack.com)
 * @brief Unit Mini CAN Test Master
 * @version 0.1
 * @date 2024-02-01
 *
 *
 * @Hardwares: M5CoreS3 + Unit Mini CAN
 * @Platform Version: Arduino M5Stack Board Manager v2.0.9
 * @Dependent Library:
 * M5GFX: https://github.com/m5stack/M5GFX
 * M5Unified: https://github.com/m5stack/M5Unified
 * M5CoreS3: https://github.com/m5stack/M5CoreS3
 */

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/semphr.h"
#include "esp_err.h"
#include "esp_log.h"
#include "driver/twai.h"
#include "esp_err.h"

#include "M5CoreS3.h"

M5Canvas canvas(&CoreS3.Display);

/* --------------------- Definitions and static variables ------------------ */

#define TX_TASK_PRIO 8  // Receiving task priority
#define TX_GPIO_NUM  gpio_num_t(9)
#define RX_GPIO_NUM  gpio_num_t(8)

static const twai_general_config_t g_config =
    TWAI_GENERAL_CONFIG_DEFAULT(TX_GPIO_NUM, RX_GPIO_NUM, TWAI_MODE_NORMAL);
static const twai_timing_config_t t_config = TWAI_TIMING_CONFIG_25KBITS();
static const twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

#define ID_SLAVE_1 0x0B1

static const twai_message_t slave_1_on = {.identifier       = ID_SLAVE_1,
                                          .data_length_code = 8,
                                          .data = {1, 2, 3, 4, 5, 6, 7, 8}};

static const twai_message_t slave_1_off = {.identifier       = ID_SLAVE_1,
                                           .data_length_code = 8,
                                           .data = {0, 0, 0, 0, 0, 0, 0, 0}};

static void twai_transmit_task(void *arg) {
    while (1) {
        twai_transmit(&slave_1_on, portMAX_DELAY);

        Serial.printf("send cmd on to 0x%02X\r\n", ID_SLAVE_1);
        Serial.print("send data: ");
        canvas.printf("send cmd on to 0x%02X\r\n", ID_SLAVE_1);
        canvas.print("send data: ");
        for (int i = 0; i < slave_1_on.data_length_code; i++) {
            Serial.printf("0x%02X ", slave_1_on.data[i]);
            canvas.printf("0x%02X ", slave_1_on.data[i]);
        }
        Serial.println();
        canvas.println("\r\n");
        canvas.pushSprite(0, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));

        twai_transmit(&slave_1_off, portMAX_DELAY);
        Serial.printf("send cmd off to 0x%02X\r\n", ID_SLAVE_1);
        Serial.print("send data: ");
        canvas.printf("send cmd off to 0x%02X\r\n", ID_SLAVE_1);
        canvas.print("send data: ");
        for (int i = 0; i < slave_1_off.data_length_code; i++) {
            Serial.printf("0x%02X ", slave_1_off.data[i]);
            canvas.printf("0x%02X ", slave_1_on.data[i]);
        }
        Serial.println();
        canvas.println("\r\n");
        canvas.pushSprite(0, 0);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    vTaskDelete(NULL);
}

void setup() {
    auto cfg = M5.config();
    CoreS3.begin(cfg);

    canvas.setColorDepth(1);  // mono color
    canvas.createSprite(CoreS3.Display.width(), CoreS3.Display.height());
    canvas.setPaletteColor(1, GREEN);
    canvas.setTextScroll(true);

    canvas.println("CAN Master");

    canvas.pushSprite(0, 0);

    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
    Serial.println("Driver installed");
    ESP_ERROR_CHECK(twai_start());
    xTaskCreatePinnedToCore(twai_transmit_task, "twai_transmit_task", 4096,
                            NULL, TX_TASK_PRIO, NULL, tskNO_AFFINITY);
}

void loop() {
}