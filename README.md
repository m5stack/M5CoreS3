# M5CoreS3 Library

[![Arduino Compile](https://github.com/m5stack/M5CoreS3/actions/workflows/arduino-action-cores3-compile.yml/badge.svg)](https://github.com/m5stack/M5CoreS3/actions/workflows/arduino-action-cores3-compile.yml)
[![Arduino Lint](https://github.com/m5stack/M5CoreS3/actions/workflows/Arduino-Lint-Check.yml/badge.svg)](https://github.com/m5stack/M5CoreS3/actions/workflows/Arduino-Lint-Check.yml)
[![Clang Format](https://github.com/m5stack/M5CoreS3/actions/workflows/clang-format-check.yml/badge.svg)](https://github.com/m5stack/M5CoreS3/actions/workflows/clang-format-check.yml)


English | [中文](README_cn.md)

<img src="https://static-cdn.m5stack.com/resource/docs/products/core/CoreS3/img-96063e2a-637a-4d11-ac47-1ce4f1cdfd3e.webp" alt="M5CoreS3" width="350" height="350">

* **For the Detailed documentation of CoreS3, please [Click here](https://docs.m5stack.com/en/core/CoreS3)**

## Depend Libraries:

  - [M5GFX](https://github.com/m5stack/m5gfx)
  - [M5Unified](https://github.com/m5stack/M5unified)

## Description

`CoreS3` is the third generation of the M5Stack development kit series, its core master adopts the `ESP32-S3` solution, `dual-core Xtensa LX7` processor, the main frequency is`240MHz`, comes with '`WiFi`function, and the onboard `16MFLASH`and `8M-PSRAM`; It can `download the program`through the `TYPE-C` interface, support `OTG and CDC`functions, and facilitate external USB devices and flashing firmware; The front is equipped with a `2.0-inch capacitive touch IPS screen`, and the panel is made of `high-strength glass material`; A `30w pixel camera GC0308` is built into the bottom of the screen, with `proximity sensor LTR-553ALS-WA`; The power supply part adopts `AXP2101 power management core`chip and `4-way power flow control loop`, and the overall adopts `low power consumption` design; On-board `6-axis attitude sensor BMI270 and magnetometer BMM150`; On-board `TF-card (microSD)` card slot; On-board BM8563 `RTC` chip, providing accurate timing and `sleep-timer wake-up` function; In terms of sound output, it adopts high-fidelity `16bits-I2S` power amplifier chip AW88298, and the fuselage has a built-in `1w speaker`; In terms of sound input, ES7210 `audio decoding chip + dual microphone input` is adopted; On the side of the fuselage, there is a `independent power button and restart (RST) button`, self-built delay circuit, `long press the reset button to enter the program download mode`. The CoreS3 set comes with a `DinBase Base` by default, which is convenient for `Din rail, wall and screw fixing`; It can be powered by external `DC 12V (support 9~24V)` or internal `500mAh lithium battery`; DinBase reserves multiple `proto` locations for users to `DIY`. This finished product is suitable for scenarios such as `Internet of Things development, various DIY project development, smart home control system and industrial automation control system`.

**Power on and off operation:**<br>Power on: Click the left power button<br>shut down: Long press the left power button for 6 seconds <br>reset: Click the bottom RST button


## Features

- Developed based on ESP32, support WiFi @16M Flash, 8M PSRAM
- Built-in camera, proximity sensor, speaker, power indicator, RTC, I2S amplifier, dual microphone, condenser touch screen, power button, reset button, gyroscope
- TF card slot
- High-strength glass
- Support OTG and CDC functions
- AXP2101 power management, low power design
- Supported programming platforms: Arduino, UIFlow

## PlatformIO Compilation

[Compilation File](https://github.com/m5stack/M5CoreS3/blob/main/platformio.ini)

## M5CoreS3 M-BUS Schematic diagram

<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/products/core/CoreS3/S3.jpg" width = "35%">

## Schematic

<img alt="schematics" src="https://static-cdn.m5stack.com/resource/docs/products/core/CoreS3/img-513d30d4-3378-44b9-9d75-4f3f3ac6fb1f.png" width="100%" />


- [Complete schematic pdf](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/K128%20CoreS3/Sch_M5_CoreS3_v1.0.pdf)


## More Information

**Arduino IDE Development**: [Click Here](https://docs.m5stack.com/en/quick_start/cores3/arduino)