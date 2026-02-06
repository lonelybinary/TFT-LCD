# 3.5-inch TFT-LCD Display Basic Tutorial

Welcome to the basic tutorial for the 3.5-inch TFT-LCD display! This tutorial will take you from zero to learn how to use this large display.

## Tutorial Introduction

This tutorial contains 11 progressive lessons, starting from the most basic "Hello World", gradually learning core functions such as text display, color usage, graphics drawing, and finally integrating all knowledge through practical application cases.

## Display Specifications

- **Display Size**: 3.5 inch
- **Resolution**: 320 x 480 pixels (portrait native)
- **Driver IC**: ST7796 (compatible with ST7365)
- **Display Mode**: IPS TFT-LCD (IPS display)
- **Interface**: SPI (4-wire)
- **Color Depth**: 16-bit (RGB565)

**Important Notes**:
- According to the specification, this is an IPS display, so the IPS parameter in code is set to `true`
- `Arduino_ST7796` class can drive ST7796 chip
- Backlight uses PWM control (different from 0.96-inch Active Low control)
- If color display is incorrect, check IPS parameter settings

## Hardware Requirements

### Required Hardware
- ESP32-S3 development board
- 3.5-inch TFT-LCD display
- Dupont wires (for connections)

### Pin Connections

| Display Pin | ESP32-S3 GPIO | Description |
|------------|--------------|-------------|
| VDD (7) | 3.3V | Power supply (**Must be 3.3V**) |
| GND (2) | GND | Ground |
| CS (8) | GPIO 10 | Chip select |
| RST (3) | GPIO 42 | Reset |
| DC (4) | GPIO 2 | Data/Command select (**Must connect**) |
| MOSI (5) | GPIO 11 | SPI data (VSPI hardware SPI) |
| SCLK (6) | GPIO 12 | SPI clock (VSPI hardware SPI) |
| BLK (1) | GPIO 41 | Backlight control (PWM) |

**Important Notes**:
- Must use 3.3V power supply, cannot connect 5V
- DC pin must be connected
- MOSI and SCLK must connect to VSPI hardware SPI pins
- Backlight uses PWM control, need to configure PWM channel

## Software Requirements

### Arduino IDE
- **Arduino IDE**: Latest version
- **ESP32 Arduino Framework**: 2.0.17 (required)
- **Arduino GFX Library**: 1.6.4

**Installation Steps**:
1. Install Arduino IDE
2. Add ESP32 board support (framework version 2.0.17)
3. Install library: Tools → Manage Libraries → Search "GFX Library for Arduino" → Install version 1.6.4

**Important Warning**:
- ⚠️ **Do not use ESP32 framework 3.X.X** (compatibility issues with GFX Library 1.6.4)
- ⚠️ **Must use framework 2.0.17**

## Tutorial Directory

### [Lesson 01: Hello World](Lesson01_HelloWorld/README.md)
**Learning Objectives**: Display first text
- Display initialization
- PWM backlight control
- Basic text display
- Set text color and position

### [Lesson 02: Colors](Lesson02_Colors/README.md)
**Learning Objectives**: Learn color usage
- Predefined colors
- Fill screen color
- Set text color

### [Lesson 03: Text Size](Lesson03_TextSize/README.md)
**Learning Objectives**: Control text size
- setTextSize() function
- Effects of different sizes
- Size impact on layout

### [Lesson 04: Text Style](Lesson04_TextStyle/README.md)
**Learning Objectives**: Text style settings
- Foreground and background colors
- Create label effects
- Text highlighting

### [Lesson 05: Graphics](Lesson05_Graphics/README.md)
**Learning Objectives**: Draw basic graphics
- Line drawing
- Rectangles and circles
- Create UI elements

### [Lesson 06: Rotation](Lesson06_Rotation/README.md)
**Learning Objectives**: Screen rotation
- setRotation() function
- Different rotation angles
- Rotation impact on coordinates

### [Lesson 07: System Info Display](Lesson07_SystemInfo/README.md)
**Learning Objectives**: Create system information display interface
- UI component design (labels, progress bars, separators)
- Information layout and hierarchy
- Status indicator design

### [Lesson 08: Menu Interface](Lesson08_Menu/README.md)
**Learning Objectives**: Create menu interface
- Menu item layout
- Highlight current option
- Title bar design

### [Lesson 09: Data Monitoring Interface](Lesson09_DataMonitoring/README.md)
**Learning Objectives**: Create data monitoring interface
- Card-style layout design
- Data visualization (progress bars)
- Multi-card arrangement

### [Lesson 10: Notification Interface](Lesson10_Notification/README.md)
**Learning Objectives**: Create notification interface
- Notification card design
- Icon and text combination
- Close button design

### [Lesson 11: Clock Display](Lesson11_Clock/README.md)
**Learning Objectives**: Create clock display interface
- Analog clock drawing
- Clock mark drawing
- Hour and minute hand drawing
- Digital time display

## Learning Paths

### Beginner Path
1. Start from Lesson 01, learn in order
2. Practice hands-on for each lesson
3. Complete extended exercises
4. Check FAQ section when encountering problems

### Quick Start Path
If you're already familiar with Arduino and displays:
1. Lesson 01: Understand initialization
2. Lesson 02: Master color usage
3. Lesson 05: Learn graphics drawing
4. Lesson 07-11: View practical application cases

### Advanced Learning Path
After completing basic tutorial:
- Try creating your own applications
- Combine with sensor data
- Add user interactions
- Optimize performance

## Usage Instructions

### How to Start

1. **Prepare Hardware**
   - Connect display and ESP32-S3 according to pin connection table
   - Check all connections are correct
   - Confirm power supply is 3.3V

2. **Configure Software**
   - Install Arduino IDE
   - Install ESP32 framework 2.0.17
   - Install GFX Library 1.6.4

3. **Start Learning**
   - Open first lesson's code file
   - Upload to ESP32-S3
   - Observe display effects
   - Read README to understand key concepts

### Code File Description

Each lesson contains:
- **`.ino` file**: Arduino IDE code
- **`README.md`**: Lesson documentation

### Learning Suggestions

1. **Progressive**: Learn in order, don't skip lessons
2. **Hands-on Practice**: Upload code to verify for each lesson
3. **Understand Principles**: Don't just copy code, understand why
4. **Try Modifications**: Modify parameters to observe effect changes
5. **Complete Exercises**: Extended exercises for each lesson are valuable

## Frequently Asked Questions

### Hardware Issues

**Q: Display not lighting up?**
- Check backlight connection (GPIO 41)
- 3.5-inch display uses PWM control for backlight, need to configure PWM correctly
- Check if power supply is 3.3V

**Q: Display garbled or abnormal?**
- Check SPI connections (MOSI, SCLK)
- Confirm DC pin is connected
- Check power supply stability

**Q: Upload failed?**
- Enter download mode: Hold BOOT, press RESET, release BOOT
- Check serial port selection
- Reduce upload speed

### Software Issues

**Q: Compilation error?**
- Confirm ESP32 framework version is 2.0.17
- Confirm GFX Library version is 1.6.4
- Check board selection (ESP32S3 Dev Module)

**Q: LIST_HEAD error?**
- This is a framework version incompatibility issue
- Must use ESP32 framework 2.0.17, cannot use 3.X.X

**Q: Code runs but display shows nothing?**
- Check serial output for errors
- Confirm display initialization succeeded
- Check backlight PWM configuration is correct

**Q: Color display incorrect?**
- **Check IPS parameter**: According to specification, 3.5-inch display is IPS, IPS parameter should be set to `true`
- If color display is abnormal, try checking IPS parameter settings
- Confirm using `Arduino_ST7796` class

**Q: Backlight control method?**
- 3.5-inch display uses PWM control for backlight (different from 0.96-inch Active Low)
- Need to use `ledcSetup()`, `ledcAttachPin()`, and `ledcWrite()` functions
- Brightness range: 0-255 (0=darkest, 255=brightest)

## Technical Support

### Reference Resources
- [3.5-inch Display Main README](../../3.5inch/README.md)
- [Arduino GFX Library Documentation](https://github.com/moononournation/Arduino_GFX)
- [ESP32 Arduino Documentation](https://docs.espressif.com/projects/arduino-esp32/)

### Get Help
- Check FAQ section of each lesson
- Check code comments
- Refer to example code

## Course Completion Checklist

After completing all courses, you should be able to:
- [ ] Initialize display and display text
- [ ] Use various colors and create custom colors
- [ ] Set text size and style
- [ ] Draw lines, rectangles, circles, and other graphics
- [ ] Rotate display orientation
- [ ] Create system information display interface
- [ ] Create menu interface
- [ ] Create data monitoring interface
- [ ] Create notification interface
- [ ] Create clock display interface
- [ ] Encapsulate common functions

## Next Steps

After completing this tutorial, you can:
1. Create your own application projects
2. Combine with sensors to display real-time data
3. Add interactive functions like buttons
4. Optimize interface and performance
5. Learn tutorials for other display sizes

## License

MIT License

---

**Happy Learning! Start your display programming journey!** 🚀
