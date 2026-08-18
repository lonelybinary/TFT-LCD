# MicroPython examples

Prefer Python over Arduino/C++? Every display size in this kit also has a
MicroPython test script. Like the Arduino sketches, **the same script runs
unmodified on both an ESP32-S3 and a classic ESP32** — it detects the chip at
runtime and picks the right pins automatically.

Everything runs on the **stock MicroPython firmware** from micropython.org.
No custom firmware build, no external libraries to hunt down — the display
driver is one or two small files in this repo ([`lib/st77xx.py`](lib/st77xx.py),
plus [`lib/nv3007.py`](lib/nv3007.py) for the two NV3007 sizes) that you copy to
the board next to the example.

## What's where

```
micropython/
├── README.md            # This guide
└── lib/
    ├── st77xx.py        # Driver for ST7735S / ST7789 / ST7796 (all drawing code lives here)
    └── nv3007.py        # NV3007 driver for the 1.68 / 2.79 inch - needs st77xx.py too
{size}inch/code/micropython/
└── main.py              # Ready-to-run test script for that display size
```

| Size      | Resolution | Driver chip | Test script |
| --------- | ---------- | ----------- | ----------- |
| 0.96 inch | 80 × 160   | ST7735S     | [`tft-lcd/0.96inch/code/micropython/main.py`](../tft-lcd/0.96inch/code/micropython/main.py) |
| 1.8 inch  | 128 × 160  | ST7735S     | [`tft-lcd/1.8inch/code/micropython/main.py`](../tft-lcd/1.8inch/code/micropython/main.py) |
| 2.0 inch  | 240 × 320  | ST7789      | [`tft-lcd/2.0inch/code/micropython/main.py`](../tft-lcd/2.0inch/code/micropython/main.py) |
| 2.4 inch  | 240 × 320  | ST7789      | [`tft-lcd/2.4inch/code/micropython/main.py`](../tft-lcd/2.4inch/code/micropython/main.py) |
| 2.8 inch  | 240 × 320  | ST7789      | [`tft-lcd/2.8inch/code/micropython/main.py`](../tft-lcd/2.8inch/code/micropython/main.py) |
| 3.5 inch  | 320 × 480  | ST7796      | [`tft-lcd/3.5inch/code/micropython/main.py`](../tft-lcd/3.5inch/code/micropython/main.py) |

### Narrow TFT LCD Collection

These run in **landscape** (`rotation=1`) and their backlight is **active low** (`LOW` = on).
The scripts already handle both.

| Size      | Resolution | Driver chip | Test script |
| --------- | ---------- | ----------- | ----------- |
| 1.14 inch | 135 × 240  | ST7789      | [`narrow-lcd/1.14inch/code/micropython/main.py`](../narrow-lcd/1.14inch/code/micropython/main.py) |
| 1.68 inch | 142 × 428  | NV3007      | [`narrow-lcd/1.68inch/code/micropython/main.py`](../narrow-lcd/1.68inch/code/micropython/main.py) |
| 1.9 inch  | 170 × 320  | ST7789      | [`narrow-lcd/1.9inch/code/micropython/main.py`](../narrow-lcd/1.9inch/code/micropython/main.py) |
| 2.25 inch | 76 × 284   | ST7789P3    | [`narrow-lcd/2.25inch/code/micropython/main.py`](../narrow-lcd/2.25inch/code/micropython/main.py) |
| 2.79 inch | 142 × 428  | NV3007      | [`narrow-lcd/2.79inch/code/micropython/main.py`](../narrow-lcd/2.79inch/code/micropython/main.py) |

> **The two NV3007 panels (1.68 and 2.79 inch) need a second driver file.** The NV3007 is
> a different controller with its own (much longer) initialisation sequence, so it lives in
> [`micropython/lib/nv3007.py`](lib/nv3007.py). That file borrows all the drawing code from
> `st77xx.py`, so for these two sizes copy **both** driver files to the board:
>
> ```bash
> mpremote cp micropython/lib/st77xx.py :
> mpremote cp micropython/lib/nv3007.py :
> ```
>
> Each size has its own class (`NV3007_168`, `NV3007_279`) carrying that panel's vendor
> voltage/gamma table — same values as the Arduino_GFX driver the Arduino sketches use.

Wiring is identical to the Arduino examples — see the table in the
[TFT-LCD series README](../tft-lcd/README.md#how-to-wire-it-up) or the
[Narrow LCD series README](../narrow-lcd/README.md#how-to-wire-it-up). You don't edit any code to
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

## Step 2 — Copy the files to the board

Copy the driver(s) plus the `main.py` for **your display size**. The drivers are in
`micropython/lib/` at the root of this repository, **not** in the size folders; each size's
`code/micropython/README.md` lists exactly which files it needs. Two ways:

**Easy way (Thonny):**

1. Open **View → Files**. The top pane is your computer, the bottom pane is
   the board.
2. Upload `micropython/lib/st77xx.py` to the board (right-click → *Upload to /*).
3. Upload the `main.py` for your size, e.g. `tft-lcd/2.4inch/code/micropython/main.py`.

**Command-line way (mpremote):**

```bash
pip install mpremote
# from the root of this repo (2.4 inch shown - use your size's folder):
mpremote cp micropython/lib/st77xx.py :
mpremote cp tft-lcd/2.4inch/code/micropython/main.py :
```

## Step 3 — Run it

Press the board's **reset** button (or run `mpremote reset`). A file named
`main.py` runs automatically every boot, so the display should light up and
show "LonelyBinary", eight color bars, and the screen info — the same test
picture as the Arduino sketch.

**Want to learn to build real interfaces next?** Work through the
[11-lesson MicroPython tutorial](../tutorials/micropython/README.md) — the Python
version of the Arduino lessons, from Hello World to a clock face.

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

`st77xx.py` exposes three classes — `ST7735`, `ST7789`, `ST7796` — and
`nv3007.py` adds `NV3007_168` and `NV3007_279`; all share the same API:

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
- **CS must be wired to the CS GPIO, not jumpered to GND.** With CS tied low
  the display never sees a CS edge, which is the only thing (short of a hard
  reset) that lets it re-sync its SPI byte framing — one stray clock pulse at
  boot then leaves every command misaligned and the panel stays black with the
  backlight on. The Arduino sketches may happen to work with CS grounded;
  MicroPython does not. Remove the CS-to-GND jumper and run CS to the pin in
  the wiring table.
- On the **0.96-inch** module the backlight is **active-low** (the script
  already handles this — but if you adapted the code, drive BLK LOW, not HIGH).

**Red and blue are swapped**
- Flip the `bgr=` argument where the display object is created in `main.py`.

**Picture is upside-down, or text reads like a mirror image**
- Panel batches differ in scan direction. Add or flip `flip_x=True` (left-right
  mirror) and/or `flip_y=True` (top-bottom mirror) where the display object is
  created — both together give a 180° rotation.

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
