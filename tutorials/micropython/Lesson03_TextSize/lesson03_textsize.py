"""
Lesson 03: Text Size
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Make text bigger or smaller

Key concepts:
- The scale= parameter of text()
- How scale affects character width and height (8 x 8 pixels times scale)
- Mixing sizes for titles and body text

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson03_textsize.py
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

print("Lesson 03: Text Size")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Lesson Content ====================

# Part 1: The same text at four different scales
print("Displaying different text sizes...")
tft.fill(BLACK)

tft.text("Size 1", 20, 20, WHITE, scale=1)
tft.text("Size 2", 20, 50, WHITE, scale=2)
tft.text("Size 3", 20, 100, WHITE, scale=3)
tft.text("Size 4", 20, 180, WHITE, scale=4)

time.sleep(3)

# Part 2: Size comparison with two colors on one line.
# Every character cell is 8 x 8 pixels times the scale, so the second
# piece of text starts at x = 20 + (6 characters) * 8 * scale.
# (Scale 4 is the largest that fits: "Size 4 ABC" is 10 chars * 32 px
# = 320 px - exactly the screen width. Arduino's font is only 6 px wide,
# which is why its version could show size 5 too.)
print("Comparing text sizes...")
tft.fill(BLACK)

y = 20
for scale in range(1, 5):
    tft.text("Size %d" % scale, 20, y, WHITE, scale=scale)
    tft.text(" ABC", 20 + 6 * 8 * scale, y, CYAN, scale=scale)
    y += scale * 8 + 5

time.sleep(3)

# Part 3: Numbers in different sizes
print("Displaying numbers in different sizes...")
tft.fill(BLACK)

tft.text("Numbers:", 50, 20, WHITE, scale=2)
tft.text("123", 50, 60, WHITE, scale=2)
tft.text("456", 50, 120, WHITE, scale=3)
tft.text("789", 50, 220, WHITE, scale=4)

time.sleep(3)

# Part 4: Mixed sizes - title, subtitle, body
print("Displaying mixed size text...")
tft.fill(BLACK)

tft.text("TITLE", 80, 30, YELLOW, scale=3)
tft.text("Subtitle", 50, 100, CYAN, scale=2)
tft.text("Body text line 1", 20, 150, WHITE, scale=1)
tft.text("Body text line 2", 20, 170, WHITE, scale=1)
tft.text("Body text line 3", 20, 190, WHITE, scale=1)

time.sleep(3)

# Part 5: Animate text size, centered each time.
# Centering formula: x = (screen width - text width) // 2,
# where text width = number of characters * 8 * scale.
print("Animating text size...")

for scale in range(1, 6):
    tft.fill(BLACK)
    text_w = 4 * 8 * scale          # "SIZE" is 4 characters
    x = (tft.width - text_w) // 2
    y = (tft.height - 8 * scale) // 2
    tft.text("SIZE", x, y, WHITE, scale=scale)
    time.sleep(1)

print("Text size demonstration complete!")
