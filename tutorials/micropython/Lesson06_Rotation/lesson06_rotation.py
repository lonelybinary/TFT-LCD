"""
Lesson 06: Rotation
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Turn the screen sideways

Key concepts:
- The set_rotation() method
- How rotation swaps tft.width and tft.height
- How it changes the coordinate system

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson06_rotation.py
"""

import os
import time
from machine import Pin, SPI
from st77xx import ST7796, BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN

# ==================== Display setup (same in every lesson) ====================
if "ESP32S3" in os.uname().machine:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 1, 10, 42, 2, 11, 12, 41  # ESP32-S3
else:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 2, 15, 4, 2, 23, 18, 32   # classic ESP32

print("Lesson 06: Rotation")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Lesson Content ====================

# Part 1: Visit all four rotations and draw the coordinate system
print("Displaying all rotation angles...")

for rotation in range(4):
    tft.set_rotation(rotation)
    tft.fill(BLACK)

    # Rotation number and the screen size in this orientation.
    # tft.width / tft.height swap when the screen turns sideways!
    tft.text("Rot: %d" % rotation, 50, 50, WHITE, scale=3)
    tft.text("W: %d H: %d" % (tft.width, tft.height), 50, 120, WHITE, scale=2)

    # Draw the axes through the center
    center_x = tft.width // 2
    center_y = tft.height // 2
    tft.line(0, center_y, tft.width - 1, center_y, RED)      # X axis
    tft.text("X", tft.width - 40, center_y - 30, RED, scale=2)
    tft.line(center_x, 0, center_x, tft.height - 1, GREEN)   # Y axis
    tft.text("Y", center_x + 10, 20, GREEN, scale=2)

    # Origin marker - (0,0) is always the current top-left corner
    tft.fill_circle(0, 0, 5, YELLOW)
    tft.text("(0,0)", 10, 10, YELLOW, scale=1)

    # Corner markers
    tft.fill_circle(0, 0, 3, CYAN)
    tft.fill_circle(tft.width - 1, 0, 3, CYAN)
    tft.fill_circle(0, tft.height - 1, 3, CYAN)
    tft.fill_circle(tft.width - 1, tft.height - 1, 3, CYAN)

    time.sleep(3)

# Part 2: The same centered content at each rotation
print("Displaying same content at different rotations...")

for rotation in range(4):
    tft.set_rotation(rotation)
    tft.fill(BLACK)

    # Center "TEST" using the CURRENT width/height
    text_w = 4 * 8 * 4                     # "TEST", scale 4
    x = (tft.width - text_w) // 2
    y = (tft.height - 32) // 2
    tft.text("TEST", x, y, WHITE, scale=4)

    tft.text("Rotation: %d" % rotation, 20, 20, CYAN, scale=2)
    time.sleep(3)

# Part 3: Graphics at each rotation
print("Showing graphics at different rotations...")

for rotation in range(4):
    tft.set_rotation(rotation)
    tft.fill(BLACK)

    center_x = tft.width // 2
    center_y = tft.height // 2

    tft.rect(center_x - 60, center_y - 40, 120, 80, RED)
    tft.circle(center_x, center_y, 50, GREEN)
    tft.line(center_x, center_y, center_x + 60, center_y - 60, BLUE)

    tft.text("Rot: %d" % rotation, 20, 20, WHITE, scale=2)
    time.sleep(3)

# Part 4: Rotation reference card
print("Rotation angle reference...")
tft.set_rotation(0)  # restore the default
tft.fill(BLACK)

tft.text("Rotation:", 50, 50, WHITE, scale=2)
tft.text("0 = 0 deg", 50, 100, WHITE, scale=2)
tft.text("1 = 90 deg", 50, 150, WHITE, scale=2)
tft.text("2 = 180 deg", 50, 200, WHITE, scale=2)
tft.text("3 = 270 deg", 50, 250, WHITE, scale=2)

print("Rotation demonstration complete!")
