"""
Lesson 02: Colors
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Learn to use color on the screen

Key concepts:
- The built-in color names
- Filling the whole screen with a color
- Coloring text
- Making your own colors with color565()

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson02_colors.py
"""

import os
import time
from machine import Pin, SPI
import st77xx
from st77xx import ST7796, BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN

# ==================== Display setup (same in every lesson) ====================
if "ESP32S3" in os.uname().machine:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 1, 10, 42, 2, 11, 12, 41  # ESP32-S3
else:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 2, 15, 4, 2, 23, 18, 32   # classic ESP32

print("Lesson 02: Colors")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Lesson Content ====================

# Part 1: Fill the screen with each predefined color
print("Displaying predefined colors...")

for name, color in (("RED", RED), ("GREEN", GREEN), ("BLUE", BLUE),
                    ("YELLOW", YELLOW), ("MAGENTA", MAGENTA), ("CYAN", CYAN),
                    ("WHITE", WHITE), ("BLACK", BLACK)):
    print("  " + name)
    tft.fill(color)
    time.sleep(2)

# Part 2: Show each color's name, written in that color
print("Displaying color names...")
tft.fill(BLACK)

y = 20
for name, color in (("RED", RED), ("GREEN", GREEN), ("BLUE", BLUE),
                    ("YELLOW", YELLOW), ("MAGENTA", MAGENTA), ("CYAN", CYAN),
                    ("WHITE", WHITE)):
    tft.text(name, 50, y, color, scale=2)
    y += 40

# Part 3: Make your own color with color565(red, green, blue).
# Each channel is 0-255, like a web color. The display stores colors in
# 16 bits (RGB565), and color565() does the packing for you.
orange = st77xx.color565(255, 140, 0)
gray = st77xx.color565(128, 128, 128)
tft.text("ORANGE", 50, y, orange, scale=2)
tft.text("GRAY", 50, y + 40, gray, scale=2)

print("Color demonstration complete!")
