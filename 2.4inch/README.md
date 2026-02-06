# 2.4 Inch TFT-LCD Display Driver

## Display Specifications

### Basic Information
- **Display Size**: 2.4 inch
- **Driver IC**: ST7789
- **Resolution**: 240 x 320 pixels
- **Display Type**: IPS TFT-LCD
- **Interface Type**: SPI (Serial Peripheral Interface)
- **Color Depth**: 16-bit (RGB565)
- **Viewing Angle**: IPS Full Viewing Angle

### Physical Parameters
- **Active Display Area**: 240 x 320 pixels
- **Pixel Size**: Approximately 0.20mm x 0.20mm
- **Screen Size**: Approximately 48mm x 64mm
- **Operating Voltage**: 3.3V
- **Operating Temperature**: -20°C ~ +70°C

### Display Features
- **Display Orientation**: Supports 0°, 90°, 180°, 270° rotation
- **Color Mode**: RGB565 (65,536 colors)
- **Refresh Rate**: Supports high-speed refresh
- **Backlight Control**: PWM control (Active High)

## Pin Definitions

### Display Pins (8-pin Interface)

| Pin No. | Function | ESP32-S3 Connection | Description |
|---------|----------|---------------------|-------------|
| 1 | LEDA/BLK | GPIO 41 | Backlight control (PWM) |
| 2 | GND | GND | Ground |
| 3 | RESET | GPIO 42 | Reset signal |
| 4 | DC/RS/A0 | GPIO 2 | Data/Command select (**Must connect**) |
| 5 | SDA/MOSI | GPIO 11 | SPI data output (VSPI hardware SPI) |
| 6 | SCL/SCLK | GPIO 12 | SPI clock (VSPI hardware SPI) |
| 7 | VDD | 3.3V | Power supply (**Must be 3.3V, do not connect 5V**) |
| 8 | CS | GPIO 10 | Chip select signal |

### ESP32-S3 Connection Diagram

```
Display Pin → ESP32-S3 GPIO
─────────────────────────
VDD (7)  → 3.3V
GND (2)  → GND
CS (8)   → GPIO 10
RST (3)  → GPIO 42
DC (4)   → GPIO 2  (Must connect)
MOSI (5) → GPIO 11 (VSPI hardware SPI)
SCLK (6) → GPIO 12 (VSPI hardware SPI)
BLK (1)  → GPIO 41 (Backlight control)
```

## Hardware SPI Configuration

This project uses **Hardware SPI (VSPI)** for better performance and faster speed:

- **SPI Bus**: VSPI
- **MOSI**: GPIO 11 (Fixed, VSPI hardware SPI pin)
- **SCLK**: GPIO 12 (Fixed, VSPI hardware SPI pin)
- **CS**: GPIO 10 (Customizable)
- **DC**: GPIO 2 (Customizable)
- **RST**: GPIO 42 (Customizable)

**Note**: MOSI and SCLK must be connected to ESP32-S3's VSPI hardware SPI pins and cannot be changed arbitrarily.

## Display Offset Configuration

### Current Offset Settings
- **Col Offset 1/2**: 0 (Column offset, left-right movement)
- **Row Offset 1/2**: 0 (Row offset, up-down movement)

### Offset Description
- `col offset`: Column offset (left-right movement), typically ranges from 0-5
  - Decrease value → Display content moves left
  - Increase value → Display content moves right
- `row offset`: Row offset (up-down movement), typically ranges from 0-5
  - Decrease value → Display content moves up
  - Increase value → Display content moves down
- `offset 1` is used for rotation 0/2
- `offset 2` is used for rotation 1/3

### Calibration Method
If the display position is inaccurate, you can:
1. Adjust the offset parameters in the code
2. Fine-tune according to actual display effect

## Project Structure

```
2.4inch/
├── code/
│   └── 2.4inch_Test/
│       └── 2.4inch_Test.ino  # Arduino IDE version program
└── README.md              # This file (display specifications)
```

## Usage

### Arduino IDE Version

1. **Install Arduino IDE**
   - Download and install Arduino IDE

2. **Install ESP32 Board Support**
   - File → Preferences → Add board manager URL
   - Tools → Board Manager → Search "esp32" → Install version 2.0.17

3. **Install Library**
   - Tools → Manage Libraries → Search "GFX Library for Arduino"
   - Install version 1.6.4

4. **Open Program**
   - Open `code/2.4inch_Test/2.4inch_Test.ino`
   - Select board: ESP32S3 Dev Module
   - Upload program

## Library Dependencies
- **Arduino GFX Library**: moononournation/GFX Library for Arduino@1.6.4
- **ESP32 Arduino Framework**: 2.0.17 (Required for GFX Library 1.6.4 compatibility)
  - ⚠️ **Important**: Arduino IDE version must use ESP32 Arduino framework 2.0.17
  - ⚠️ **Warning**: **Do not use ESP32 framework 3.X.X** (has compatibility issues with GFX Library 1.6.4)
  - ⚠️ **PWM API**: ESP32 2.0.17 uses `ledcSetup()` + `ledcAttachPin()`, not `ledcAttach()`

## Display Features

The program displays:
- **LonelyBinary text** - Centered at the top of the screen
- **Color bars** - 8 horizontal color bars (RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE, BLACK)
- **Screen information** - Resolution, driver IC, and screen size displayed at the bottom

## Frequently Asked Questions

### Q: Screen not lighting up?
- **Check backlight connection**: Confirm GPIO 41 connection is correct, use PWM control
- **Check power supply**: Must use 3.3V, do not connect 5V
- **Check code**: Confirm backlight control is set correctly

### Q: Display position inaccurate?
- **Adjust offset**: Modify `col offset` and `row offset` parameters in the code
- **Check initialization**: Confirm resolution is set correctly (240x320)

### Q: Screen garbled or display abnormal?
- **Check SPI connection**: Confirm MOSI, SCLK are connected to correct hardware SPI pins
- **Check power supply**: Ensure stable power supply, use 3.3V
- **Check reset**: Confirm RST pin connection is correct

### Q: Upload failed?
- **Enter download mode**: Hold BOOT button, press RESET once, release BOOT
- **Check serial port**: Confirm correct serial port is selected
### Q: Compilation error?
- **Arduino IDE version**: Ensure using GFX Library for Arduino 1.6.4 and ESP32 framework 2.0.17
- **Check board configuration**: Confirm ESP32-S3 board is selected
- **LIST_HEAD error**: This is a compatibility issue between GFX Library 1.6.4 and ESP32 framework 3.X.X, must use framework 2.0.17

## Important Notes

1. **Power Requirements**: Must use 3.3V, absolutely do not connect 5V, otherwise the display will be damaged
2. **Backlight Control**: Use PWM to control backlight brightness
3. **Hardware SPI**: MOSI and SCLK must be connected to VSPI hardware SPI pins (GPIO 11 and GPIO 12)
4. **DC Pin**: DC/RS/A0 pin must be connected, otherwise the display will not work properly
5. **Resolution**: Confirm resolution is set to 240x320

## Technical Specifications

| Item | Specification |
|------|---------------|
| Driver IC | ST7789 |
| Resolution | 240 x 320 |
| Color Depth | 16-bit (RGB565) |
| Interface | 4-wire SPI |
| Operating Voltage | 3.3V |
| SPI Speed | Hardware SPI (VSPI) |
| Display Type | IPS TFT-LCD |
| Backlight | LED backlight (PWM control) |

## License

MIT License
