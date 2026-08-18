# MicroPython test — 1.68 inch (NV3007)

`main.py` in this folder draws the same test picture as the Arduino sketch
("LonelyBinary", eight colour bars, screen info). It runs on **stock MicroPython
firmware** on both an **ESP32-S3** and a **classic ESP32** — the script detects the
chip and picks the right pins by itself.

## The driver is NOT in this folder — here is where it is

Customers most often get stuck here, so to be explicit: `main.py` imports a display
driver that is kept **once, for every size in this kit**, at the **root of the
repository**, in `micropython/lib/`. You need to copy it to the board too.

Everything that has to be on the board (root filesystem, next to each other):

| File | Where to get it | What it is |
| ---- | --------------- | ---------- |
| `st77xx.py` | [`micropython/lib/st77xx.py`](../../../../micropython/lib/st77xx.py) — repo root, **not this folder** | Display driver: all the drawing code (fill, text, lines...) |
| `nv3007.py` | [`micropython/lib/nv3007.py`](../../../../micropython/lib/nv3007.py) — repo root, **not this folder** | NV3007 power-up sequence for this panel; imports st77xx.py |
| `main.py` | this folder | The test script for the 1.68 inch |

Repository layout, so you can find it:

```
TFT-LCD/                          <- repository root
├── micropython/
│   └── lib/
│       ├── st77xx.py             <- driver, copy this
│       └── nv3007.py             <- and this (NV3007 sizes only)
└── narrow-lcd/1.68inch/code/micropython/
    └── main.py                   <- and this
```

## How to copy the files to the board

**Thonny (easiest):**

1. Flash MicroPython first if the board doesn't have it — see
   [micropython/README.md](../../../../micropython/README.md), Step 1.
2. **View → Files.** The top pane is your computer, the bottom pane is the board.
3. In the top pane navigate to the repository, right-click each file → **Upload to /**:
   - `micropython/lib/st77xx.py`
   - `micropython/lib/nv3007.py`
   - `narrow-lcd/1.68inch/code/micropython/main.py`
4. Press the board's reset button. `main.py` runs automatically at every boot.

**mpremote (command line):** from the root of the repository:

```bash
pip install mpremote
mpremote cp micropython/lib/st77xx.py :
mpremote cp micropython/lib/nv3007.py :
mpremote cp narrow-lcd/1.68inch/code/micropython/main.py :
mpremote reset
```

## Display details

- **Display:** 1.68 inch, 142x428 pixels (428x142 in landscape)
- **Driver IC:** NV3007 (uses the `nv3007.py` driver on top of `st77xx.py`)
- **Wiring:** same as the Arduino sketch — see [../../README.md](../../README.md) for this
  size's pin table. Both boards' pin sets are already in `main.py`.

## If the screen stays black

- The most common cause is a missing driver file: `ImportError: no module named 'st77xx'`
  (or `'nv3007'`) in the shell means it isn't on the board — copy it as above.
- **CS must be wired to the CS GPIO, not jumpered to GND.** With CS tied low the panel can't
  re-sync its SPI framing and stays black under MicroPython (the Arduino sketch may still
  appear to work). Remove any CS-to-GND jumper.
- More in the [MicroPython troubleshooting section](../../../../micropython/README.md#troubleshooting).
