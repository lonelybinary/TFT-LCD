"""
Lesson 07: System Info Display
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Build a system-info screen

Key concepts:
- Wrapping drawing code into reusable Python functions
- Labels, progress bars, separators, centered titles
- Status indicators

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson07_systeminfo.py
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

print("Lesson 07: System Info Display")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Reusable UI helpers ====================
# From here on, we stop drawing everything by hand and build a small
# toolbox of functions. Every remaining lesson reuses this idea.

def draw_label(text, x, y, bg_color, text_color, scale=2):
    """A padded, colored label like [ONLINE]."""
    text_w = len(text) * 8 * scale
    text_h = 8 * scale
    tft.fill_rect(x, y, text_w + 8, text_h + 8, bg_color)
    tft.text(text, x + 4, y + 4, text_color, bg=bg_color, scale=scale)


def draw_progress_bar(x, y, width, height, percent, frame_color, fill_color):
    """A progress bar: outline frame + partial fill."""
    tft.rect(x, y, width, height, frame_color)
    fill_w = (width - 4) * percent // 100
    if fill_w > 0:
        tft.fill_rect(x + 2, y + 2, fill_w, height - 4, fill_color)


def draw_centered_text(text, y, color, scale):
    """Text horizontally centered on the current screen width."""
    x = (tft.width - len(text) * 8 * scale) // 2
    tft.text(text, x, y, color, scale=scale)


def draw_separator(y, color):
    """A horizontal rule with a 20 px margin on each side."""
    tft.hline(20, y, tft.width - 40, color)


# ==================== Lesson Content ====================

print("Displaying System Info Interface")
tft.fill(BLACK)

# Title and separator
draw_centered_text("SYSTEM INFO", 20, YELLOW, 2)
draw_separator(60, CYAN)

# Status row: plain text + a green label
tft.text("Status:", 30, 100, WHITE, scale=2)
draw_label("ONLINE", 170, 95, GREEN, BLACK, 2)

# Temperature row: mixed colors on one line
tft.text("Temp:", 30, 160, WHITE, scale=2)
tft.text("25.5", 130, 160, CYAN, scale=2)
tft.text("C", 200, 160, WHITE, scale=2)

# Battery row: a progress bar at 75%
tft.text("Battery:", 30, 220, WHITE, scale=2)
draw_progress_bar(180, 220, 120, 20, 75, WHITE, GREEN)

# Signal row: four bars of growing height, the last one gray (off)
tft.text("Signal:", 30, 280, WHITE, scale=2)
gray = st77xx.color565(128, 128, 128)
for i in range(4):
    bar_h = (i + 1) * 8
    color = GREEN if i < 3 else gray
    tft.fill_rect(170 + i * 14, 280 + (32 - bar_h), 10, bar_h, color)

print("System Info Display complete!")
