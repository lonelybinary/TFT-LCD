"""
Lesson 11: Clock Display
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Draw an analog clock face

Key concepts:
- Drawing the clock circle and tick marks
- Placing the hands with math.sin() and math.cos()
- Showing a digital time too
- (Bonus) making it tick with erase-and-redraw

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson11_clock.py
"""

import os
import math
import time
from machine import Pin, SPI
from st77xx import ST7796, BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN

# ==================== Display setup (same in every lesson) ====================
if "ESP32S3" in os.uname().machine:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 1, 10, 42, 2, 11, 12, 41  # ESP32-S3
else:
    SPI_ID, CS, RST, DC, MOSI, SCLK, BL = 2, 15, 4, 2, 23, 18, 32   # classic ESP32

print("Lesson 11: Clock Display")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Lesson Content ====================

CENTER_X = 160   # screen center: 320 / 2
CENTER_Y = 240   # screen center: 480 / 2
RADIUS = 100     # clock radius, keeps the face on screen


def hand_end(angle_deg, length):
    """Convert 'clock angle' (0 deg = 12 o'clock, clockwise) to x, y.

    math.sin/cos work in radians measured from the positive x axis, so we
    shift by -90 degrees to make 0 point straight up.
    """
    a = math.radians(angle_deg - 90)
    return (CENTER_X + int(length * math.cos(a)),
            CENTER_Y + int(length * math.sin(a)))


def draw_face():
    """The parts that never change: circle, ticks, digital time slot."""
    tft.circle(CENTER_X, CENTER_Y, RADIUS, WHITE)
    # 12 tick marks, one every 30 degrees
    for i in range(12):
        outer = hand_end(i * 30, RADIUS - 5)
        inner = hand_end(i * 30, RADIUS - 20)
        tft.line(outer[0], outer[1], inner[0], inner[1], WHITE)


def draw_hands(hour, minute, color_hour=RED, color_min=GREEN):
    # Hour hand: 360 deg / 12 h = 30 deg per hour, plus a bit for minutes
    hx, hy = hand_end(hour % 12 * 30 + minute // 2, 45)
    tft.line(CENTER_X, CENTER_Y, hx, hy, color_hour)
    # Minute hand: 360 deg / 60 min = 6 deg per minute
    mx, my = hand_end(minute * 6, 70)
    tft.line(CENTER_X, CENTER_Y, mx, my, color_min)
    # Center dot on top
    tft.fill_circle(CENTER_X, CENTER_Y, 5, WHITE)


def draw_digital(hour, minute):
    text = "%02d:%02d" % (hour, minute)
    x = (tft.width - len(text) * 8 * 3) // 2
    tft.text(text, x, 380, WHITE, bg=BLACK, scale=3)


print("Displaying Clock Interface")
tft.fill(BLACK)

draw_face()
draw_hands(3, 0)      # 3 o'clock, like the Arduino lesson
draw_digital(3, 0)

print("Clock Display complete!")

# Bonus: make it tick. Advance one minute per second (a fast-forward demo).
# Erase the old hands by redrawing them in black, then draw the new ones -
# the face and ticks are never repainted.
print("Fast-forward ticking for 30 seconds...")
hour, minute = 3, 0
for _ in range(30):
    time.sleep(1)
    draw_hands(hour, minute, BLACK, BLACK)      # erase old hands
    minute += 1
    if minute == 60:
        minute = 0
        hour = (hour + 1) % 12
    draw_face()                                  # restore any tick we clipped
    draw_hands(hour, minute)
    draw_digital(hour, minute)

print("Done! Try wiring this to machine.RTC() for real time.")
