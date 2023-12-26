#include "LTR5XX.h"

/*===========================================================================*/
/* LTR5XX Registers address*/
#define LTR5XX_ALS_CONTR_REG     0x80
#define LTR5XX_PS_CONTR_REG      0x81
#define LTR5XX_PS_LED_REG        0x82
#define LTR5XX_PS_N_PULSES_REG   0x83
#define LTR5XX_PS_MEAS_RATE_REG  0x84
#define LTR5XX_ALS_MEAS_PATE_REG 0x85

#ifdef LTR507
#define LTR5XX_ALS_DATA_0_REG        0x88
#define LTR5XX_ALS_DATA_1_REG        0x89
#define LTR5XX_ALS_PS_STATUS_REG     0x8A
#define LTR5XX_PS_DATA_LOW_REG       0x8B
#define LTR5XX_PS_DATA_HIGH_REG      0x8C
#define LTR5XX_ALS_DATA_CH1_0_REG    0x8D
#define LTR5XX_ALS_DATA_CH1_1_REG    0x8E
#define LTR5XX_ALS_DATA_CH1_2_REG    0x8F
#define LTR5XX_ALS_DATA_CH2_0_REG    0x90
#define LTR5XX_ALS_DATA_CH2_1_REG    0x91
#define LTR5XX_ALS_DATA_CH2_2_REG    0x92
#define LTR5XX_INTERRUPT_REG         0x98
#define LTR5XX_PS_THRES_UP_0_REG     0x99
#define LTR5XX_PS_THRES_UP_1_REG     0x9A
#define LTR5XX_PS_THRES_LOW_0_REG    0x9B
#define LTR5XX_PS_THRES_LOW_1_REG    0x9C
#define LTR5XX_ALS_THRES_UP_0_REG    0x9E
#define LTR5XX_ALS_THRES_UP_1_REG    0x9F
#define LTR5XX_ALS_THRES_LOW_0_REG   0xA0
#define LTR5XX_ALS_THRES_LOW_1_REG   0xA1
#define LTR5XX_INTERRUPT_PERSIST_REG 0xA4
#endif

#ifdef LTR55X
#define LTR5XX_ALS_PS_STATUS_REG     0x8C
#define LTR5XX_PS_DATA_LOW_REG       0x8D
#define LTR5XX_PS_DATA_HIGH_REG      0x8E
#define LTR5XX_ALS_DATA_CH1_0_REG    0x88
#define LTR5XX_ALS_DATA_CH1_1_REG    0x89
#define LTR5XX_ALS_DATA_CH0_0_REG    0x8A
#define LTR5XX_ALS_DATA_CH0_1_REG    0x8B
#define LTR5XX_INTERRUPT_REG         0x8F
#define LTR5XX_PS_THRES_UP_0_REG     0x90
#define LTR5XX_PS_THRES_UP_1_REG     0x91
#define LTR5XX_PS_THRES_LOW_0_REG    0x92
#define LTR5XX_PS_THRES_LOW_1_REG    0x93
#define LTR5XX_ALS_THRES_UP_0_REG    0x97
#define LTR5XX_ALS_THRES_UP_1_REG    0x98
#define LTR5XX_ALS_THRES_LOW_0_REG   0x99
#define LTR5XX_ALS_THRES_LOW_1_REG   0x9A
#define LTR5XX_INTERRUPT_PERSIST_REG 0x9E
#endif
/*===========================================================================*/

/*===========================================================================*/
/*LTR55X Registers operating parameters*/
#ifdef LTR55X
#define LTR5XX_ALS_MODE_MASK  0x01
#define LTR5XX_ALS_MODE_SHIFT 0

#define LTR5XX_ALS_GAIN_MASK  0x1C
#define LTR5XX_ALS_GAIN_SHIFT 2

#define LTR5XX_ALS_INTEGRATION_TIME_MASK  0x38
#define LTR5XX_ALS_INTEGRATION_TIME_SHIFT 3

#define LTR5XX_ALS_MEASURE_RATE_MASK  0x07
#define LTR5XX_ALS_MEASURE_RATE_SHIFT 0

#define LTR5XX_ALS_DATA_LOW_MASK  0xFF
#define LTR5XX_ALS_DATA_HIGH_MASK 0xFF

#define LTR5XX_PS_PULSES_MASK 0x0F

#define LTR5XX_PS_MEAS_RATE_MASK 0x0F

#define LTR5XX_VALID_PS_DATA_MASK  0x80
#define LTR5XX_VALID_PS_DATA_SHIFT 7
#endif

/*LTR507 Registers operating parameters*/
#ifdef LTR507
#define LTR5XX_ALS_MODE_MASK  0x02
#define LTR5XX_ALS_MODE_SHIFT 0

#define LTR5XX_ALS_GAIN_MASK  0x18
#define LTR5XX_ALS_GAIN_SHIFT 3

#define LTR5XX_ALS_ADC_BIT_WIDTH_MASK  0xE0
#define LTR5XX_ALS_ADC_BIT_WIDTH_SHIFT 5

#define LTR5XX_ALS_MEASURE_RATE_MASK  0x07
#define LTR5XX_ALS_MEASURE_RATE_SHIFT 0

#define LTR5XX_ALS_DATA_LOW_MASK  0xF0
#define LTR5XX_ALS_DATA_MID_MASK  0xFF
#define LTR5XX_ALS_DATA_HIGH_MASK 0xFF

#define LTR5XX_PS_PULSES_MASK 0xFF

#define LTR5XX_PS_MEAS_RATE_MASK 0x07

#define LTR5XX_VALID_PS_DATA_MASK  0x10
#define LTR5XX_VALID_PS_DATA_SHIFT 4
#endif

/*LTR55X and LTR507 common Registers operating parameters*/
#define LTR5XX_PS_MODE_MASK  0x02
#define LTR5XX_PS_MODE_SHIFT 1

#define LTR5XX_LED_PULSE_FREQ_MASK  0xE0
#define LTR5XX_LED_PULSE_FREQ_SHIFT 5

#define LTR5XX_LED_DUTY_CYCLE_MASK  0x18
#define LTR5XX_LED_DUTY_CYCLE_SHIFT 3

#define LTR5XX_LED_PEAK_CURRENT_MASK 0x07

#define LTR5XX_PS_DATA_LOW_MASK  0xFF
#define LTR5XX_PS_DATA_HIGH_MASK 0x07

#define LTR5XX_ALS_INTERRUPT_STATUS_MASK  0x08
#define LTR5XX_ALS_INTERRUPT_STATUS_SHIFT 3

#define LTR5XX_PS_INTERRUPT_STATUS_MASK  0x02
#define LTR5XX_PS_INTERRUPT_STATUS_SHIFT 1

#define LTR5XX_INTERRUPT_POLARITY_MASK  0x04
#define LTR5XX_INTERRUPT_POLARITY_SHIFT 2

#define LTR5XX_INTERRUPT_MODE_MASK 0x03

#define LTR5XX_PS_THRES_UP_1_MASK  0x07
#define LTR5XX_PS_THRES_LOW_1_MASK 0x07

#define LTR5XX_PS_INTERRUPT_PERSIST_MASK  0xF0
#define LTR5XX_PS_INTERRUPT_PERSIST_SHIFT 4

#define LTR5XX_ALS_INTERRUPT_PERSIST_MASK 0x0F

bool LTR5XX::ltr5xx_read(uint8_t start_reg_addr, uint8_t *pdata, uint8_t size) {
    return M5.In_I2C.readRegister(_address, start_reg_addr, pdata, size,
                                  100000L);
}

bool LTR5XX::ltr5xx_write(uint8_t start_reg_addr, uint8_t *pdata,
                          uint8_t size) {
    return M5.In_I2C.writeRegister(_address, start_reg_addr, pdata, size,
                                   100000L);
}

bool LTR5XX::ps_set_led_pulse_freq(uint8_t value) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_PS_LED_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_LED_PULSE_FREQ_MASK);
    tmp_value =
        (value << LTR5XX_LED_PULSE_FREQ_SHIFT) & LTR5XX_LED_PULSE_FREQ_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_PS_LED_REG, &write_reg, 1);
}

bool LTR5XX::ps_set_led_duty_cycle(uint8_t value) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_PS_LED_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_LED_DUTY_CYCLE_MASK);
    tmp_value =
        (value << LTR5XX_LED_DUTY_CYCLE_SHIFT) & LTR5XX_LED_DUTY_CYCLE_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_PS_LED_REG, &write_reg, 1);
}

bool LTR5XX::ps_set_led_peak_current(uint8_t value) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_PS_LED_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_LED_PEAK_CURRENT_MASK);
    tmp_value = value & LTR5XX_LED_PEAK_CURRENT_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_PS_LED_REG, &write_reg, 1);
}

bool LTR5XX::ps_set_n_pulses(uint8_t value) {
    uint8_t tmp_value;
    tmp_value = value & LTR5XX_PS_PULSES_MASK;
    return ltr5xx_write(LTR5XX_PS_N_PULSES_REG, &tmp_value, 1);
}

bool LTR5XX::ps_set_meas_rate(uint8_t value) {
    uint8_t tmp_value;
    tmp_value = value & LTR5XX_PS_MEAS_RATE_MASK;
    return ltr5xx_write(LTR5XX_PS_MEAS_RATE_REG, &tmp_value, 1);
}

bool LTR5XX::als_set_gain(uint8_t value) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_ALS_CONTR_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_ALS_GAIN_MASK);
    tmp_value = (value << LTR5XX_ALS_GAIN_SHIFT) & LTR5XX_ALS_GAIN_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_ALS_CONTR_REG, &write_reg, 1);
}

// LTR507 default integration time is 75ms,only use default values
#ifdef LTR55X
bool LTR5XX::als_set_integration_time(uint8_t value) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_ALS_MEAS_PATE_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_ALS_INTEGRATION_TIME_MASK);
    tmp_value = (value << LTR5XX_ALS_INTEGRATION_TIME_SHIFT) &
                LTR5XX_ALS_INTEGRATION_TIME_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_ALS_MEAS_PATE_REG, &write_reg, 1);
}
#endif

// LTR507 can chose als adc bit width
#ifdef LTR507
bool void LTR5XX::als_set_adc_bit_width(uint8_t value) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_ALS_MEAS_PATE_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_ALS_ADC_BIT_WIDTH_MASK);
    tmp_value = (value << LTR5XX_ALS_ADC_BIT_WIDTH_SHIFT) &
                LTR5XX_ALS_ADC_BIT_WIDTH_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_ALS_MEAS_PATE_REG, &write_reg, 1);
}
#endif

bool LTR5XX::als_set_measure_rate(uint8_t value) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_ALS_MEAS_PATE_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_ALS_MEASURE_RATE_MASK);
    tmp_value =
        (value << LTR5XX_ALS_MEASURE_RATE_SHIFT) & LTR5XX_ALS_MEASURE_RATE_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_ALS_MEAS_PATE_REG, &write_reg, 1);
}

bool LTR5XX::ltr5xx_set_interrupt_polarity(uint8_t polarity) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_INTERRUPT_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_INTERRUPT_POLARITY_MASK);
    tmp_value = (polarity << LTR5XX_INTERRUPT_POLARITY_SHIFT) &
                LTR5XX_INTERRUPT_POLARITY_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_INTERRUPT_REG, &write_reg, 1);
}

bool LTR5XX::ltr5xx_set_interrupt_mode(uint8_t mode) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_INTERRUPT_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_INTERRUPT_MODE_MASK);
    tmp_value = mode & LTR5XX_INTERRUPT_MODE_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_INTERRUPT_REG, &write_reg, 1);
}

bool LTR5XX::ps_set_threshold(uint16_t ps_upper_threshold,
                              uint16_t ps_lower_threshold) {
    uint8_t buffer[4];

    buffer[0] = ps_upper_threshold & 0xFF;  // up_reg_0
    buffer[1] =
        (ps_upper_threshold >> 8) & LTR5XX_PS_THRES_UP_1_MASK;  // up_reg_1
    buffer[2] = ps_lower_threshold & 0xFF;                      // low_reg_0
    buffer[3] =
        (ps_lower_threshold >> 8) & LTR5XX_PS_THRES_LOW_1_MASK;  // low_reg_1;

    return ltr5xx_write(LTR5XX_PS_THRES_UP_0_REG, &buffer[0], 4);
}

bool LTR5XX::als_set_threshold(uint16_t als_upper_threshold,
                               uint16_t als_lower_threshold) {
    uint8_t buffer[4];

    buffer[0] = als_upper_threshold & 0xFF;         // up_reg_0
    buffer[1] = (als_upper_threshold >> 8) & 0xFF;  // up_reg_1
    buffer[2] = als_lower_threshold & 0xFF;         // low_reg_0
    buffer[3] = (als_lower_threshold >> 8) & 0xFF;  // low_reg_1;

    return ltr5xx_write(LTR5XX_ALS_THRES_UP_0_REG, &buffer[0], 4);
}

bool LTR5XX::ltr5xx_set_n_values_outside_trigger_interrupt(
    uint8_t ps_n_values_outside_trigger, uint8_t als_n_values_outside_trigger) {
    uint8_t temp_value;

    temp_value =
        (ps_n_values_outside_trigger << LTR5XX_PS_INTERRUPT_PERSIST_SHIFT) &
        LTR5XX_PS_INTERRUPT_PERSIST_MASK;
    temp_value |=
        als_n_values_outside_trigger & LTR5XX_ALS_INTERRUPT_PERSIST_MASK;

    return ltr5xx_write(LTR5XX_INTERRUPT_PERSIST_REG, &temp_value, 1);
}

LTR5XX::LTR5XX(uint8_t sda, uint8_t scl, uint8_t address) {
    _sda     = sda;
    _scl     = scl;
    _address = address;
}

bool LTR5XX::begin(Ltr5xx_Init_Basic_Para *init_base_para) {
    return (setPsMode(LTR5XX_PS_STAND_BY_MODE) &&
            setAlsMode(LTR5XX_ALS_STAND_BY_MODE) &&
            ps_set_led_pulse_freq(init_base_para->ps_led_pulse_freq) &&
            ps_set_led_duty_cycle(init_base_para->ps_led_duty_cycle) &&
            ps_set_meas_rate(init_base_para->ps_measurement_rate) &&
            ps_set_led_peak_current(init_base_para->ps_led_peak_current) &&
            ps_set_n_pulses(init_base_para->ps_led_n_pulses) &&
            als_set_gain(init_base_para->als_gain) &&
#ifdef LTR55X
            als_set_integration_time(init_base_para->als_integration_time) &&
#endif
#ifdef LTR507
            als_set_adc_bit_width(init_base_para->als_adc_bit_width) &&
#endif

            als_set_measure_rate(init_base_para->als_measurement_rate));
}

bool LTR5XX::begin(Ltr5xx_Init_Interrupt_Para *init_interrupt_para) {
    return (ltr5xx_set_interrupt_polarity(
                init_interrupt_para->interrupt_polarity) &&
            ltr5xx_set_interrupt_mode(init_interrupt_para->interrupt_mode) &&
            ps_set_threshold(init_interrupt_para->ps_upper_threshold,
                             init_interrupt_para->ps_lower_threshold) &&
            als_set_threshold(init_interrupt_para->als_upper_threshold,
                              init_interrupt_para->als_lower_threshold) &&
            ltr5xx_set_n_values_outside_trigger_interrupt(
                init_interrupt_para->ps_n_values_outside_trigger,
                init_interrupt_para->als_n_values_outside_trigger));
}

bool LTR5XX::setPsMode(uint8_t mode) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_PS_CONTR_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_PS_MODE_MASK);
    tmp_value = (mode << LTR5XX_PS_MODE_SHIFT) & LTR5XX_PS_MODE_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_PS_CONTR_REG, &write_reg, 1);
}

uint16_t LTR5XX::getPsValue(void) {
    uint8_t buffer[2];
    uint16_t result;
    ltr5xx_read(LTR5XX_PS_DATA_LOW_REG, &buffer[0], 2);
    buffer[0] &= LTR5XX_PS_DATA_LOW_MASK;
    buffer[1] &= LTR5XX_PS_DATA_HIGH_MASK;
    result = (buffer[1] << 8) | buffer[0];
    return result;
}

bool LTR5XX::setAlsMode(uint8_t mode) {
    uint8_t read_reg, write_reg, tmp_value;
    ltr5xx_read(LTR5XX_ALS_CONTR_REG, &read_reg, 1);
    read_reg &= (~LTR5XX_ALS_MODE_MASK);
    tmp_value = (mode << LTR5XX_ALS_MODE_SHIFT) & LTR5XX_ALS_MODE_MASK;
    write_reg = read_reg | tmp_value;
    return ltr5xx_write(LTR5XX_ALS_CONTR_REG, &write_reg, 1);
}

uint16_t LTR5XX::getAlsValue() {
    uint8_t buffer[4];
    uint16_t result;

#ifdef LTR507
    ltr5xx_read(LTR5XX_ALS_DATA_0_REG, &buffer[0], 2);
    result = (buffer[1] << 8) | buffer[0];
#endif

#ifdef LTR55X
    uint16_t ch1_value, ch0_value;
    ltr5xx_read(LTR5XX_ALS_DATA_CH1_0_REG, &buffer[0], 4);
    ch1_value = (buffer[1] << 8) | buffer[0];
    ch0_value = (buffer[3] << 8) | buffer[2];
    result    = (ch1_value + ch0_value) >> 1;
#endif
    return result;
}

uint8_t LTR5XX::getPsIRQ() {
    uint8_t read_reg, int_status;
    ltr5xx_read(LTR5XX_ALS_PS_STATUS_REG, &read_reg, 1);
    int_status = (read_reg & LTR5XX_PS_INTERRUPT_STATUS_MASK) >>
                 LTR5XX_PS_INTERRUPT_STATUS_SHIFT;
    return int_status;
}

uint8_t LTR5XX::getAlsIRQ() {
    uint8_t read_reg, int_status;
    ltr5xx_read(LTR5XX_ALS_PS_STATUS_REG, &read_reg, 1);
    int_status = (read_reg & LTR5XX_ALS_INTERRUPT_STATUS_MASK) >>
                 LTR5XX_ALS_INTERRUPT_STATUS_SHIFT;
    return int_status;
}