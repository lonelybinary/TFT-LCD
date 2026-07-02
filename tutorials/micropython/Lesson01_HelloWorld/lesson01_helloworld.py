"""
Lesson 01: Hello World
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Learn how to display text on screen

Key concepts:
- Display initialization
- Backlight on/off control
- Drawing text with color, position, and size

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson01_helloworld.py
"""

import os
import time
from machine import Pin, SPI
from st77xx import ST7796, BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN

# ==================== Display setup (same in every lesson) ====================
# Pins are picked automatically from the chip this script runs on:
# ESP32-S3 gets the kit's default wiring, anything else the classic-ESP32 pins.
if "ESP32S3" in os.uname().machine:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 1, 10, 42, 2, 11, 12, 41  # ESP32-S3
else:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 2, 15, 4, 2, 23, 18, 32   # classic ESP32

print("Lesson 01: Hello World")
print("Initializing LCD...")

# Turn the backlight on (on/off only, no brightness control). HIGH = ON.
backlight = Pin(BL, Pin.OUT, value=1)

# Hardware SPI bus, then the ST7796 driver (320x480). Creating the driver
# object resets and initializes the panel - the Arduino gfx->begin() steps
# all happen in this one line.
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)

print("LCD initialized successfully!")

# ==================== Lesson Content ====================

# Clear the screen to a black background
tft.fill(BLACK)

# Draw "Hello World" in white, starting at x=50, y=200, at 3x size.
# Note: (0, 0) is the top-left corner; x grows right, y grows down.
# This one call replaces Arduino's setTextColor + setCursor + setTextSize
# + println sequence.
tft.text("Hello World", 50, 200, WHITE, scale=3)

print("Hello World displayed on screen!")
