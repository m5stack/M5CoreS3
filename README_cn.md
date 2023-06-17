# CoreS3 Library

中文 | [English](README_cn.md)

<img src="https://static-cdn.m5stack.com/resource/docs/products/core/CoreS3/img-96063e2a-637a-4d11-ac47-1ce4f1cdfd3e.webp" width="350" height="350">

* **如果查看 CoreS3 的详细介绍文档，[点击这里](https://docs.m5stack.com/zh_CN/core/CoreS3)**

## 描述

`CoreS3`是M5Stack开发套件系列的第三代主机，其核心主控采用`ESP32-S3`方案，`双核Xtensa LX7`处理器，主频`240MHz`，自带`WiFi`功能，板载`16MFLASH`和`8M-PSRAM`；可通过`TYPE-C`接口`下载程序`，支持`OTG和CDC`功能，方便外接usb设备和烧录固件；正面搭载一块`2.0寸电容触摸IPS屏`，面板采用`高强度玻璃材质`；屏幕下方内置一个`30w像素的摄像头GC0308`，附带`接近传感器LTR-553ALS-WA`；电源部分采用`AXP2101电源管理芯`片及`4路电源流向控制回路`，整体采用`低功耗`设计；板载`六轴姿态传感器BMI270和磁力计BMM150`；板载`TF-card（microSD）`卡槽；板载BM8563 `RTC`芯片，提供精确计时及`休眠-定时唤醒`功能；声音输出方面采用高保真`16bits-I2S`功放芯片AW88298，机身内置`1w扬声器`；声音输入方面采用ES7210`音频解码芯片+双麦克风输入`；在机身侧边配有`独立电源按键与重启（RST）按键`，自建延时电路，`长按复位键便可进入程序下载模式`。CoreS3套装默认附带`DinBase底座`，方便实现`Din导轨、挂墙以及螺丝固定`；可外部`DC 12V（支持9~24V）`或者内部`500mAh锂电池`供电；DinBase预留多处`proto`的位置，方便用户`DIY`。本成品适用于`物联网开发、各种DIY项目开发、智能家居控制系统和工业自动化控制系统`等场景。

## 产品特性

- 基于 ESP32 开发,支持WiFi @16M Flash,8M PSRAM
- 内置摄像头、接近传感器、扬声器,电源指示灯,RTC,I2S功放,双麦克风,电容式触摸屏幕,电源键,复位按键,陀螺仪
- TF卡插槽
- 高强度玻璃材质
- 支持OTG和CDC功能
- 采用AXP2101电源管理，低功耗设计
- 支持编程平台：Arduino、UIFlow

## PlatformIO 编译

[编译文件](https://github.com/m5stack/M5CoreS3/blob/main/platformio.ini)

## M5CoreS3 M-BUS示意图

<img src="https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/products/core/CoreS3/S3.jpg" width = "35%">

## 原理图

<img alt="schematics" src="https://static-cdn.m5stack.com/resource/docs/products/core/CoreS3/img-513d30d4-3378-44b9-9d75-4f3f3ac6fb1f.png" width="100%" />

- [完整原理图pdf](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/core/K128%20CoreS3/Sch_M5_CoreS3_v1.0.pdf)

<!-- ## 更多信息

**Arduino IDE 环境搭建**: [点击这里](https://docs.m5stack.com/zh_CN/quick_start/cores3/arduino) -->
