# Narrow LCD Series (1.14 – 2.79 inch)

Five long, narrow IPS colour strips — good for status bars, dashboards, instrument panels
and anything that suits a wide, short display. Every module uses the **same 15-pin FPC
connector** as every other Lonely Binary display, so they all plug into the same breakout
board: swap sizes (or move to the [TFT-LCD series](../tft-lcd/README.md)) without rewiring
anything.

The same sketches run on both an **ESP32-S3** and a **classic ESP32** — no code changes,
just pick your board in the Arduino IDE.

New to these displays? Read this page top to bottom. To learn to write your own code, follow
the step-by-step lessons in [tutorials/3.5inch/](../tutorials/3.5inch/README.md) and use the
`ADAPTATION_GUIDE.md` in your size's folder to adjust them for the narrow shape.

## Sizes in this series

These are **display-only** modules — no touch. Each connects with the ribbon cable and the
small breakout board, so you only need 8 wires to get a picture.

| Size      | Resolution | In the examples (landscape) | Driver chip | SPI clock | Folder |
| --------- | ---------- | --------------------------- | ----------- | --------- | ------ |
| 1.14 inch | 135 × 240  | 240 × 135                   | ST7789      | 8 MHz     | [`1.14inch/`](1.14inch/README.md) |
| 1.68 inch | 142 × 428  | 428 × 142                   | NV3007      | 8 MHz     | [`1.68inch/`](1.68inch/README.md) |
| 1.9 inch  | 170 × 320  | 320 × 170                   | ST7789      | 8 MHz     | [`1.9inch/`](1.9inch/README.md) |
| 2.25 inch | 76 × 284   | 284 × 76                    | ST7789P3    | 8 MHz     | [`2.25inch/`](2.25inch/README.md) |
| 2.79 inch | 142 × 428  | 428 × 142                   | NV3007      | 20 MHz    | [`2.79inch/`](2.79inch/README.md) |

Each size folder contains:

```
{size}inch/
├── README.md               # Specs, wiring and the picture offsets for that size
├── ADAPTATION_GUIDE.md     # How to adapt the 3.5-inch lessons to this size
└── code/
    ├── {size}_Test/
    │   └── {size}_Test.ino # Ready-to-upload demo sketch (Arduino IDE)
    └── micropython/
        ├── README.md       # Which files to copy to the board, and from where
        └── main.py         # Test picture, in MicroPython
```

## Three things that are different about this series

All three are already handled in the example code — but they matter if you write your own:

- **The examples run in landscape** (`setRotation(1)` / `rotation=1`). Held as wired these
  panels are only 76–170 pixels across — too narrow for a word like "LonelyBinary" — so the
  examples turn them on their side. The TFT-LCD series uses rotation 0.
- **The backlight is active LOW** (`LOW` = on) on every size here. Most of the TFT-LCD series
  uses `HIGH`. The Arduino demos drive it with PWM for a brightness sweep; MicroPython uses
  plain on/off.
- **Each panel needs its own picture offsets**, measured on real hardware, and only two of
  the four offset values are active at rotation 1. Read the per-size README before changing
  them — the 1.14 inch (52/40/53/40) and the two NV3007 panels (12/0/14/0) are asymmetric.

## What you need

- An **ESP32 board**. This kit is wired for an **ESP32-S3** by default, but the examples
  also run on a **classic ESP32**. You do not need to change the code — just pick the right
  board in the Arduino IDE (explained below).
- One of the display modules above.
- The included ribbon FPC cable + breakout board (or a few jumper wires).

## Required software versions

Most compile failures come from a version mismatch, so please install these:

| Component                         | Required version          | Tested with | Where to get it                            |
| --------------------------------- | ------------------------- | ----------- | ------------------------------------------ |
| **Arduino IDE**                   | 2.x (latest)              | 2.x         | [arduino.cc/en/software](https://www.arduino.cc/en/software) |
| **ESP32 board package** (Espressif) | **3.0.0 or newer**        | **3.3.10**  | Tools → Board → Boards Manager → `esp32`   |
| **GFX Library for Arduino** (Moon On Our Nation) | **1.5.0 or newer** (NV3007 sizes: a version that includes `Arduino_NV3007`) | **1.6.6** | Tools → Manage Libraries → `GFX Library for Arduino` |

> The exact versions in the **Tested with** column are the ones these sketches were last verified
> against. Newer versions are expected to work too; the **Required version** column is the minimum.

> ⚠️ **The ESP32 board package must be 3.0.0 or newer.** Recent versions of the GFX library
> include the header `esp32-hal-periman.h`, which only exists in **ESP32 core 3.0.0+**. If you
> compile with an older core (e.g. 2.0.17), you get:
> ```
> fatal error: esp32-hal-periman.h: No such file or directory
> ```
> The fix is to update the ESP32 board package to 3.0.0 or newer (see step 2 below), **not** to
> change any code.

## How to wire it up

Connect the 8 pins on the breakout to your ESP32. **Which GPIO numbers to use depends on
your board** — use the column that matches the board you have:

| Display pin       | ESP32-S3 (default) | Classic ESP32 | What it does                   |
| ----------------- | ------------------ | ------------- | ------------------------------ |
| VDD (pin 7)       | 3.3V               | 3.3V          | Power (use 3.3V, **never 5V**) |
| GND (pin 2)       | GND                | GND           | Ground                         |
| CS (pin 8)        | GPIO 10            | GPIO 15       | Chip select                    |
| RESET (pin 3)     | GPIO 42            | GPIO 4        | Reset                          |
| DC/RS/A0 (pin 4)  | GPIO 2             | GPIO 2        | Data/command select            |
| SDA/MOSI (pin 5)  | GPIO 11            | GPIO 23       | SPI data                       |
| SCL/SCLK (pin 6)  | GPIO 12            | GPIO 18       | SPI clock                      |
| LEDA/BLK (pin 1)  | GPIO 41            | GPIO 32       | Backlight (**LOW = on**)       |

**You don't edit the code for this.** Each sketch already contains both pin sets and picks
the right one automatically based on the board you select in the Arduino IDE. If you ever
want to use different pins, change the `#define TFT_*` lines near the top of the `.ino` file.

> **Why are the pin numbers different?** The classic ESP32 simply doesn't have GPIO 41 or 42,
> and its GPIO 6–11 are reserved for internal flash memory — so the ESP32-S3 pins can't be
> reused. The classic ESP32 column uses its standard hardware-SPI pins instead.

> **CS must go to the CS GPIO.** Don't tie CS to GND with a jumper "to save a wire": the
> Arduino sketch may still appear to work, but the MicroPython examples will show a black
> screen (the panel can't re-sync its SPI framing without a CS edge).

## Step-by-step setup (Arduino IDE)

1. **Install the Arduino IDE** from [arduino.cc/en/software](https://www.arduino.cc/en/software).
2. **Add ESP32 board support.**
   - Open **Tools → Board → Boards Manager**.
   - Search for `esp32` (by Espressif Systems) and click **Install**.
   - Install **version 3.0.0 or newer** (the latest is recommended). Versions older than 3.0.0
     will fail to compile with `esp32-hal-periman.h: No such file or directory`.
3. **Install the display library.**
   - Open **Tools → Manage Libraries**.
   - Search for `GFX Library for Arduino` (by Moon On Our Nation) and click **Install**.
   - Install **version 1.5.0 or newer** (the latest is recommended).
4. **Open an example.**
   - Open the `.ino` file for your display size, e.g. `1.9inch/code/1.9inch_Test/1.9inch_Test.ino`.
5. **Select your board** under **Tools → Board → ESP32 Arduino**:
   - Choose **ESP32S3 Dev Module** if you have an ESP32-S3.
   - Choose **ESP32 Dev Module** if you have a classic ESP32 (e.g. PinPulse).
6. **Select the port** under **Tools → Port** (plug in your board first).
7. **Click Upload** (the → arrow). The demo shows red / green / blue, a backlight brightness
   sweep, a screen-info page and a thank-you page.

> **Tip:** These examples were last tested with **ESP32 core 3.3.10** and **GFX Library 1.6.6**.
> The ESP32 core must be **3.0.0 or newer** — see [Required software versions](#required-software-versions) above.

## Prefer Python?

Every size has a MicroPython test in `{size}inch/code/micropython/`. It runs on stock
MicroPython firmware on both boards, using the shared drivers at the **root of the
repository** (not inside the size folder — the `README.md` next to each `main.py` shows
exactly which files to copy):

- [`micropython/lib/st77xx.py`](../micropython/lib/st77xx.py) — all sizes (drawing code + ST7789 init)
- [`micropython/lib/nv3007.py`](../micropython/lib/nv3007.py) — **also** needed for the 1.68 and 2.79 inch (NV3007)

Setup guide: [micropython/README.md](../micropython/README.md). There is also a full
MicroPython version of the 11 lessons: [tutorials/micropython/](../tutorials/micropython/README.md).

## Troubleshooting

**Screen stays black / nothing shows up**

- Double-check every wire, especially **DC** and **RST** — a wrong DC pin is the most common cause.
- Make sure power is **3.3V**, not 5V.
- Confirm you selected the matching board (ESP32S3 Dev Module vs ESP32 Dev Module).
- Make sure CS is wired to the CS GPIO, not jumpered to GND (see the wiring note above).

**Backlight lights up but the screen stays blank — only on classic ESP32**

This is almost always the **wrong SPI bus number**. The ESP32 core numbers its SPI
buses differently per chip: the value `1` means `HSPI` (a usable bus) on the **ESP32-S3**,
but means `FSPI` — the bus wired to the on-chip program flash — on the **classic ESP32**.
The sketches in this repo select the bus with the named macro `TFT_SPI_NUM` (`HSPI` on the
S3, `VSPI` on the classic ESP32) instead of a literal number — if you adapt your own code,
do the same rather than passing `1`.

**Picture is shifted / a stripe of noise on one edge**

- The offsets for that size are wrong. Every panel in this series needs its own values,
  and only two of the four are active at rotation 1 — see the "Adjusting the picture position"
  section of the per-size README.

**Upload fails / wrong port**

- Pick the correct port under **Tools → Port**.
- Some boards need you to hold the **BOOT** button while uploading.

**Colors look wrong / red shows as blue**

- Make sure you opened the example for your exact display size — the IPS/inversion setting
  and (for the NV3007 sizes) the init table differ per size.

**Code won't compile**

- Re-check that the ESP32 board package and the GFX library both installed correctly.
- Make sure the correct board is selected under **Tools → Board**.
- **`fatal error: esp32-hal-periman.h: No such file or directory`** — your ESP32 board package
  is older than 3.0.0. Update it to **3.0.0 or newer**.
- **`Arduino_NV3007` not found** (1.68 / 2.79 inch) — update the GFX Library to a recent version.

## License

MIT License
