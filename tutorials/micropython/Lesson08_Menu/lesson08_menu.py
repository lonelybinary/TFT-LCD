"""
Lesson 08: Menu Interface
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Build a menu

Key concepts:
- Storing menu items in a list
- Highlighting the selected item
- A title bar

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson08_menu.py
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

print("Lesson 08: Menu Interface")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")


def draw_centered_text(text, y, color, scale, bg=None):
    x = (tft.width - len(text) * 8 * scale) // 2
    if bg is None:
        tft.text(text, x, y, color, scale=scale)
    else:
        tft.text(text, x, y, color, bg=bg, scale=scale)


# ==================== Lesson Content ====================

# The menu is data, the drawing is a loop. Changing the menu means
# changing the list - not the drawing code. That separation is the lesson.
MENU_ITEMS = ("Settings", "Data", "About", "Exit")
ITEM_COLORS = (WHITE, CYAN, YELLOW, RED)
selected = 0  # index of the highlighted item

print("Displaying Menu Interface")
tft.fill(BLACK)

# Title bar: a filled strip with a centered title
tft.fill_rect(0, 0, tft.width, 50, BLUE)
draw_centered_text("MENU", 15, WHITE, 2, bg=BLUE)

# Menu items
y = 70
for i, item in enumerate(MENU_ITEMS):
    if i == selected:
        # Highlight bar behind the selected item, dark text on top
        tft.fill_rect(20, y - 5, 280, 50, CYAN)
        tft.text("> " + item, 40, y + 5, BLACK, bg=CYAN, scale=2)
    else:
        tft.text("> " + item, 40, y + 5, ITEM_COLORS[i], scale=2)
    y += 60

print("Menu Interface display complete!")

# Bonus: move the highlight down one item every 2 seconds, using the
# erase-and-redraw idea from Lesson 5 (only the two changed rows repaint).
def draw_item(i, highlighted):
    y = 70 + i * 60
    if highlighted:
        tft.fill_rect(20, y - 5, 280, 50, CYAN)
        tft.text("> " + MENU_ITEMS[i], 40, y + 5, BLACK, bg=CYAN, scale=2)
    else:
        tft.fill_rect(20, y - 5, 280, 50, BLACK)
        tft.text("> " + MENU_ITEMS[i], 40, y + 5, ITEM_COLORS[i], scale=2)


print("Animating the selection...")
for step in range(1, 8):
    old = selected
    selected = step % len(MENU_ITEMS)
    time.sleep(2)
    draw_item(old, False)
    draw_item(selected, True)

print("Done!")
