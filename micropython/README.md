# MicroPython examples

Prefer Python over Arduino/C++? Every display size in this kit also has a
MicroPython test script. Like the Arduino sketches, **the same script runs
unmodified on both an ESP32-S3 and a classic ESP32** — it detects the chip at
runtime and picks the right pins automatically.

Everything runs on the **stock MicroPython firmware** from micropython.org.
No custom firmware build, no external libraries to hunt down — the display
driver is a single file in this repo ([`lib/st77xx.py`](lib/st77xx.py)) that
you copy to the board next to the example.

## What's where

```
micropython/
├── README.md            # This guide
└── lib/
    └── st77xx.py        # Driver for all three chips: ST7735S / ST7789 / ST7796
{size}inch/code/micropython/
└── main.py              # Ready-to-run test script for that display size
```

| Size      | Resolution | Driver chip | Test script |
| --------- | ---------- | ----------- | ----------- |
| 0.96 inch | 80 × 160   | ST7735S     | [`0.96inch/code/micropython/main.py`](../0.96inch/code/micropython/main.py) |
| 1.8 inch  | 128 × 160  | ST7735S     | [`1.8inch/code/micropython/main.py`](../1.8inch/code/micropython/main.py) |
| 2.0 inch  | 240 × 320  | ST7789      | [`2.0inch/code/micropython/main.py`](../2.0inch/code/micropython/main.py) |
| 2.4 inch  | 240 × 320  | ST7789      | [`2.4inch/code/micropython/main.py`](../2.4inch/code/micropython/main.py) |
| 2.8 inch  | 240 × 320  | ST7789      | [`2.8inch/code/micropython/main.py`](../2.8inch/code/micropython/main.py) |
| 3.5 inch  | 320 × 480  | ST7796      | [`3.5inch/code/micropython/main.py`](../3.5inch/code/micropython/main.py) |

Wiring is identical to the Arduino examples — see the table in the
[main README](../README.md#how-to-wire-it-up). You don't edit any code to
switch boards: the script checks which chip it is running on.

## Step 1 — Flash MicroPython (once per board)

You need **MicroPython v1.20 or newer**. Two ways to install it:

**Easy way (Thonny):**

1. Install [Thonny](https://thonny.org) (a beginner-friendly Python editor).
2. Plug in your board, then open **Run → Configure interpreter**.
3. Choose **MicroPython (ESP32)** and click **Install or update MicroPython**.
4. Pick your board family — **ESP32-S3** or **ESP32** — and the latest version,
   then click Install.

**Command-line way (esptool):**

1. Download the latest stable `.bin` from
   [micropython.org/download](https://micropython.org/download/) — choose
   **ESP32_GENERIC_S3** for an ESP32-S3 or **ESP32_GENERIC** for a classic ESP32.
2. Install esptool: `pip install esptool`
3. Erase and flash (replace the port with yours, e.g. `COM5` on Windows):

   ```bash
   # ESP32-S3 (note: flash offset 0x0)
   esptool.py --chip esp32s3 --port /dev/ttyUSB0 erase_flash
   esptool.py --chip esp32s3 --port /dev/ttyUSB0 write_flash -z 0x0 ESP32_GENERIC_S3-xxxx.bin

   # Classic ESP32 (note: flash offset 0x1000)
   esptool.py --chip esp32 --port /dev/ttyUSB0 erase_flash
   esptool.py --chip esp32 --port /dev/ttyUSB0 write_flash -z 0x1000 ESP32_GENERIC-xxxx.bin
   ```

> Some boards need the **BOOT** button held down while flashing starts.

## Step 2 — Copy two files to the board

Copy the driver plus the `main.py` for **your display size**. Two ways:

**Easy way (Thonny):**

1. Open **View → Files**. The top pane is your computer, the bottom pane is
   the board.
2. Upload `micropython/lib/st77xx.py` to the board (right-click → *Upload to /*).
3. Upload the `main.py` for your size, e.g. `2.4inch/code/micropython/main.py`.

**Command-line way (mpremote):**

```bash
pip install mpremote
# from the root of this repo (2.4 inch shown - use your size's folder):
mpremote cp micropython/lib/st77xx.py :
mpremote cp 2.4inch/code/micropython/main.py :
```

## Step 3 — Run it

Press the board's **reset** button (or run `mpremote reset`). A file named
`main.py` runs automatically every boot, so the display should light up and
show "LonelyBinary", eight color bars, and the screen info — the same test
picture as the Arduino sketch.

To experiment interactively instead, open a REPL (Thonny's shell, or
`mpremote repl`) and try:

```python
import st77xx
# ... create the display the same way main.py does, then:
tft.fill(st77xx.BLUE)
tft.text("Hello!", 10, 10, st77xx.WHITE, scale=2)
tft.fill_rect(10, 40, 100, 30, st77xx.YELLOW)
```

## Driver quick reference

`st77xx.py` exposes three classes — `ST7735`, `ST7789`, `ST7796` — that share
the same API:

| Call | What it does |
| ---- | ------------ |
| `fill(color)` | Fill the whole screen |
| `fill_rect(x, y, w, h, color)` | Filled rectangle |
| `rect(x, y, w, h, color)` | Rectangle outline |
| `hline(x, y, w, color)` / `vline(x, y, h, color)` | Horizontal / vertical line |
| `pixel(x, y, color)` | Single pixel |
| `text(s, x, y, color, bg=BLACK, scale=1)` | 8×8 font text, integer scaling |
| `blit(buf, x, y, w, h)` | Push a raw RGB565 pixel block |
| `set_rotation(r)` | 0 = portrait (as wired), 1–3 = rotated |
| `st77xx.color565(r, g, b)` | Make a color from 8-bit R, G, B |

Ready-made colors: `BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN`.

**A note on speed:** the driver is pure Python and draws straight to the panel
over SPI, so it's much slower than the compiled Arduino library — a full-screen
fill takes a noticeable fraction of a second on the larger panels. That's a
deliberate trade-off: it needs no custom firmware and almost no RAM. (A
full-screen framebuffer for the 3.5-inch panel would need 300 KB — more memory
than a classic ESP32 has free, which is why the driver doesn't use one.) For
text, menus, gauges and test patterns it's plenty; for animation you'd want a
compiled driver frozen into custom firmware.

## Troubleshooting

**Screen stays black / nothing shows up**
- Double-check every wire, especially **DC** and **RST** — a wrong DC pin is
  the most common cause.
- Make sure power is **3.3V**, not 5V.
- On the **0.96-inch** module the backlight is **active-low** (the script
  already handles this — but if you adapted the code, drive BLK LOW, not HIGH).

**Red and blue are swapped**
- Flip the `bgr=` argument where the display object is created in `main.py`.

**Colors look like a photo negative**
- Flip the `invert=` argument where the display object is created.

**Picture is shifted / has a noisy stripe on one edge (0.96-inch only)**
- Adjust `xstart` (typically 24–28) and `ystart` (0–3) in `main.py`. Small
  panels sit in the middle of the driver chip's RAM and individual batches
  can be offset by a pixel or two.

**`ImportError: no module named 'st77xx'`**
- The driver wasn't copied to the board. Repeat Step 2 — `st77xx.py` must be
  in the board's filesystem root (or `/lib`).

**`ValueError` when creating the SPI bus on old firmware**
- Very old MicroPython versions don't accept `miso=None`. Update to v1.20+
  (recommended), or pass any unused pin as `miso`.

**It works, but I want it faster**
- Keep drawing to the smallest area possible (the slow part is per-pixel
  Python work, e.g. in `text()` — solid fills are already fast since they
  stream from a small reusable buffer).
- Advanced users can freeze a compiled C driver into custom firmware — see
  the note on speed above.
