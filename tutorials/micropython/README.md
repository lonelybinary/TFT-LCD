# 3.5-inch TFT-LCD Display — MicroPython Beginner Tutorial

Welcome! This is the **MicroPython version** of the [Arduino tutorial](../3.5inch/README.md):
the same 11 lessons, the same screens, but written in Python. You go from a blank screen to
building menus, dashboards, notifications, and a clock face.

The same code runs on both an **ESP32-S3** and a **classic ESP32** board. You don't edit
any pins — each lesson detects the chip it is running on and picks the right pin set
automatically.

## What you'll learn

There are **11 short lessons**, and each one builds on the last. You start with a single
line of text ("Hello World"), then add colors, text sizes, styles, and shapes. By the end
you'll combine everything into real interfaces.

Work through them in order. Each lesson has a small, ready-to-run script and a README that
explains what the code does.

## Display specifications

- **Size**: 3.5 inch
- **Resolution**: 320 × 480 pixels (portrait by default)
- **Driver chip**: ST7796
- **Panel type**: IPS TFT-LCD (wide viewing angle, accurate colors)
- **Interface**: SPI (4-wire, hardware SPI)
- **Color depth**: 16-bit (called RGB565 — more on this in Lesson 2)

Using a different size? The lessons work on any display in this kit — change the
constructor line to your size's class and settings, exactly as shown in the table at the
top of [`micropython/lib/st77xx.py`](../../micropython/lib/st77xx.py).

## What you need

- An **ESP32 board** — either an **ESP32-S3** (the default) or a **classic ESP32**
  (such as the Lonely Binary PinPulse). The code works on both.
- The **3.5-inch TFT-LCD display** module.
- A few jumper wires (or the included ribbon cable + breakout board).
- **MicroPython firmware** on the board and the **`st77xx.py` driver** copied to it —
  one-time setup, explained next.

## One-time setup

1. **Flash MicroPython** (v1.20+) onto your board and **copy the driver
   `micropython/lib/st77xx.py`** to it. Both steps are explained in the
   [MicroPython setup guide](../../micropython/README.md) — do "Step 1" and the driver
   half of "Step 2" there, then come back.
2. Wiring is the same as the Arduino tutorial — see the table below.

| Display pin | ESP32-S3 (default) | Classic ESP32 | What it does |
|------------|--------------------|---------------|--------------|
| VDD | 3.3V | 3.3V | Power (**use 3.3V, never 5V**) |
| GND | GND | GND | Ground |
| CS | GPIO 10 | GPIO 15 | Chip select |
| RST | GPIO 42 | GPIO 4 | Reset |
| DC | GPIO 2 | GPIO 2 | Data/command select (**must connect**) |
| MOSI / SDA | GPIO 11 | GPIO 23 | SPI data |
| SCLK / SCL | GPIO 12 | GPIO 18 | SPI clock |
| BLK / LEDA | GPIO 41 | GPIO 32 | Backlight (on/off) |

## How to run a lesson

Unlike Arduino, there's **no compiling and no uploading** — you run the script directly:

**With Thonny** (easiest): open the lesson file, e.g.
`Lesson01_HelloWorld/lesson01_helloworld.py`, make sure the interpreter is set to your
board (bottom-right corner), and press **F5 (Run)**. Output appears in the Shell pane.

**With mpremote** (command line):

```bash
mpremote run tutorials/micropython/Lesson01_HelloWorld/lesson01_helloworld.py
```

`mpremote run` executes the local file on the board without copying it. If you want a
lesson to start automatically at boot instead, copy it as `main.py`:

```bash
mpremote cp tutorials/micropython/Lesson01_HelloWorld/lesson01_helloworld.py :main.py
```

## Coming from the Arduino lessons?

The concepts are identical; only the function names change. Quick map:

| Arduino (`gfx->…`) | MicroPython (`tft.…`) |
| --- | --- |
| `fillScreen(c)` | `fill(c)` |
| `setCursor(x,y)` + `setTextColor(c)` + `setTextSize(n)` + `println(s)` | `text(s, x, y, c, scale=n)` — one call |
| `setTextColor(fg, bg)` | `text(s, x, y, fg, bg=bg)` |
| `drawLine(...)` | `line(...)` |
| `drawRect(...)` / `fillRect(...)` | `rect(...)` / `fill_rect(...)` |
| `drawCircle(...)` / `fillCircle(...)` | `circle(...)` / `fill_circle(...)` |
| `fillTriangle(...)` | `fill_triangle(...)` |
| `drawFastHLine(x,y,w,c)` | `hline(x,y,w,c)` |
| `setRotation(r)` | `set_rotation(r)` |
| `width()` / `height()` | `.width` / `.height` (attributes) |
| `color565(r,g,b)` | `st77xx.color565(r,g,b)` |
| `delay(ms)` | `time.sleep(seconds)` |

**One important difference:** Arduino's font is **6 px** per character; MicroPython's
built-in font is **8 px** per character (both are 8 px tall, times the scale). So text is
about a third wider here — a few lesson layouts shift coordinates slightly, and text width
math is `len(s) * 8 * scale` instead of `len(s) * 6 * size`.

## Lesson directory

### [Lesson 01: Hello World](Lesson01_HelloWorld/README.md)
**Goal**: Show your first text on the screen.

### [Lesson 02: Colors](Lesson02_Colors/README.md)
**Goal**: Use the built-in colors, fill the screen, color your text.

### [Lesson 03: Text Size](Lesson03_TextSize/README.md)
**Goal**: Make text bigger or smaller with `scale=`.

### [Lesson 04: Text Style](Lesson04_TextStyle/README.md)
**Goal**: Background colors, labels, and highlight effects.

### [Lesson 05: Graphics](Lesson05_Graphics/README.md)
**Goal**: Lines, rectangles, circles, triangles — and a progress bar.

### [Lesson 06: Rotation](Lesson06_Rotation/README.md)
**Goal**: Turn the screen sideways and understand the coordinate system.

### [Lesson 07: System Info Display](Lesson07_SystemInfo/README.md)
**Goal**: Build a system-info screen from reusable helper functions.

### [Lesson 08: Menu Interface](Lesson08_Menu/README.md)
**Goal**: Build a menu with a highlighted selection.

### [Lesson 09: Data Monitoring Interface](Lesson09_DataMonitoring/README.md)
**Goal**: Build a dashboard with card-style layout.

### [Lesson 10: Notification Interface](Lesson10_Notification/README.md)
**Goal**: Build a notification card with an icon and close button.

### [Lesson 11: Clock Display](Lesson11_Clock/README.md)
**Goal**: Draw an analog clock face with `math.sin()` and `math.cos()`.

## How to get the most out of this tutorial

1. **Go in order.** Each lesson assumes you've done the ones before it.
2. **Run every script.** Seeing it on real hardware is the whole point.
3. **Use the REPL.** This is MicroPython's superpower over Arduino: after a lesson runs,
   you can keep typing commands interactively (`tft.fill_circle(160, 240, 50, RED)`) and
   watch the screen react instantly. Experiment!
4. **Try the Extended Exercises** at the end of each lesson README.

## Troubleshooting

**Screen stays black / nothing shows up**
- Double-check every wire, especially **DC** and **RST**.
- Make sure power is **3.3V**, not 5V.

**`ImportError: no module named 'st77xx'`**
- The driver isn't on the board yet — see [One-time setup](#one-time-setup).

**Text reads like a mirror image, or the picture is upside-down**
- Panel batches vary in scan direction. Add `flip_x=True` and/or `flip_y=True` to the
  `ST7796(...)` constructor line in the lesson.

**Colors look wrong (red shows as blue)**
- Flip the `bgr=` argument in the constructor line.

**Drawing feels slower than the Arduino version**
- That's expected: the driver is pure Python so that it runs on stock firmware with no
  custom build. Solid fills are fast; per-pixel work (text, diagonal lines, circle
  outlines) is slower. Lesson 5 shows the main trick: redraw only what changed instead
  of clearing the whole screen.

## After you finish

Once you've completed all 11 lessons, you'll be able to:
- [ ] Initialize the display and show text
- [ ] Use colors and make your own with `color565()`
- [ ] Control text size and put backgrounds behind text
- [ ] Draw lines, rectangles, circles, and triangles
- [ ] Rotate the display
- [ ] Build a system-info screen, a menu, a dashboard, a notification, and a clock face
- [ ] Wrap common drawing code into reusable Python functions

From there, try reading a real sensor and showing live data, using `machine.RTC` to make
the clock tick, or adapting a lesson to another display size in this kit.

## Helpful links

- [MicroPython setup guide for this kit](../../micropython/README.md)
- [The st77xx driver](../../micropython/lib/st77xx.py)
- [The Arduino version of this tutorial](../3.5inch/README.md)
- [MicroPython documentation](https://docs.micropython.org/)

## License

MIT License

---

**Happy building! Let's start with [Lesson 01: Hello World](Lesson01_HelloWorld/README.md). 🚀**
