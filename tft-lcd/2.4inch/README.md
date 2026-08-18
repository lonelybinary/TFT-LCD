# 2.4 Inch TFT-LCD Display

A 2.4-inch IPS color display for your ESP32 projects. This page covers the specs and wiring for this size. For full setup steps, see the [main README](../README.md).

## Photos

**Front**
![2.4 inch front](./images/2.4front.png)

**Back**
![2.4 inch back](./images/2.4back.png)

## The basics

- **Driver chip:** ST7789
- **Resolution:** 240 × 320 pixels
- **Colors:** 16-bit (65,536 colors)
- **Connection:** SPI (a fast, simple way to talk to the screen)
- **Power:** 3.3V only (never 5V)
- **Touch:** no — this is a display-only module
- **Panel type:** IPS (great viewing angles)
- **Screen size:** about 48mm × 64mm

## How to wire it up

These are the 8 wires between the display and your board. **Which GPIO numbers to use depends on your board** — pick the column that matches the board you have.

| Display pin | ESP32-S3 (default) | Classic ESP32 | What it does |
|-------------|--------------------|---------------|--------------|
| VCC / VDD | 3.3V | 3.3V | Power (use 3.3V, **never 5V**) |
| GND | GND | GND | Ground |
| CS | GPIO 10 | GPIO 15 | Chip select |
| RST | GPIO 42 | GPIO 4 | Reset |
| DC | GPIO 2 | GPIO 2 | Data/command select |
| MOSI / SDA | GPIO 11 | GPIO 23 | SPI data |
| SCLK / SCL | GPIO 12 | GPIO 18 | SPI clock |
| BLK / LEDA | GPIO 41 | GPIO 32 | Backlight |

**You don't edit the code to switch boards.** The sketch already contains both pin sets and picks the right one automatically based on the board you select in the Arduino IDE (`#if defined(CONFIG_IDF_TARGET_ESP32S3)`). Just choose **ESP32S3 Dev Module** for an ESP32-S3, or **ESP32 Dev Module** for a classic ESP32 (such as the Lonely Binary PinPulse).

> **Why are the pin numbers different?** The classic ESP32 doesn't have GPIO 41 or 42, and its GPIO 6–11 are reserved for internal flash memory — so the ESP32-S3 pins can't be reused. The classic ESP32 column uses its standard hardware-SPI pins instead.

The backlight is simple on/off only (no brightness control). On this size, `HIGH` turns it on.

## Adjusting the picture position (offset)

This size ships with both the column and row offset at **0**, so the picture should already sit correctly. If it ever looks slightly shifted, you can nudge the `col offset` / `row offset` values near the top of the sketch (lower to move left/up, higher to move right/down). Different batches can vary slightly.

## Try it out

1. Open `code/2.4inch_Test/2.4inch_Test.ino` in the Arduino IDE.
2. Select your board (**ESP32S3 Dev Module** or **ESP32 Dev Module**) and the right port.
3. Click Upload.

The test sketch shows the LonelyBinary name, eight color bars, and the screen details at the bottom — a quick way to confirm everything works.

New here? The full step-by-step setup (installing the IDE, the ESP32 boards, and the display library) lives in the [main README](../README.md). Ready to write your own code? Work through the beginner lessons in [`tutorials/3.5inch/`](../tutorials/3.5inch/README.md), and use this size's `ADAPTATION_GUIDE.md` to adjust them for the 2.4-inch screen.

## Library versions

The examples were tested with the **latest** Arduino ESP32 core and the **latest** GFX Library for Arduino, and they also work with the older ESP32 core 2.0.17 + GFX 1.6.4. Use whichever versions you have — they all work. (The sketch has a tiny color-compatibility helper so it builds on old and new GFX versions; you never need to touch it.)

## If something isn't working

**Screen stays black**
- Re-check every wire, especially **DC** and **RST**.
- Make sure power is **3.3V**, not 5V.
- Confirm you picked the matching board (ESP32S3 Dev Module vs ESP32 Dev Module).

**Picture looks shifted**
- Adjust the `col offset` / `row offset` values as described above.

**Upload fails**
- Pick the correct port under **Tools → Port**. Some boards need you to hold **BOOT** while uploading.

## License

MIT License
