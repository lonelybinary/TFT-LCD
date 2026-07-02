"""
Lesson 10: Notification Interface
3.5 inch TFT-LCD MicroPython Tutorial

Course objectives: Build a notification card

Key concepts:
- Card design with an icon
- Combining icons and text
- A close button

Needs st77xx.py (from micropython/lib/) copied to the board once.
Run with Thonny (F5) or:  mpremote run lesson10_notification.py
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

print("Lesson 10: Notification Interface")
backlight = Pin(BL, Pin.OUT, value=1)
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
print("LCD initialized successfully!")

# ==================== Lesson Content ====================

print("Displaying Notification Interface")
tft.fill(BLACK)

# The notification card: a white rounded-feeling panel (rectangle + border).
# Defining the geometry as variables FIRST means every element below is
# positioned relative to the card - move the card, everything follows.
card_x = 30
card_y = 80
card_w = 260
card_h = 200

tft.fill_rect(card_x, card_y, card_w, card_h, WHITE)
tft.rect(card_x, card_y, card_w, card_h, CYAN)

# Icon: a blue circle with an exclamation mark, vertically centered on
# the card's left side
icon_x = card_x + 40
icon_y = card_y + card_h // 2
tft.fill_circle(icon_x, icon_y, 25, BLUE)
tft.text("!", icon_x - 8, icon_y - 12, WHITE, bg=BLUE, scale=3)

# Notification text, to the right of the icon
text_x = card_x + 80
tft.text("New Message", text_x, card_y + 40, BLACK, bg=WHITE, scale=2)
tft.text("You have 3", text_x, card_y + 90, BLACK, bg=WHITE, scale=1)
tft.text("unread items", text_x, card_y + 110, BLACK, bg=WHITE, scale=1)

# Close button: a red square with an X, in the card's top-right corner
btn_x = card_x + card_w - 30
btn_y = card_y + 10
tft.fill_rect(btn_x, btn_y, 20, 20, RED)
tft.text("X", btn_x + 6, btn_y + 6, WHITE, bg=RED, scale=1)

print("Notification Interface display complete!")

# Bonus: dismiss the notification after 5 seconds by painting the
# background color over the card area - the "close" action.
time.sleep(5)
print("Dismissing notification...")
tft.fill_rect(card_x, card_y, card_w, card_h, BLACK)
tft.text("Notification closed", 60, 230, WHITE, scale=1)
print("Done!")
