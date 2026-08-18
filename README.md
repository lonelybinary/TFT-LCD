# Lonely Binary TFT-LCD Displays

Beginner-friendly example code for Lonely Binary SPI TFT-LCD displays — eleven sizes in two
series — for **ESP32-S3** and **classic ESP32**, in **Arduino** and **MicroPython**.

## One connector, every display

**Every Lonely Binary display uses the same 15-pin FPC connector** — all eleven TFT-LCD sizes
here, and our e-paper and touch displays too. They all plug into the same breakout board, so
you wire the breakout to your ESP32 **once** and then swap screens freely: no rewiring, no
new pin table, just open the example for the size you plugged in.

## Pick your series

| Series | Sizes | Shape | Start here |
| ------ | ----- | ----- | ---------- |
| **TFT-LCD** | 0.96 · 1.8 · 2.0 · 2.4 · 2.8 · 3.5 inch | Classic rectangular panels | [tft-lcd/README.md](tft-lcd/README.md) |
| **Narrow LCD** | 1.14 · 1.68 · 1.9 · 2.25 · 2.79 inch | Long, narrow strips (status bars, gauges) | [narrow-lcd/README.md](narrow-lcd/README.md) |

Each series README has everything for that series: the size table, wiring for both boards,
required software versions, Arduino IDE setup step by step, and troubleshooting. Inside, each
size has its own folder with a specs/wiring page, a ready-to-upload test sketch, a MicroPython
test, and a guide for adapting the lessons to that size.

## Learn to code for it

- **[tutorials/3.5inch/](tutorials/3.5inch/README.md)** — 11 step-by-step Arduino lessons,
  from Hello World to a clock face. Written for the 3.5 inch; every other size folder has an
  `ADAPTATION_GUIDE.md` that shows what to change.
- **[tutorials/micropython/](tutorials/micropython/README.md)** — the same 11 lessons in
  MicroPython.

## MicroPython

- **[micropython/README.md](micropython/README.md)** — flashing MicroPython, copying files to
  the board, driver reference, troubleshooting.
- **[micropython/lib/](micropython/lib/)** — the display drivers (`st77xx.py` for all sizes,
  plus `nv3007.py` for the 1.68 / 2.79 inch). They live **here, once**, not inside the size
  folders — every `code/micropython/README.md` next to a `main.py` tells you which files to
  copy and where they are.

## Repository layout

```
TFT-LCD/
├── README.md               # This index
├── tft-lcd/                # TFT-LCD series: 0.96, 1.8, 2.0, 2.4, 2.8, 3.5 inch
│   ├── README.md           #   full guide for the series
│   └── {size}inch/         #   one folder per size (README, test sketch, MicroPython test, adaptation guide)
├── narrow-lcd/             # Narrow LCD series: 1.14, 1.68, 1.9, 2.25, 2.79 inch
│   ├── README.md           #   full guide for the series
│   └── {size}inch/
├── micropython/            # MicroPython setup guide + the shared drivers (lib/)
└── tutorials/              # 11 lessons, Arduino (3.5inch/) and MicroPython (micropython/)
```

## License

MIT License
