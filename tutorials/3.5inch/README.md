# 3.5-inch TFT-LCD Display — Beginner Tutorial

Welcome! This tutorial takes you from a blank screen to building real interfaces on the
3.5-inch TFT-LCD display. No prior graphics experience needed — we explain everything as we go.

The same code runs on both an **ESP32-S3** and a **classic ESP32** board. You don't edit
any pins — you just pick your board in the Arduino IDE and upload.

## What you'll learn

There are **11 short lessons**, and each one builds on the last. You start with a single
line of text ("Hello World"), then add colors, text styles, and shapes. By the end you'll
combine everything to build menus, dashboards, notifications, and a clock face.

Work through them in order. Each lesson has a small, ready-to-upload sketch and a README
that explains what the code does.

## Display specifications

- **Size**: 3.5 inch
- **Resolution**: 320 × 480 pixels (portrait by default)
- **Driver chip**: ST7796
- **Panel type**: IPS TFT-LCD (wide viewing angle, accurate colors)
- **Interface**: SPI (4-wire, hardware SPI for a fast, stable picture)
- **Color depth**: 16-bit (called RGB565 — more on this in Lesson 2)

> **About the "IPS" setting:** because this panel is IPS, the sketches create the display
> with the IPS option set to `true`. You don't need to change this. If colors ever look
> inverted (red shows as blue, for example), that setting is the first thing to check.

## What you need

- An **ESP32 board** — either an **ESP32-S3** (the default) or a **classic ESP32**
  (such as the Lonely Binary PinPulse). The code works on both.
- The **3.5-inch TFT-LCD display** module.
- A few jumper wires (or the included ribbon cable + breakout board).

## How to wire it up

Connect the 8 display pins to your ESP32. **The GPIO numbers depend on which board you
have** — use the column that matches your board.

| Display pin | ESP32-S3 (default) | Classic ESP32 | What it does |
|------------|--------------------|---------------|--------------|
| VDD | 3.3V | 3.3V | Power (**use 3.3V, never 5V**) |
| GND | GND | GND | Ground |
| CS | GPIO 10 | GPIO 15 | Chip select |
| RST | GPIO 42 | GPIO 4 | Reset |
| DC | GPIO 2 | GPIO 2 | Data/command select (**must connect**) |
| MOSI / SDA | GPIO 11 | GPIO 23 | SPI data |
| SCLK / SCL | GPIO 12 | GPIO 18 | SPI clock |
| BLK / LEDA | GPIO 41 | GPIO 32 | Backlight (on/off) |

> **You don't edit the code for the pins.** Each sketch already contains both pin sets and
> picks the right one automatically based on the board you select in the Arduino IDE. The
> classic ESP32 doesn't have GPIO 41 or 42, and its GPIO 6–11 are reserved for internal
> flash memory — that's why the two boards use different pins.

**Other wiring notes:**
- Power must be **3.3V**, never 5V.
- The **DC** pin must be connected — a missing or wrong DC pin is the most common reason
  for a blank screen.
- The backlight is simple **on/off only** (no brightness/dimming). On the 3.5-inch panel,
  `HIGH` turns it on. (The 0.96-inch module is the opposite — `LOW` turns it on.)

## Software setup (Arduino IDE)

1. **Install the Arduino IDE** from [arduino.cc/en/software](https://www.arduino.cc/en/software).

2. **Add ESP32 board support.**
   - Open **Tools → Board → Boards Manager**.
   - Search for `esp32` (by Espressif Systems) and click **Install**. The latest version is fine.

3. **Install the display library.**
   - Open **Tools → Manage Libraries**.
   - Search for `GFX Library for Arduino` (by Moon On Our Nation) and click **Install**.
     The latest version is fine.

4. **Open a lesson sketch**, for example `Lesson01_HelloWorld/`.

5. **Select your board** under **Tools → Board → ESP32 Arduino**:
   - **ESP32S3 Dev Module** if you have an ESP32-S3.
   - **ESP32 Dev Module** if you have a classic ESP32 (e.g. PinPulse).

6. **Select the port** under **Tools → Port** (plug in your board first).

7. **Click Upload** (the → arrow) and watch the display.

> **Tip:** These examples work with the latest ESP32 core and GFX library. They also work
> with older versions (ESP32 core 2.0.17 + GFX 1.6.4) if that's what you already have.

## Lesson directory

### [Lesson 01: Hello World](Lesson01_HelloWorld/README.md)
**Goal**: Show your first text on the screen.
- Initialize the display and turn on the backlight
- Set text color, position, and size
- Print "Hello World"

### [Lesson 02: Colors](Lesson02_Colors/README.md)
**Goal**: Use color on the screen.
- The built-in color names
- Fill the whole screen with a color
- Set text color

### [Lesson 03: Text Size](Lesson03_TextSize/README.md)
**Goal**: Make text bigger or smaller.
- The `setTextSize()` function
- How size affects character width and height
- Mixing sizes for titles and body text

### [Lesson 04: Text Style](Lesson04_TextStyle/README.md)
**Goal**: Add background colors and highlights to text.
- Foreground and background colors
- Building label and highlight effects
- Choosing readable color combinations

### [Lesson 05: Graphics](Lesson05_Graphics/README.md)
**Goal**: Draw shapes.
- Lines, rectangles, circles, and triangles
- Outlined vs. filled shapes
- Building simple UI parts like progress bars and buttons

### [Lesson 06: Rotation](Lesson06_Rotation/README.md)
**Goal**: Turn the screen sideways.
- The `setRotation()` function
- How rotation swaps width and height
- How it changes the coordinate system

### [Lesson 07: System Info Display](Lesson07_SystemInfo/README.md)
**Goal**: Build a system-info screen.
- Reusable UI pieces (labels, progress bars, separators)
- Laying out information clearly
- Status indicators

### [Lesson 08: Menu Interface](Lesson08_Menu/README.md)
**Goal**: Build a menu.
- Storing menu items in an array
- Highlighting the selected item
- A title bar

### [Lesson 09: Data Monitoring Interface](Lesson09_DataMonitoring/README.md)
**Goal**: Build a dashboard.
- Card-style layout
- Showing data with progress bars
- Arranging multiple cards side by side

### [Lesson 10: Notification Interface](Lesson10_Notification/README.md)
**Goal**: Build a notification card.
- Card design with an icon
- Combining icons and text
- A close button

### [Lesson 11: Clock Display](Lesson11_Clock/README.md)
**Goal**: Draw an analog clock face.
- Drawing the clock circle and tick marks
- Drawing the hour and minute hands with `sin()` and `cos()`
- Showing a digital time too

## How to get the most out of this tutorial

1. **Go in order.** Each lesson assumes you've done the ones before it.
2. **Upload every sketch.** Seeing it run on real hardware is the whole point.
3. **Try the Extended Exercises.** Changing numbers and watching what happens is the
   fastest way to learn.
4. **Don't worry if something breaks.** Each lesson has an FAQ for common problems.

## Troubleshooting

**Screen stays black / nothing shows up**
- Double-check every wire, especially **DC** and **RST**.
- Make sure the backlight pin is wired and the sketch sets it (on the 3.5-inch panel,
  the backlight turns on with `HIGH`).
- Confirm power is **3.3V**, not 5V.
- Make sure you selected the matching board (ESP32S3 Dev Module vs ESP32 Dev Module).

**Upload fails / wrong port**
- Pick the correct port under **Tools → Port**.
- Some boards need you to hold **BOOT** while uploading (or hold BOOT, tap RESET, release BOOT
  to enter download mode).

**Colors look wrong (e.g. red shows as blue)**
- This panel is IPS, so the sketch creates the display with the IPS option set to `true`.
  If you changed that, set it back.
- Make sure you're using the `Arduino_ST7796` driver class.

**Code won't compile**
- Re-check that the ESP32 board package and the GFX library both installed correctly.
- Make sure the correct board is selected under **Tools → Board**.

## After you finish

Once you've completed all 11 lessons, you'll be able to:
- [ ] Initialize the display and show text
- [ ] Use colors and make your own with `color565()`
- [ ] Control text size and style
- [ ] Draw lines, rectangles, circles, and triangles
- [ ] Rotate the display
- [ ] Build a system-info screen, a menu, a dashboard, a notification, and a clock face
- [ ] Wrap common drawing code into reusable helper functions

From there, try connecting a sensor and showing live data, adding buttons for interaction,
or adapting the lessons to a different display size (each size folder has an
`ADAPTATION_GUIDE.md`).

## Helpful links

- [3.5-inch display README](../../3.5inch/README.md)
- [Arduino GFX Library on GitHub](https://github.com/moononournation/Arduino_GFX)
- [ESP32 Arduino documentation](https://docs.espressif.com/projects/arduino-esp32/)

## License

MIT License

---

**Happy building! Let's start with [Lesson 01: Hello World](Lesson01_HelloWorld/README.md). 🚀**
