"""
nv3007.py - MicroPython driver for the NV3007 SPI TFT-LCDs in the Lonely
Binary Narrow TFT LCD Collection (1.68 inch and 2.79 inch, 142 x 428).

Needs st77xx.py next to it: the NV3007 speaks the same command set as the
ST77xx family for drawing (CASET / RASET / RAMWR / MADCTL), so this file only
supplies the NV3007-specific power-up sequence and reuses every drawing
primitive (fill, text, lines, blit, ...) from st77xx.ST77xx.

Copy BOTH files to the board:
    mpremote cp micropython/lib/st77xx.py :
    mpremote cp micropython/lib/nv3007.py :

The two sizes share the chip but not the settings - each has its own vendor
init table (voltage / gamma), taken from Arduino_GFX's Arduino_NV3007 driver
(nv3007_init_operations for the 1.68 inch, nv3007_279_init_operations for the
2.79 inch), which is what the Arduino sketches in this repo use.

Example (1.68 inch on a classic ESP32, landscape):

    from machine import Pin, SPI
    import st77xx, nv3007

    spi = SPI(2, baudrate=8_000_000, sck=Pin(18), mosi=Pin(23), miso=None)
    tft = nv3007.NV3007_168(spi, dc=Pin(2), cs=Pin(15), rst=Pin(4),
                            rotation=1, xstart=14, ystart=0)
    tft.fill(st77xx.RED)
    tft.text("Hello", 10, 10, st77xx.WHITE, scale=2)

MIT License.
"""

import st77xx

# The private const() names in st77xx are compiled away and cannot be
# imported, so the few commands used here are spelled out again.
_SLPOUT = 0x11
_INVOFF = 0x20
_INVON = 0x21
_DISPON = 0x29

# NV3007 panels are 142 x 428 at rotation 0 (portrait, as wired).
WIDTH = 142
HEIGHT = 428


class NV3007(st77xx.ST77xx):
    """Base NV3007 class. Use NV3007_168 or NV3007_279 below, which pick the
    right vendor init table; or pass your own via the _INIT class attribute.

    Constructor arguments are the same as st77xx.ST77xx except that width and
    height default to 142 x 428 and invert defaults to False (these are not
    IPS-inverted panels)."""

    def __init__(self, spi, dc, cs, rst=None, width=WIDTH, height=HEIGHT,
                 rotation=0, bgr=False, invert=False, xstart=0, ystart=0,
                 flip_x=False, flip_y=False):
        super().__init__(spi, width, height, dc, cs, rst,
                         rotation=rotation, bgr=bgr, invert=invert,
                         xstart=xstart, ystart=ystart,
                         flip_x=flip_x, flip_y=flip_y)

    def init(self):
        """NV3007 power-up. Unlike the ST77xx path this sends NO software
        reset and no NORON: the hardware reset plus the vendor table is the
        whole sequence (the table itself contains COLMOD, SLPOUT and DISPON),
        matching what Arduino_GFX does for this chip."""
        self.reset()
        for cmd, data, delay in self._INIT:
            self._cmd(cmd, data, delay)
        self._cmd(_INVON if self.invert else _INVOFF, None, 10)


class NV3007_168(NV3007):
    """1.68 inch NV3007 (142 x 428). Vendor init from Arduino_GFX
    nv3007_init_operations."""

    _INIT = (
        (0xFF, b"\xa5", 0),                      # unlock vendor registers
        (_SLPOUT, None, 120),
        (0xFF, b"\xa5", 0),
        (0x9A, b"\x08", 0),
        (0x9B, b"\x08", 0),
        (0x9C, b"\xb0", 0),
        (0x9D, b"\x17", 0),
        (0x9E, b"\xc2", 0),
        (0x8F, b"\x22\x04", 0),
        (0x84, b"\x90", 0),
        (0x83, b"\x7b", 0),
        (0x85, b"\x4f", 0),
        # gamma
        (0x6E, b"\x0f", 0), (0x7E, b"\x0f", 0),
        (0x60, b"\x00", 0), (0x70, b"\x00", 0),
        (0x6D, b"\x39", 0), (0x7D, b"\x31", 0),
        (0x61, b"\x0a", 0), (0x71, b"\x0a", 0),
        (0x6C, b"\x35", 0), (0x7C, b"\x29", 0),
        (0x62, b"\x0f", 0), (0x72, b"\x0f", 0),
        (0x68, b"\x4f", 0), (0x78, b"\x45", 0),
        (0x66, b"\x33", 0), (0x76, b"\x33", 0),
        (0x6B, b"\x14", 0), (0x7B, b"\x14", 0),
        (0x63, b"\x09", 0), (0x73, b"\x09", 0),
        (0x6A, b"\x13", 0), (0x7A, b"\x16", 0),
        (0x64, b"\x08", 0), (0x74, b"\x08", 0),
        (0x69, b"\x07", 0), (0x79, b"\x0d", 0),
        (0x65, b"\x05", 0), (0x75, b"\x05", 0),
        (0x67, b"\x33", 0), (0x77, b"\x33", 0),
        (0x6F, b"\x00", 0), (0x7F, b"\x00", 0),
        (0x50, b"\x00", 0),
        (0x52, b"\xd6", 0),
        (0x53, b"\x04", 0),
        (0x54, b"\x04", 0),
        (0x55, b"\x1b", 0),
        (0x56, b"\x1b", 0),
        (0xA0, b"\x2a\x24\x00", 0),
        (0xA1, b"\x84", 0),
        (0xA2, b"\x85", 0),
        (0xA8, b"\x34", 0),
        (0xA9, b"\x80", 0),
        (0xAA, b"\x73", 0),
        (0xAB, b"\x03\x61", 0),
        (0xAC, b"\x03\x65", 0),
        (0xAD, b"\x03\x60", 0),
        (0xAE, b"\x03\x64", 0),
        (0xB9, b"\x82", 0),
        (0xBA, b"\x83", 0),
        (0xBB, b"\x80", 0),
        (0xBC, b"\x81", 0),
        (0xBD, b"\x02", 0),
        (0xBE, b"\x01", 0),
        (0xBF, b"\x04", 0),
        (0xC0, b"\x03", 0),
        (0xC4, b"\x33", 0),
        (0xC5, b"\x80", 0),
        (0xC6, b"\x73", 0),
        (0xC7, b"\x00", 0),
        (0xC8, b"\x33\x33", 0),
        (0xC9, b"\x5b", 0),
        (0xCA, b"\x5a", 0),
        (0xCB, b"\x5d", 0),
        (0xCC, b"\x5c", 0),
        (0xCD, b"\x33\x33", 0),
        (0xCE, b"\x5f", 0),
        (0xCF, b"\x5e", 0),
        (0xD0, b"\x61", 0),
        (0xD1, b"\x60", 0),
        (0xB0, b"\x3a\x3a\x00\x00", 0),
        (0xB6, b"\x32", 0),
        (0xB7, b"\x80", 0),
        (0xB8, b"\x73", 0),
        (0xE0, b"\x00", 0),
        (0xE1, b"\x03\x0f", 0),
        (0xE2, b"\x04", 0),
        (0xE3, b"\x01", 0),
        (0xE4, b"\x0e", 0),
        (0xE5, b"\x01", 0),
        (0xE6, b"\x19", 0),
        (0xE7, b"\x10", 0),
        (0xE8, b"\x10", 0),
        (0xE9, b"\x21", 0),
        (0xEA, b"\x12", 0),
        (0xEB, b"\xd0", 0),
        (0xEC, b"\x04", 0),
        (0xED, b"\x07", 0),
        (0xEE, b"\x07", 0),
        (0xEF, b"\x09", 0),
        (0xF0, b"\xd0", 0),
        (0xF1, b"\x0e", 0),
        (0xF9, b"\x56", 0),
        (0xF2, b"\x26\x1b\x0b\x20", 0),
        (0xEC, b"\x04", 0),
        (0x35, b"\x00", 0),                      # tearing effect line on
        (0x44, b"\x00\x10", 0),                  # tear scanline
        (0x46, b"\x10", 0),
        (0xFF, b"\x00", 0),                      # lock vendor registers
        (0x3A, b"\x05", 0),                      # COLMOD 16-bit RGB565
        (_SLPOUT, None, 200),
        (_DISPON, None, 150),
    )


class NV3007_279(NV3007):
    """2.79 inch NV3007 (142 x 428). Same chip as the 1.68 inch but different
    voltage / gamma values. Vendor init from Arduino_GFX
    nv3007_279_init_operations."""

    _INIT = (
        (0xFF, b"\xa5", 0),                      # unlock vendor registers
        (0x9A, b"\x08", 0),
        (0x9B, b"\x08", 0),
        (0x9C, b"\xb0", 0),
        (0x9D, b"\x16", 0),
        (0x9E, b"\xc4", 0),
        (0x8F, b"\x55\x04", 0),
        (0x84, b"\x90", 0),
        (0x83, b"\x7b", 0),
        (0x85, b"\x33", 0),
        # gamma
        (0x60, b"\x00", 0), (0x70, b"\x00", 0),
        (0x61, b"\x02", 0), (0x71, b"\x02", 0),
        (0x62, b"\x04", 0), (0x72, b"\x04", 0),
        (0x6C, b"\x29", 0), (0x7C, b"\x29", 0),
        (0x6D, b"\x31", 0), (0x7D, b"\x31", 0),
        (0x6E, b"\x0f", 0), (0x7E, b"\x0f", 0),
        (0x66, b"\x21", 0), (0x76, b"\x21", 0),
        (0x68, b"\x3a", 0), (0x78, b"\x3a", 0),
        (0x63, b"\x07", 0), (0x73, b"\x07", 0),
        (0x64, b"\x05", 0), (0x74, b"\x05", 0),
        (0x65, b"\x02", 0), (0x75, b"\x02", 0),
        (0x67, b"\x23", 0), (0x77, b"\x23", 0),
        (0x69, b"\x08", 0), (0x79, b"\x08", 0),
        (0x6A, b"\x13", 0), (0x7A, b"\x13", 0),
        (0x6B, b"\x13", 0), (0x7B, b"\x13", 0),
        (0x6F, b"\x00", 0), (0x7F, b"\x00", 0),
        (0x50, b"\x00", 0),
        (0x52, b"\xd6", 0),
        (0x53, b"\x08", 0),
        (0x54, b"\x08", 0),
        (0x55, b"\x1e", 0),
        (0x56, b"\x1c", 0),
        (0xA0, b"\x2b\x24\x00", 0),
        (0xA1, b"\x87", 0),
        (0xA2, b"\x86", 0),
        (0xA5, b"\x00", 0),
        (0xA6, b"\x00", 0),
        (0xA7, b"\x00", 0),
        (0xA8, b"\x36", 0),
        (0xA9, b"\x7e", 0),
        (0xAA, b"\x7e", 0),
        (0xB9, b"\x85", 0),
        (0xBA, b"\x84", 0),
        (0xBB, b"\x83", 0),
        (0xBC, b"\x82", 0),
        (0xBD, b"\x81", 0),
        (0xBE, b"\x80", 0),
        (0xBF, b"\x01", 0),
        (0xC0, b"\x02", 0),
        (0xC1, b"\x00", 0),
        (0xC2, b"\x00", 0),
        (0xC3, b"\x00", 0),
        (0xC4, b"\x33", 0),
        (0xC5, b"\x7e", 0),
        (0xC6, b"\x7e", 0),
        (0xC8, b"\x33\x33", 0),
        (0xC9, b"\x68", 0),
        (0xCA, b"\x69", 0),
        (0xCB, b"\x6a", 0),
        (0xCC, b"\x6b", 0),
        (0xCD, b"\x33\x33", 0),
        (0xCE, b"\x6c", 0),
        (0xCF, b"\x6d", 0),
        (0xD0, b"\x6e", 0),
        (0xD1, b"\x6f", 0),
        (0xAB, b"\x03\x67", 0),
        (0xAC, b"\x03\x6b", 0),
        (0xAD, b"\x03\x68", 0),
        (0xAE, b"\x03\x6c", 0),
        (0xB3, b"\x00", 0),
        (0xB4, b"\x00", 0),
        (0xB5, b"\x00", 0),
        (0xB6, b"\x32", 0),
        (0xB7, b"\x7e", 0),
        (0xB8, b"\x7e", 0),
        (0xE0, b"\x00", 0),
        (0xE1, b"\x03\x0f", 0),
        (0xE2, b"\x04", 0),
        (0xE3, b"\x01", 0),
        (0xE4, b"\x0e", 0),
        (0xE5, b"\x01", 0),
        (0xE6, b"\x19", 0),
        (0xE7, b"\x10", 0),
        (0xE8, b"\x10", 0),
        (0xEA, b"\x12", 0),
        (0xEB, b"\xd0", 0),
        (0xEC, b"\x04", 0),
        (0xED, b"\x07", 0),
        (0xEE, b"\x07", 0),
        (0xEF, b"\x09", 0),
        (0xF0, b"\xd0", 0),
        (0xF1, b"\x0e", 0),
        (0xF9, b"\x17", 0),
        (0xF2, b"\x2c\x1b\x0b\x20", 0),
        (0xE9, b"\x29", 0),
        (0xEC, b"\x04", 0),
        (0x35, b"\x00", 0),                      # tearing effect line on
        (0x44, b"\x00\x10", 0),                  # tear scanline
        (0x46, b"\x10", 0),
        (0xFF, b"\x00", 0),                      # lock vendor registers
        (0x3A, b"\x05", 0),                      # COLMOD 16-bit RGB565
        (_SLPOUT, None, 120),
        (_DISPON, None, 0),
    )
