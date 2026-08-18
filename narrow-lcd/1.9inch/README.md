# 1.9 Inch TFT-LCD Display (Narrow TFT LCD Collection)

A 1.9-inch narrow color display for your ESP32 projects — a good middle ground - wide enough for two columns of text. This page covers the
specs and wiring for this size. For full setup steps, see the [main README](../README.md).

## The basics

- **Driver chip:** ST7789
- **Resolution:** 170 × 320 pixels (portrait, as wired)
- **In the examples:** 320 × 170 — the examples run in landscape (rotation 1)
- **Colors:** 16-bit (65,536 colors)
- **Connection:** SPI (a fast, simple way to talk to the screen)
- **SPI clock:** 8 MHz (tested)
- **Power:** 3.3V only (never 5V)
- **Touch:** no — this is a display-only module

## Why landscape?

Every screen in this collection is a narrow strip. Held the way it is wired, this one is only
**170 pixels wide** — not enough room for a word like "LonelyBinary" across the top. So the
examples call `setRotation(1)`, which turns the panel on its side and gives you **320 × 170**.
The wider screens elsewhere in this repo use rotation 0; this collection is the exception.

If you would rather work in portrait, change `setRotation(1)` to `setRotation(0)` — but see
the offset note below, because the offsets that apply change with the rotation.

## How to wire it up

These are the 8 wires between the display and your board. **Which GPIO numbers to use depends on
your board** — pick the column that matches the board you have.

| Display pin | ESP32-S3 (default) | Classic ESP32 | What it does |
|-------------|--------------------|---------------|--------------|
| VCC / VDD | 3.3V | 3.3V | Power (use 3.3V, **never 5V**) |
| GND | GND | GND | Ground |
| CS | GPIO 10 | GPIO 15 | Chip select |
| RST | GPIO 42 | GPIO 4 | Reset |
| DC | GPIO 2 | GPIO 2 | Data/command select |
| MOSI / SDA | GPIO 11 | GPIO 23 | SPI data |
| SCLK / SCL | GPIO 12 | GPIO 18 | SPI clock |
| BLK / LEDA | GPIO 41 | GPIO 32 | Backlight |

Every screen in this collection uses the same 15-pin FPC connector, so they all plug into the
same breakout board — you can swap sizes without rewiring anything. The only thing that changes
in software is which example you open.

**You don't edit the code to switch boards.** The sketch already contains both pin sets and picks
the right one automatically based on the board you select in the Arduino IDE (`#if defined(CONFIG_IDF_TARGET_ESP32S3)`).
Just choose **ESP32S3 Dev Module** for an ESP32-S3, or **ESP32 Dev Module** for a classic ESP32
(such as the Lonely Binary PinPulse).

> **Why are the pin numbers different?** The classic ESP32 doesn't have GPIO 41 or 42, and its
> GPIO 6–11 are reserved for internal flash memory — so the ESP32-S3 pins can't be reused. The
> classic ESP32 column uses its standard hardware-SPI pins instead.

> **Backlight on this collection is active low:** `LOW` turns the backlight ON. Several of the
> wider screens in this repo use `HIGH` — don't copy that line across. It's still simple on/off;
> there is no brightness control. The example handles this for you.

## Adjusting the picture position (offset)

This size ships with `35, 0, 35, 0` (col offset 1, row offset 1, col offset 2, row offset 2).

**Only two of those four are active at any one rotation**, which is worth knowing before you
start changing numbers. The GFX library picks them like this:

| Rotation | X offset comes from | Y offset comes from |
|----------|---------------------|---------------------|
| 0 | col offset 1 | row offset 1 |
| 1 (used by the examples) | **row offset 1** | **col offset 2** |

So on the examples in this folder, the two numbers that matter are **row offset 1 = 0**
(horizontal) and **col offset 2 = 35** (vertical). Editing col offset 1 will appear to do
nothing at all.

If the picture looks shifted — content cut off at one edge and a blank band at the opposite edge
— nudge the relevant number by 1 or 2. Different batches can vary slightly.

## Try it out

1. Open `code/1.9inch_Test/1.9inch_Test.ino` in the Arduino IDE.
2. Select your board (**ESP32S3 Dev Module** or **ESP32 Dev Module**) and the right port.
3. Click Upload.

The demo runs through four scenes once, then stops on the thank-you page (press reset to see
it again):

1. **Red, green and blue** full screen, 2 seconds each, with the colour name in the middle —
   confirms the panel, the wiring and the colour order.
2. **A brightness sweep**, 100% → 10% → 100%, on a white background — confirms the backlight
   pin and shows off PWM dimming.
3. **A screen info page** — driver, resolution, pins and SPI clock.
4. **A thank-you page**, with a reminder that every size in the collection shares the same
   15-pin FPC connector, so you can swap displays without rewiring.

New here? The full step-by-step setup (installing the IDE, the ESP32 boards, and the display
library) lives in the [main README](../README.md). Ready to write your own code? Work through the
beginner lessons in [`tutorials/3.5inch/`](../tutorials/3.5inch/README.md), and use this size's
`ADAPTATION_GUIDE.md` to adjust them for the 1.9-inch screen.

## Prefer Python?

There is a MicroPython version of the same test in `code/micropython/main.py`. It runs on
stock MicroPython firmware using the shared `st77xx.py` driver — see
[micropython/README.md](../micropython/README.md) for the setup steps.

## Library versions

The examples were tested with the **latest** Arduino ESP32 core and the **latest** GFX Library for
Arduino. (The sketch has a tiny color-compatibility helper so it builds on old and new GFX
versions; you never need to touch it.)

## If something isn't working

**Screen stays black**
- Re-check every wire, especially **DC** and **RST**.
- Make sure power is **3.3V**, not 5V.
- Confirm you picked the matching board (ESP32S3 Dev Module vs ESP32 Dev Module).
- Check the backlight line: this collection is **active low** (`LOW` = on).

**Picture looks shifted**
- Adjust the offsets as described above — remember that at rotation 1 only **row offset 1** and
  **col offset 2** do anything.

**Colors look wrong / everything looks like a photo negative**
- That is the IPS setting. This size uses `true`; the example already has it right.

**Upload fails**
- Pick the correct port under **Tools → Port**. Some boards need you to hold **BOOT** while uploading.

## License

MIT License
