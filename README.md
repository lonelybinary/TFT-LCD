# TFT-LCD

ESP32-S3 Multi-size TFT-LCD Display Driver Example Code (Using Arduino GFX Official Library)

## Supported Display Sizes

- 0.96 inch (160x80) - ST7735S
- 1.8 inch (128x160) - ST7735S
- 2.0 inch (240x320) - ST7789
- 2.4 inch (240x320) - ST7789
- 2.8 inch (240x320) - ST7789
- 3.5 inch (320x480) - ST7796S/ST7365

## Hardware Requirements

- ESP32-S3 development board
- SPI interface TFT-LCD display
- Connection wires (VCC, GND, CS, DC, RST, MOSI, SCLK, BLK)

## Pin Definitions

All projects use unified pin definitions with **Hardware SPI (VSPI)**:

- CS: GPIO 10
- RST: GPIO 42
- DC: GPIO 2
- MOSI: GPIO 11 (VSPI hardware SPI)
- SCLK: GPIO 12 (VSPI hardware SPI)
- BACKLIGHT: GPIO 41

**Note:** This project uses hardware SPI for faster speed and more stable performance. MOSI and SCLK must be connected to ESP32-S3's VSPI hardware SPI pins.

## Usage

### Arduino IDE Version

1. Install Arduino IDE
2. Install ESP32 Arduino framework **2.0.17** (required)
   - Tools → Board → Board Manager → Search "esp32" → Install version 2.0.17
   - ⚠️ **Do not use ESP32 framework 3.X.X** (has compatibility issues with GFX Library 1.6.4)
3. Install GFX Library for Arduino **1.6.4**
   - Tools → Manage Libraries → Search "GFX Library for Arduino" → Install version 1.6.4
4. Open the `.ino` file in `code/{size}_Test/` folder
5. Select board: ESP32S3 Dev Module
6. Upload program

## Library Dependencies
- **Arduino GFX Library**: moononournation/GFX Library for Arduino@1.6.4
- **ESP32 Arduino Framework**: 2.0.17 (Required for GFX Library 1.6.4 compatibility)
  - ⚠️ **Important**: ESP32 Arduino framework 2.0.17 is required for Arduino IDE version
  - ⚠️ **Warning**: **Do not use ESP32 framework 3.X.X** with GFX Library 1.6.4 (compatibility issues)
  - ⚠️ **PWM API**: ESP32 2.0.17 uses `ledcSetup()` + `ledcAttachPin()`, not `ledcAttach()`

## Project Structure

Each display size folder contains:
- `README.md` / `README_CN.md` - Display specifications (English/Chinese)
- `code/` - Arduino IDE version
  - `{size}_Test/{size}_Test.ino` / `{size}_Test_CN.txt` - Arduino IDE main program (English/Chinese)

## License

MIT License
