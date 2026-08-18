"""
SPI TFT-LCD Test Script (MicroPython)

What it does: lights up the screen and draws "LonelyBinary" plus a set of
color bars, so you can confirm your display and wiring work. Display only
(no touch). The backlight is simple on/off (no brightness control).

Display:    2.8 inch, 240x320 pixels
Driver IC:  ST7789

Runs UNMODIFIED on both a classic ESP32 and an ESP32-S3 - the right pin set
is picked automatically at runtime from the chip the script runs on.

WHERE IS THE DRIVER? This script needs `st77xx.py` on the board.
It is NOT in this folder - the driver lives once, for all sizes, at the
ROOT of this repository:
     TFT-LCD/micropython/lib/st77xx.py
(i.e. from this folder: ../../../../micropython/lib/). Read the README.md
next to this file for the full picture.

Files to put in the board's root filesystem:
     st77xx.py   - the display driver (all drawing code)
     main.py     - this file

Setup (full steps in micropython/README.md at the repo root):
1. Flash stock MicroPython firmware (v1.20 or newer) from micropython.org
2. Copy the driver and this script onto the board:
     Thonny:   View -> Files, right-click each file -> "Upload to /"
     mpremote (from the root of this repository):
     mpremote cp micropython/lib/st77xx.py :
     mpremote cp tft-lcd/2.8inch/code/micropython/main.py :
3. Press reset - a file named main.py runs automatically at boot.
"""

import os
from machine import Pin, SPI
import st77xx

# ==================== SPI LCD Pin Definitions ====================
# 8-pin SPI LCD display pin definitions:
# 1.LEDA/BLK, 2.GND, 3.RESET, 4.DC/RS/A0, 5.SDA/MOSI, 6.SCL/SCLK, 7.VDD, 8.CS
# This kit ships wired for ESP32-S3, but the display module works with any
# board. The right pin set is chosen automatically below by looking at the
# chip this script runs on - you do NOT need to edit anything to switch boards.
#
#   Display pin        ESP32-S3      Classic ESP32   What it does
#   VDD (pin 7)        3.3V          3.3V            Power (use 3.3V, NEVER 5V)
#   GND (pin 2)        GND           GND             Ground
#   CS  (pin 8)        GPIO 10       GPIO 15         Chip select
#   RESET (pin 3)      GPIO 42       GPIO 4          Reset
#   DC/RS/A0 (pin 4)   GPIO 2        GPIO 2          Data/command (must connect!)
#   SDA/MOSI (pin 5)   GPIO 11       GPIO 23         SPI data
#   SCL/SCLK (pin 6)   GPIO 12       GPIO 18         SPI clock
#   LEDA/BLK (pin 1)   GPIO 41       GPIO 32         Backlight (on/off only)

IS_S3 = "ESP32S3" in os.uname().machine

if IS_S3:
    # ESP32-S3 - default wiring for this kit.
    # SPI(1) with sck=12 / mosi=11 is the S3's FSPI host on its native pins.
    SPI_ID = 1
    TFT_CS, TFT_RST, TFT_DC = 10, 42, 2
    TFT_MOSI, TFT_SCLK = 11, 12
    TFT_BACKLIGHT = 41
else:
    # Classic ESP32 (e.g. Lonely Binary PinPulse).
    # GPIO 41/42 don't exist here and GPIO 6-11 are used by the flash chip,
    # so the S3 pins can't be reused. SPI(2) is VSPI on its native pins.
    SPI_ID = 2
    TFT_CS, TFT_RST, TFT_DC = 15, 4, 2
    TFT_MOSI, TFT_SCLK = 23, 18
    TFT_BACKLIGHT = 32


# ==================== Display LonelyBinary and Color Bars ====================
def display_lonely_binary(tft):
    tft.fill(st77xx.BLACK)

    # Top section: "LonelyBinary" centered.
    # MicroPython's built-in font is 8 px per character (Arduino's is 6),
    # so at scale 2 the title is 12 * 8 * 2 = 192 px wide - fits 240 px.
    title = "LonelyBinary"
    scale = 2
    text_x = (tft.width - len(title) * 8 * scale) // 2
    tft.text(title, text_x, 74, st77xx.WHITE, scale=scale)

    # Middle section: 8 horizontal color bars
    colors = (st77xx.RED, st77xx.GREEN, st77xx.BLUE, st77xx.YELLOW,
              st77xx.MAGENTA, st77xx.CYAN, st77xx.WHITE, st77xx.BLACK)
    bar_start_y = 114
    bar_height = (tft.height - bar_start_y - 40) // 8  # leaves room for info
    for i, c in enumerate(colors):
        tft.fill_rect(0, bar_start_y + i * bar_height, tft.width, bar_height, c)

    # Bottom: screen information (resolution, driver, inch size)
    info_y = 274
    tft.text("240x320", 10, info_y, st77xx.WHITE)
    tft.text("ST7789", 10, info_y + 12, st77xx.WHITE)
    tft.text("2.8inch", 10, info_y + 24, st77xx.WHITE)


# ==================== Initialization ====================
print("========================================")
print("SPI LCD Test Program (MicroPython)")
print("Driver IC: ST7789")
print("Display Size: 2.8 inch")
print("Resolution: 240x320")
print("Board detected:", "ESP32-S3" if IS_S3 else "classic ESP32")
print("========================================")

# Turn the backlight on (on/off only, no brightness control). HIGH = ON.
backlight = Pin(TFT_BACKLIGHT, Pin.OUT, value=1)

# Hardware SPI. Only MOSI and SCLK are wired - the display has no MISO.
spi = SPI(SPI_ID, baudrate=40000000, polarity=0, phase=0,
          sck=Pin(TFT_SCLK), mosi=Pin(TFT_MOSI), miso=None)

print("Initializing LCD...")
tft = st77xx.ST7789(spi, 240, 320,
                    dc=Pin(TFT_DC), cs=Pin(TFT_CS), rst=Pin(TFT_RST))
print("LCD initialization complete")

# Display LonelyBinary and color bars (static display)
display_lonely_binary(tft)
print("Display ready - showing static LonelyBinary and color bars")
