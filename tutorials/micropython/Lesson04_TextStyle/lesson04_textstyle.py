"""
Lesson 04: Text Style
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Add background colors and highlights to text

Key concepts:
- Foreground and background colors (the bg= parameter)
- Building label and highlight effects with fill_rect + text
- Choosing readable color combinations

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson04_textstyle.py
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

print("Lesson 04: Text Style")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Lesson Content ====================

# Part 1: Foreground color only (background stays black)
print("Displaying text with foreground color only...")
tft.fill(BLACK)

tft.text("White text", 50, 30, WHITE, scale=2)
tft.text("Red text", 50, 70, RED, scale=2)
tft.text("Green text", 50, 110, GREEN, scale=2)
tft.text("Blue text", 50, 150, BLUE, scale=2)
tft.text("Yellow text", 50, 190, YELLOW, scale=2)

time.sleep(3)

# Part 2: Foreground AND background color.
# The bg= parameter paints the character cells' background - the same as
# Arduino's two-argument setTextColor(fg, bg).
print("Displaying text with foreground and background colors...")
tft.fill(BLACK)

tft.text("White on Red", 50, 30, WHITE, bg=RED, scale=2)
tft.text("Black on Yellow", 50, 80, BLACK, bg=YELLOW, scale=2)
tft.text("White on Blue", 50, 130, WHITE, bg=BLUE, scale=2)
tft.text("Red on White", 50, 180, RED, bg=WHITE, scale=2)

time.sleep(3)

# Part 3: Color combinations - contrast matters for readability
print("Displaying different color combinations...")
tft.fill(BLACK)

tft.text("High Contrast", 50, 30, WHITE, bg=BLACK, scale=2)
tft.text("Inverted", 50, 80, BLACK, bg=WHITE, scale=2)
tft.text("Cyan/Magenta", 50, 130, CYAN, bg=MAGENTA, scale=2)
tft.text("Yellow/Blue", 50, 180, YELLOW, bg=BLUE, scale=2)

time.sleep(3)

# Part 4: Background areas bigger than the text.
# bg= only covers the character cells. For padding around the text,
# draw a filled rectangle first, then the text on top of it.
print("Displaying text with background areas...")
tft.fill(BLACK)

# Method 1: bg= (background exactly the size of the text)
tft.text("Method 1", 50, 30, WHITE, bg=RED, scale=2)

# Method 2: rectangle first, then text - padding all around
tft.fill_rect(20, 100, 180, 30, GREEN)
tft.text("Method 2", 50, 107, BLACK, bg=GREEN, scale=2)

# Method 3: a wider banner
tft.fill_rect(20, 160, 230, 30, BLUE)
tft.text("Method 3", 50, 167, WHITE, bg=BLUE, scale=2)

time.sleep(3)

# Part 5: Label effects - the building block of every status UI
print("Creating label effects...")
tft.fill(BLACK)

for y, label_text, bg_color, fg_color in (
        (50, "SUCCESS", GREEN, BLACK),
        (100, "WARNING", YELLOW, BLACK),
        (150, "ERROR", RED, WHITE),
        (200, "INFO", BLUE, WHITE)):
    tft.fill_rect(50, y, 130, 35, bg_color)
    tft.text(label_text, 60, y + 10, fg_color, bg=bg_color, scale=2)

time.sleep(3)

# Part 6: Highlight one line among normal lines
print("Creating text highlight effects...")
tft.fill(BLACK)

tft.text("Normal Text", 50, 50, WHITE, scale=2)
tft.fill_rect(0, 100, 320, 40, CYAN)
tft.text("Highlighted Line", 50, 112, BLACK, bg=CYAN, scale=2)
tft.text("Normal Text", 50, 160, WHITE, scale=2)

print("Text style demonstration complete!")
