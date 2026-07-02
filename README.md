# TFT-LCD Display Kit

Beginner-friendly example code for Lonely Binary SPI TFT-LCD displays, in six sizes.
The same sketches run on both an **ESP32-S3** and a **classic ESP32** board.

New to these displays? Start here, then follow the step-by-step lessons in
[tutorials/3.5inch/](tutorials/3.5inch/README.md).

## What's in the box

These are **display-only** modules — there is no touch screen. Each module connects with
a ribbon cable and a small breakout board, so you only need 8 wires to get a picture.


| Size      | Resolution | Driver chip |
| --------- | ---------- | ----------- |
| 0.96 inch | 80 × 160   | ST7735S     |
| 1.8 inch  | 128 × 160  | ST7735S     |
| 2.0 inch  | 240 × 320  | ST7789      |
| 2.4 inch  | 240 × 320  | ST7789      |
| 2.8 inch  | 240 × 320  | ST7789      |
| 3.5 inch  | 320 × 480  | ST7796      |


## What you need

- An **ESP32 board**. This kit is wired for an **ESP32-S3** by default, but the examples
also run on a **classic ESP32**. You do not need to change the code — just pick the right board in the Arduino IDE (explained below).
- One of the TFT-LCD display modules above.
- A few jumper wires (or the included ribbon FPC cable + breakout board).

## Required software versions

Most compile failures come from a version mismatch, so please install these:

| Component                         | Required version          | Tested with | Where to get it                            |
| --------------------------------- | ------------------------- | ----------- | ------------------------------------------ |
| **Arduino IDE**                   | 2.x (latest)              | 2.x         | [arduino.cc/en/software](https://www.arduino.cc/en/software) |
| **ESP32 board package** (Espressif) | **3.0.0 or newer**        | **3.3.10**  | Tools → Board → Boards Manager → `esp32`   |
| **GFX Library for Arduino** (Moon On Our Nation) | **1.5.0 or newer** | **1.6.6**   | Tools → Manage Libraries → `GFX Library for Arduino` |

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

Connect the 8 pins on the display to your ESP32. **Which GPIO numbers to use depends on
your board** — use the column that matches the board you have:


| Display pin | ESP32-S3 (default) | Classic ESP32 | What it does                   |
| ----------- | ------------------ | ------------- | ------------------------------ |
| VCC / VDD   | 3.3V               | 3.3V          | Power (use 3.3V, **never 5V**) |
| GND         | GND                | GND           | Ground                         |
| CS          | GPIO 10            | GPIO 15       | Chip select                    |
| RST         | GPIO 42            | GPIO 4        | Reset                          |
| DC          | GPIO 2             | GPIO 2        | Data/command select            |
| MOSI / SDA  | GPIO 11            | GPIO 23       | SPI data                       |
| SCLK / SCL  | GPIO 12            | GPIO 18       | SPI clock                      |
| BLK / LEDA  | GPIO 41            | GPIO 32       | Backlight                      |


**You don't edit the code for this.** Each sketch already contains both pin sets and picks
the right one automatically based on the board you select in the Arduino IDE. If you ever
want to use different pins, change the `#define TFT_*` lines near the top of the `.ino` file.

> **Why are the pin numbers different?** The classic ESP32 simply doesn't have GPIO 41 or 42,
> and its GPIO 6–11 are reserved for internal flash memory — so the ESP32-S3 pins can't be
> reused. The classic ESP32 column uses its standard hardware-SPI pins instead.

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
  - Open the `.ino` file for your display size, e.g. `2.4inch/code/2.4inch_Test/2.4inch_Test.ino`.
5. **Select your board** under **Tools → Board → ESP32 Arduino**:
  - Choose **ESP32S3 Dev Module** if you have an ESP32-S3.
  - Choose **ESP32 Dev Module** if you have a classic ESP32 (e.g. PinPulse).
6. **Select the port** under **Tools → Port** (plug in your board first).
7. **Click Upload** (the → arrow). The display should light up and show a test image.

> **Tip:** These examples were last tested with **ESP32 core 3.3.10** and **GFX Library 1.6.6**.
> The ESP32 core must be **3.0.0 or newer** — see [Required software versions](#required-software-versions) above.

## Where to go next

- **Just want to check the screen works?** Upload the test sketch in `{size}inch/code/`.
- **Want to learn to code for it?** Work through the 11 lessons in
[tutorials/3.5inch/](tutorials/3.5inch/README.md), starting with Hello World.
- **Prefer Python?** Every size also has a **MicroPython** test script that runs on
stock MicroPython firmware, on both ESP32-S3 and classic ESP32 — see
[micropython/README.md](micropython/README.md). There's a full MicroPython version of
the 11 lessons too: [tutorials/micropython/](tutorials/micropython/README.md).
- **Have a different size than 3.5 inch?** Each size folder has an `ADAPTATION_GUIDE.md`
that shows how to adjust the 3.5-inch lesson code for your screen.

## Troubleshooting

**Screen stays black / nothing shows up**

- Double-check every wire, especially **DC** and **RST** — a wrong DC pin is the most common cause.
- Make sure power is **3.3V**, not 5V.
- Confirm you selected the matching board (ESP32S3 Dev Module vs ESP32 Dev Module).

**Backlight lights up but the screen stays blank — only on classic ESP32**

This is almost always the **wrong SPI bus number**. The ESP32 core numbers its SPI
buses differently per chip: the value `1` means `HSPI` (a usable bus) on the **ESP32-S3**,
but means `FSPI` — the bus wired to the on-chip program flash — on the **classic ESP32**.
A sketch that hard-codes `1` for the bus therefore works on the S3 but produces a lit
backlight with a black screen on the classic ESP32 (the backlight is just a GPIO, so it
still turns on). The sketches in this repo fix this by selecting the bus with the named
macro `TFT_SPI_NUM` (`HSPI` on the S3, `VSPI` on the classic ESP32) instead of a literal
number — if you adapt your own code, do the same rather than passing `1`.

**Upload fails / wrong port**

- Pick the correct port under **Tools → Port**.
- Some boards need you to hold the **BOOT** button while uploading.

**Colors look wrong**

- This usually means the wrong driver or wiring. Make sure you opened the example for your
exact display size.

**Code won't compile**

- Re-check that the ESP32 board package and the GFX library both installed correctly.
- Make sure the correct board is selected under **Tools → Board**.
- **`fatal error: esp32-hal-periman.h: No such file or directory`** — your ESP32 board package
is older than 3.0.0. Open **Tools → Board → Boards Manager**, find `esp32` by Espressif, and
update it to **3.0.0 or newer**. See [Required software versions](#required-software-versions).

## Project structure

```
TFT-LCD/
├── {size}inch/                 # One folder per display size (0.96, 1.8, 2.0, 2.4, 2.8, 3.5)
│   ├── README.md               # Specs + wiring for that size
│   ├── ADAPTATION_GUIDE.md     # How to adapt the 3.5-inch lessons to this size
│   └── code/
│       ├── {size}_Test/
│       │   └── {size}_Test.ino # Ready-to-upload test sketch (Arduino IDE)
│       └── micropython/
│           └── main.py         # Same test, in MicroPython
├── micropython/
│   ├── README.md               # MicroPython setup guide (flashing, copying files)
│   └── lib/
│       └── st77xx.py           # MicroPython driver (ST7735S / ST7789 / ST7796)
└── tutorials/
    ├── 3.5inch/                # 11 beginner lessons, Arduino (Hello World → Clock)
    │   ├── Lesson01_HelloWorld/
    │   ├── Lesson02_Colors/
    │   └── ...
    └── micropython/            # The same 11 lessons, in MicroPython
        ├── Lesson01_HelloWorld/
        └── ...
```

## Notes about the hardware

- **Backlight** is simple on/off (no brightness/PWM control). On most sizes `HIGH` = on;
on the 0.96-inch module `LOW` = on.
- These modules use **hardware SPI** for a fast, stable picture, so MOSI and SCLK should stay
on the pins listed above.

## License

MIT License