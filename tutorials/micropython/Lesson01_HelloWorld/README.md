# Lesson 01: Hello World

## Course Objectives

Show your very first text on the 3.5-inch TFT-LCD screen — the "hello world" of displays.
Once this works, you know your wiring, firmware, and driver are all correct.

## Key Concepts

### 1. Initializing the display

Three things happen before you can draw:

```python
# Turn on the backlight (on/off only - no dimming). HIGH = ON on this panel.
backlight = Pin(BL, Pin.OUT, value=1)

# Open the SPI bus the display is wired to
spi = SPI(SPI_ID, baudrate=40000000, sck=Pin(SCLK), mosi=Pin(MOSI), miso=None)

# Create the driver - this also resets and initializes the panel
tft = ST7796(spi, 320, 480, dc=Pin(DC), cs=Pin(CS), rst=Pin(RST), bgr=True)
```

You don't need to know the GPIO numbers by heart — the `if "ESP32S3" ...` block at the
top picks the right pin set for your board automatically. That's the MicroPython
equivalent of choosing your board in the Arduino IDE.

### 2. Drawing text

```python
tft.text("Hello World", 50, 200, WHITE, scale=3)
```

One call sets everything Arduino needed four calls for:
- **`"Hello World"`** — the text to draw
- **`50, 200`** — the position of the text's top-left corner
- **`WHITE`** — the color (built-ins: `BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN`)
- **`scale=3`** — the size multiplier; each character is 8×8 pixels times the scale

**How coordinates work:**
- The origin `(0, 0)` is the **top-left** corner.
- **x** increases to the right (0 to 319), **y** increases downward (0 to 479).

### 3. Clearing the screen

```python
tft.fill(BLACK)
```

Fills every pixel with one color — the standard way to start a new screen.

## Run it

Open `lesson01_helloworld.py` in Thonny and press **F5**, or:

```bash
mpremote run lesson01_helloworld.py
```

(The `st77xx.py` driver must already be on the board — see the
[tutorial README](../README.md#one-time-setup).)

## Extended Exercises

1. Change the text, the color, and the position.
2. Draw a second line of text below the first (each scale-3 character is 24 px tall).
3. Try the REPL: after the script finishes, type
   `tft.text("From the REPL!", 20, 300, CYAN, scale=2)` in the shell and watch the
   screen update instantly — no re-upload needed.

## FAQ

**The screen stays black.** Check the DC and RST wires first, confirm 3.3V power, and
make sure the backlight turned on (it lights even with wrong data wiring — if it's
completely dark, check the BLK pin and power).

**`ImportError: no module named 'st77xx'`.** The driver isn't on the board yet — copy
`micropython/lib/st77xx.py` to it (see the tutorial README).

**Text is mirrored or upside-down.** Your panel batch scans the other way: add
`flip_x=True` and/or `flip_y=True` to the `ST7796(...)` line.

---

Next: [Lesson 02: Colors](../Lesson02_Colors/README.md)
