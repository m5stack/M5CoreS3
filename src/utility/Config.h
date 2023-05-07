#ifndef _CONFIG_H_
#define _CONFIG_H_

#define TFT     M5Display::instance
#define BUTTONS M5Buttons::instance

// Screen
#define TFT_DC_PIN   35
#define TFT_CS_PIN   3
#define TFT_MOSI_PIN 37
#define TFT_CLK_PIN  36
#define TFT_RST_PIN  -1
#define TFT_MISO_PIN 35

// SD card
#define TFCARD_CS_PIN 4

// UART
#define USE_SERIAL USBSerial

// CoreS3 defines
#define M5Stack_M5CoreS3
#define TFT_eSPI_TOUCH_EMULATION
#define TOUCH M5Touch::instance

#endif /* CONFIG_H */
