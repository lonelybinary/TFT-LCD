# TFT-LCD

ESP32-S3 各尺寸 TFT-LCD 屏幕驱动示例代码（Arduino 版本）

使用 **Arduino GFX 官方库** 和 **Arduino 框架**开发

## 支持的屏幕尺寸

- 0.96 英寸 (160x80) - ST7735S
- 1.8 英寸 (128x160) - ST7735
- 2.0 英寸 (240x320) - ST7789
- 2.4 英寸 (240x320) - ST7789
- 2.8 英寸 (240x320) - ST7789
- 3.5 英寸 (320x480) - ST7796S/ST7365

## 硬件要求

- ESP32-S3 开发板
- SPI 接口 TFT-LCD 屏幕
- 连接线（VCC, GND, CS, DC, RST, MOSI, SCLK, BLK）

## 引脚定义

所有项目使用统一的引脚定义，**使用硬件 SPI (VSPI)**：

- CS: GPIO 10
- RST: GPIO 42
- DC: GPIO 2
- MOSI: GPIO 11 (VSPI 硬件 SPI)
- SCLK: GPIO 12 (VSPI 硬件 SPI)
- BACKLIGHT: GPIO 41

**注意：** 本项目使用硬件 SPI，速度更快、性能更稳定。MOSI 和 SCLK 必须连接到 ESP32-S3 的 VSPI 硬件 SPI 引脚。

## 开发环境

- **框架**: Arduino Framework
- **开发工具**: PlatformIO
- **库依赖**: Arduino GFX Library (moononournation/GFX Library for Arduino@1.3.9)

## 使用方法

1. 安装 PlatformIO IDE 或 VS Code + PlatformIO 插件
2. 打开对应的屏幕尺寸文件夹
3. 连接硬件并配置串口
4. 编译并上传到 ESP32-S3

## 代码说明

本项目使用 **Arduino 框架**开发，所有代码基于 Arduino API 编写：
- 使用 `Arduino.h` 头文件
- 使用标准的 `setup()` 和 `loop()` 函数结构
- 使用 Arduino GFX 库进行屏幕驱动

## 项目结构

每个屏幕尺寸文件夹包含：
- `platformio.ini` - PlatformIO 项目配置
- `src/main.cpp` - 主程序代码

## 许可证

MIT License
