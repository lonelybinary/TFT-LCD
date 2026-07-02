"""
Lesson 09: Data Monitoring Interface
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Build a dashboard

Key concepts:
- Card-style layout
- Showing data with progress bars
- Updating values in place (no flicker)

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson09_datamonitoring.py
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

print("Lesson 09: Data Monitoring Interface")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== UI helpers (from Lesson 07) ====================

def draw_label(text, x, y, bg_color, text_color, scale=2):
    text_w = len(text) * 8 * scale
    tft.fill_rect(x, y, text_w + 8, 8 * scale + 8, bg_color)
    tft.text(text, x + 4, y + 4, text_color, bg=bg_color, scale=scale)


def draw_progress_bar(x, y, width, height, percent, frame_color, fill_color):
    tft.rect(x, y, width, height, frame_color)
    fill_w = (width - 4) * percent // 100
    # paint the fill AND the empty remainder, so updates need no screen clear
    tft.fill_rect(x + 2, y + 2, fill_w, height - 4, fill_color)
    tft.fill_rect(x + 2 + fill_w, y + 2, (width - 4) - fill_w, height - 4, BLACK)


def draw_centered_text(text, y, color, scale):
    x = (tft.width - len(text) * 8 * scale) // 2
    tft.text(text, x, y, color, scale=scale)


def draw_card(x, y, title, percent, accent_color):
    """One data card: outline, title, big % value, progress bar."""
    tft.rect(x, y, 130, 100, accent_color)
    tft.text(title, x + 10, y + 10, accent_color, scale=2)
    tft.text("%3d%%" % percent, x + 10, y + 40, WHITE, scale=3)
    draw_progress_bar(x + 10, y + 70, 110, 15, percent, accent_color, GREEN)


# ==================== Lesson Content ====================

print("Displaying Data Monitoring Interface")
tft.fill(BLACK)

# Title
draw_centered_text("MONITOR", 20, WHITE, 2)
tft.hline(20, 60, tft.width - 40, GREEN)

# Two cards side by side
draw_card(25, 100, "CPU", 45, CYAN)
draw_card(165, 100, "MEM", 62, YELLOW)

# Status row
tft.text("Status:", 30, 230, WHITE, scale=2)
draw_label("OK", 160, 225, GREEN, BLACK, 2)

print("Data Monitoring Interface display complete!")

# Bonus: live updates. Redraw ONLY the value text and the bar fill -
# the card frames and titles never repaint, so there is no flicker.
print("Simulating live data for 20 seconds...")
cpu, mem = 45, 62
for tick in range(10):
    time.sleep(2)
    # fake new readings that wander up and down
    cpu = (cpu + 7) % 100
    mem = (mem + 13) % 100
    tft.text("%3d%%" % cpu, 35, 140, WHITE, bg=BLACK, scale=3)
    draw_progress_bar(35, 170, 110, 15, cpu, CYAN, GREEN)
    tft.text("%3d%%" % mem, 175, 140, WHITE, bg=BLACK, scale=3)
    draw_progress_bar(175, 170, 110, 15, mem, YELLOW, GREEN)

print("Done!")
