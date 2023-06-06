#ifndef __CONFIG_H
#define __CONFIG_H

#define DEMO_VERSION "0.4"

#define GC0308_ADDR  0x21
#define LTR553_ADDR  0x23
#define AXP2101_ADDR 0x34
#define AW88298_ADDR 0x36
#define FT6336_ADDR  0x38
#define ES7210_ADDR  0x40
#define BM8563_ADDR  0x51
#define AW9523_ADDR  0x58
#define BMI270_ADDR  0x69
#define BMM150_ADDR  0x10

#define SYS_I2C_PORT 0
#define SYS_I2C_SDA  12
#define SYS_I2C_SCL  11

#define EXT_I2C_PORT 0

#define PORTA_PIN_0  1
#define PORTA_PIN_1  2
#define PORTB_PIN_0  8
#define PORTB_PIN_1  9
#define PORTC_PIN_0  18
#define PORTC_PIN_1  17

#define POWER_MODE_USB_IN_BUS_IN 0
#define POWER_MODE_USB_IN_BUS_OUT 1
#define POWER_MODE_USB_OUT_BUS_IN 2
#define POWER_MODE_USB_OUT_BUS_OUT 3

#define MIC_BUF_SIZE 256

#define MONKEY_TEST_ENABLE 0

#endif  // __CONFIG_H