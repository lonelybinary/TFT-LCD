"""
Lesson 05: Graphics
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Draw shapes

Key concepts:
- Lines, rectangles, circles, and triangles
- Outlined vs. filled shapes
- Building simple UI parts like progress bars
- Smooth animation: redraw only what changed

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson05_graphics.py
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

print("Lesson 05: Graphics")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Lesson Content ====================

# Part 1: Lines - line(x0, y0, x1, y1, color)
print("Drawing lines...")
tft.fill(BLACK)

tft.line(20, 20, 300, 20, WHITE)    # horizontal
tft.line(20, 20, 20, 460, RED)      # vertical
tft.line(20, 20, 300, 460, GREEN)   # diagonal
tft.line(300, 20, 20, 460, BLUE)    # the other diagonal

time.sleep(2)

# Part 2: Rectangle outlines - rect(x, y, width, height, color)
print("Drawing rectangles (outline)...")
tft.fill(BLACK)

tft.rect(20, 20, 80, 60, RED)
tft.rect(120, 20, 100, 80, GREEN)
tft.rect(20, 120, 150, 100, BLUE)

time.sleep(2)

# Part 3: Filled rectangles - fill_rect(...)
print("Drawing filled rectangles...")
tft.fill(BLACK)

tft.fill_rect(20, 20, 80, 60, RED)
tft.fill_rect(120, 20, 100, 80, GREEN)
tft.fill_rect(20, 120, 150, 100, BLUE)

time.sleep(2)

# Part 4: Circle outlines - circle(center_x, center_y, radius, color)
print("Drawing circles (outline)...")
tft.fill(BLACK)

tft.circle(80, 100, 30, RED)
tft.circle(160, 100, 50, GREEN)
tft.circle(240, 100, 70, BLUE)

time.sleep(2)

# Part 5: Filled circles - fill_circle(...)
print("Drawing filled circles...")
tft.fill(BLACK)

tft.fill_circle(80, 200, 30, RED)
tft.fill_circle(160, 200, 50, GREEN)
tft.fill_circle(240, 200, 70, BLUE)

time.sleep(2)

# Part 6: Combining shapes into simple icons
print("Creating simple icons...")
tft.fill(BLACK)

# Play button (triangle), stop button (square), record button (circle)
tft.fill_triangle(50, 100, 50, 200, 150, 150, GREEN)
tft.fill_rect(180, 100, 80, 80, RED)
tft.fill_circle(280, 150, 39, BLUE)

time.sleep(2)

# Part 7: A grid, drawn with two loops
print("Drawing grid...")
tft.fill(BLACK)

for x in range(0, 320, 40):
    tft.line(x, 0, x, 479, CYAN)
for y in range(0, 480, 40):
    tft.line(0, y, 319, y, CYAN)

time.sleep(2)

# Part 8: A progress bar - an outline plus a partial fill
print("Drawing progress bar...")
tft.fill(BLACK)

tft.text("Progress: 50%", 50, 100, WHITE, scale=2)
tft.rect(20, 200, 280, 40, WHITE)         # frame
tft.fill_rect(20, 200, 140, 40, GREEN)    # 50% of 280 wide

time.sleep(2)

# Part 9: Animation. The trick on a pure-Python driver: DON'T clear the
# whole screen every frame (that redraws 153,600 pixels). Erase just the
# old shape by drawing over it in the background color, then draw the new
# one. Only ~2% of the pixels change per frame, so it's fast and flicker-free.
print("Animating graphics...")
tft.fill(BLACK)

# Moving circle
old_x = None
for x in range(40, 280, 10):
    if old_x is not None:
        tft.fill_circle(old_x, 240, 30, BLACK)   # erase previous position
    tft.fill_circle(x, 240, 30, YELLOW)
    old_x = x
    time.sleep(0.1)

# Growing rectangle: it only grows, so just draw the new strip each frame
tft.fill(BLACK)
for w in range(20, 300, 10):
    tft.fill_rect(10, 200, w, 80, CYAN)
    time.sleep(0.05)

print("Graphics demonstration complete!")
