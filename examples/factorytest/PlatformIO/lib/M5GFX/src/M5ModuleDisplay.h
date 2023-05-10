#ifndef __M5GFX_M5MODULEDISPLAY__
#define __M5GFX_M5MODULEDISPLAY__

// If you want to use a set of functions to handle SD/SPIFFS/HTTP,
//  please include <SD.h>,<SPIFFS.h>,<HTTPClient.h> before <M5GFX.h>
// #include <SD.h>
// #include <SPIFFS.h>
// #include <HTTPClient.h>

#include "lgfx/v1/panel/Panel_M5HDMI.hpp"
#include "M5GFX.h"

#include <sdkconfig.h>
#include <soc/efuse_reg.h>

#ifndef M5MODULEDISPLAY_LOGICAL_WIDTH
#define M5MODULEDISPLAY_LOGICAL_WIDTH 1280
#endif
#ifndef M5MODULEDISPLAY_LOGICAL_HEIGHT
#define M5MODULEDISPLAY_LOGICAL_HEIGHT 720
#endif
#ifndef M5MODULEDISPLAY_REFRESH_RATE
#define M5MODULEDISPLAY_REFRESH_RATE 0.0f
#endif
#ifndef M5MODULEDISPLAY_OUTPUT_WIDTH
#define M5MODULEDISPLAY_OUTPUT_WIDTH 0
#endif
#ifndef M5MODULEDISPLAY_OUTPUT_HEIGHT
#define M5MODULEDISPLAY_OUTPUT_HEIGHT 0
#endif
#ifndef M5MODULEDISPLAY_SCALE_W
#define M5MODULEDISPLAY_SCALE_W 0
#endif
#ifndef M5MODULEDISPLAY_SCALE_H
#define M5MODULEDISPLAY_SCALE_H 0
#endif
#ifndef M5MODULEDISPLAY_PIXELCLOCK
#define M5MODULEDISPLAY_PIXELCLOCK 74250000
#endif

#if __has_include(<esp_idf_version.h>)
 #include <esp_idf_version.h>
 #if ESP_IDF_VERSION >= ESP_IDF_VERSION_VAL(4, 3, 0)
  #define M5MODULEDISPLAY_SPI_DMA_CH SPI_DMA_CH_AUTO
 #endif
#endif

class M5ModuleDisplay : public M5GFX
{
  lgfx::Panel_M5HDMI::config_resolution_t _cfg_reso;

public:

  struct config_t
  {
    uint16_t logical_width  = M5MODULEDISPLAY_LOGICAL_WIDTH;
    uint16_t logical_height = M5MODULEDISPLAY_LOGICAL_HEIGHT;
    float refresh_rate      = M5MODULEDISPLAY_REFRESH_RATE;
    uint16_t output_width   = M5MODULEDISPLAY_OUTPUT_WIDTH;
    uint16_t output_height  = M5MODULEDISPLAY_OUTPUT_HEIGHT;
    uint_fast8_t scale_w    = M5MODULEDISPLAY_SCALE_W;
    uint_fast8_t scale_h    = M5MODULEDISPLAY_SCALE_H;
    uint32_t pixel_clock    = M5MODULEDISPLAY_PIXELCLOCK;
  };

  config_t config(void) const { return config_t(); }

  M5ModuleDisplay( const config_t& cfg )
  {
    _board = lgfx::board_t::board_M5ModuleDisplay;
    _cfg_reso.logical_width  = cfg.logical_width;
    _cfg_reso.logical_height = cfg.logical_height;
    _cfg_reso.refresh_rate   = cfg.refresh_rate;
    _cfg_reso.output_width   = cfg.output_width;
    _cfg_reso.output_height  = cfg.output_height;
    _cfg_reso.scale_w        = cfg.scale_w;
    _cfg_reso.scale_h        = cfg.scale_h;
    _cfg_reso.pixel_clock    = cfg.pixel_clock;
  }

  M5ModuleDisplay( uint16_t logical_width  = M5MODULEDISPLAY_LOGICAL_WIDTH
                 , uint16_t logical_height = M5MODULEDISPLAY_LOGICAL_HEIGHT
                 , float refresh_rate      = M5MODULEDISPLAY_REFRESH_RATE
                 , uint16_t output_width   = M5MODULEDISPLAY_OUTPUT_WIDTH
                 , uint16_t output_height  = M5MODULEDISPLAY_OUTPUT_HEIGHT
                 , uint_fast8_t scale_w    = M5MODULEDISPLAY_SCALE_W
                 , uint_fast8_t scale_h    = M5MODULEDISPLAY_SCALE_H
                 , uint32_t pixel_clock    = M5MODULEDISPLAY_PIXELCLOCK
                 )
  {
    _board = lgfx::board_t::board_M5ModuleDisplay;
    _cfg_reso.logical_width  = logical_width;
    _cfg_reso.logical_height = logical_height;
    _cfg_reso.refresh_rate   = refresh_rate;
    _cfg_reso.output_width   = output_width;
    _cfg_reso.output_height  = output_height;
    _cfg_reso.scale_w        = scale_w;
    _cfg_reso.scale_h        = scale_h;
    _cfg_reso.pixel_clock    = pixel_clock;
  }

  bool init_impl(bool use_reset, bool use_clear)
  {
    if (_panel_last.get() != nullptr) {
      return true;
    }
    auto p = new lgfx::Panel_M5HDMI();
    if (!p) {
      return false;
    }

#if defined (CONFIG_IDF_TARGET_ESP32S3)
 #define M5GFX_SPI_HOST SPI2_HOST

    // for CoreS3
    int i2c_port = 1;
    int i2c_sda  = GPIO_NUM_12;
    int i2c_scl  = GPIO_NUM_11;
    int spi_cs   = GPIO_NUM_7;
    int spi_mosi = GPIO_NUM_37;
    int spi_miso = GPIO_NUM_35;
    int spi_sclk = GPIO_NUM_36;

#elif !defined (CONFIG_IDF_TARGET) || defined (CONFIG_IDF_TARGET_ESP32)
 #define M5GFX_SPI_HOST VSPI_HOST

    int i2c_port = 1;
    int i2c_sda  = GPIO_NUM_21;
    int i2c_scl  = GPIO_NUM_22;
    int spi_cs   = GPIO_NUM_19;
    int spi_miso = GPIO_NUM_38;
    int spi_mosi = GPIO_NUM_23;
    int spi_sclk = GPIO_NUM_18;

    if (0x03 == m5gfx::i2c::readRegister8(1, 0x34, 0x03, 400000))
    { // M5Stack Core2 / Tough
#if defined ( ESP_LOGD )
      ESP_LOGD("LGFX","ModuleDisplay with Core2/Tough");
#endif
    }
    else
    { // M5Stack BASIC / FIRE / GO
#if defined ( ESP_LOGD )
      ESP_LOGD("LGFX","ModuleDisplay with Core Basic/Fire/Go");
#endif
      i2c_port =  0;
      spi_cs   = GPIO_NUM_13;
      spi_miso = GPIO_NUM_19;
    }
#endif

#if defined M5GFX_SPI_HOST

// AtomDisplay/ModuleDisplay自己機種判定のための暫定措置
    // m5gfx::pinMode(GPIO_NUM_0, m5gfx::pin_mode_t::output);
    // m5gfx::gpio_lo(GPIO_NUM_0);

    auto bus_spi = new lgfx::Bus_SPI();
    {
      auto cfg = bus_spi->config();
      cfg.freq_write = 80000000;
      cfg.freq_read  = 16000000;
      cfg.spi_mode = 3;
      cfg.spi_host = M5GFX_SPI_HOST;
#undef M5GFX_SPI_HOST
#ifndef M5MODULEDISPLAY_SPI_DMA_CH
      cfg.dma_channel = 1;
#else
      cfg.dma_channel = M5MODULEDISPLAY_SPI_DMA_CH;
#endif
      cfg.use_lock = true;
      cfg.pin_mosi = spi_mosi;
      cfg.pin_miso = spi_miso;
      cfg.pin_sclk = spi_sclk;
      cfg.spi_3wire = false;

      bus_spi->config(cfg);
      p->setBus(bus_spi);
    }

    {
      auto cfg = p->config_transmitter();
      cfg.freq_read = 400000;
      cfg.freq_write = 400000;
      cfg.pin_scl = i2c_scl;
      cfg.pin_sda = i2c_sda;
      cfg.i2c_port = i2c_port;
      cfg.i2c_addr = 0x39;
      cfg.prefix_cmd = 0x00;
      cfg.prefix_data = 0x00;
      cfg.prefix_len = 0;
      p->config_transmitter(cfg);
    }

    {
      auto cfg = p->config();
      cfg.offset_rotation = 3;
      cfg.pin_cs     = spi_cs;
      cfg.readable   = false;
      cfg.bus_shared = true;
      p->config(cfg);
      p->setRotation(1);
    }
    p->config_resolution(_cfg_reso);
    setPanel(p);
    if (lgfx::LGFX_Device::init_impl(use_reset, use_clear))
    {
      _panel_last.reset(p);
      _bus_last.reset(bus_spi);
      return true;
    }
    setPanel(nullptr);
    delete p;
    delete bus_spi;

#endif

    return false;
  }
};

#endif
