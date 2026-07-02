"""
st77xx.py - MicroPython driver for ST7735S / ST7789 / ST7796 SPI TFT-LCDs
(Lonely Binary TFT-LCD kit).

Pure Python, so it runs on the STOCK MicroPython firmware from micropython.org
on both the classic ESP32 and the ESP32-S3 - no custom firmware build needed.

Design note: drawing goes straight to the panel over SPI instead of through a
full-screen buffer in RAM. A full framebuffer would need width x height x 2
bytes (300 KB for the 3.5-inch 320x480 panel), which does not fit in a classic
ESP32's free heap. Direct drawing keeps RAM use tiny at the cost of speed -
fine for text, status screens and test patterns.

Pick the class that matches your display's driver IC:

    Size       Resolution  Class          Extras needed
    0.96 inch  80 x 160    ST7735         xstart=24, bgr=True, invert=False
    1.8 inch   128 x 160   ST7735         flip_x=True, flip_y=True
    2.0 inch   240 x 320   ST7789         (defaults)
    2.4 inch   240 x 320   ST7789         (defaults)
    2.8 inch   240 x 320   ST7789         (defaults)
    3.5 inch   320 x 480   ST7796         bgr=True

Example (2.4 inch on a classic ESP32):

    from machine import Pin, SPI
    import st77xx

    spi = SPI(2, baudrate=40_000_000, sck=Pin(18), mosi=Pin(23), miso=None)
    tft = st77xx.ST7789(spi, 240, 320,
                        dc=Pin(2), cs=Pin(15), rst=Pin(4))
    tft.fill(st77xx.RED)
    tft.text("Hello", 10, 10, st77xx.WHITE, scale=2)

MIT License.
"""

import struct
import time
import framebuf
from machine import Pin
from micropython import const

# ---- ST77xx command set (shared by ST7735S / ST7789 / ST7796) ----
_SWRESET = const(0x01)  # software reset
_SLPOUT = const(0x11)   # exit sleep mode
_NORON = const(0x13)    # normal display mode on
_INVOFF = const(0x20)   # display inversion off
_INVON = const(0x21)    # display inversion on (needed by most IPS panels)
_DISPON = const(0x29)   # display on
_CASET = const(0x2A)    # column address set
_RASET = const(0x2B)    # row address set
_RAMWR = const(0x2C)    # memory write
_MADCTL = const(0x36)   # memory data access control (rotation / color order)
_COLMOD = const(0x3A)   # pixel format (0x55 = 16-bit RGB565)

# MADCTL bits
_MADCTL_MY = const(0x80)   # row order
_MADCTL_MX = const(0x40)   # column order
_MADCTL_MV = const(0x20)   # row/column exchange
_MADCTL_BGR = const(0x08)  # BGR color filter order

# ---- Ready-to-use RGB565 colors ----
BLACK = const(0x0000)
WHITE = const(0xFFFF)
RED = const(0xF800)
GREEN = const(0x07E0)
BLUE = const(0x001F)
YELLOW = const(0xFFE0)
MAGENTA = const(0xF81F)
CYAN = const(0x07FF)


def color565(r, g, b):
    """Pack 8-bit R, G, B (0-255 each) into a 16-bit RGB565 color."""
    return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3)


class ST77xx:
    """Base class - use ST7735 / ST7789 / ST7796 below, not this directly."""

    # Per-controller extra init commands, filled in by subclasses:
    # a tuple of (command, data bytes, delay_ms) entries.
    _INIT = ()
    # Per-controller MADCTL quirk, XORed into every rotation's value
    # (the ST7796 scans mirrored, so its subclass sets MX here).
    _MADCTL_XOR = 0x00

    def __init__(self, spi, width, height, dc, cs, rst=None,
                 rotation=0, bgr=False, invert=True, xstart=0, ystart=0,
                 flip_x=False, flip_y=False):
        """
        spi      - a machine.SPI already configured (mode 0, MOSI + SCK only)
        width    - panel width in pixels at rotation 0 (portrait)
        height   - panel height in pixels at rotation 0
        dc       - machine.Pin for Data/Command (required)
        cs       - machine.Pin for Chip Select (required)
        rst      - machine.Pin for hardware reset, or None if tied high
        rotation - 0..3 (0 = portrait, 1 = 90 degrees, ...)
        bgr      - True if the panel wants BGR color order
                   (symptom of a wrong value: red and blue are swapped)
        invert   - True for IPS panels that need display inversion
                   (symptom of a wrong value: image looks like a photo negative)
        xstart   - column offset of the visible area in controller RAM
        ystart   - row offset (small panels sit in the middle of the RAM)
        flip_x   - True if the picture is mirrored left-right on your panel
        flip_y   - True if the picture is mirrored top-bottom
                   (set both for a panel that shows everything upside-down)
        """
        self.spi = spi
        self.dc = dc
        self.cs = cs
        self.rst = rst
        dc.init(Pin.OUT, value=0)
        cs.init(Pin.OUT, value=1)
        if rst is not None:
            rst.init(Pin.OUT, value=1)

        self._pw = width    # physical (rotation 0) size
        self._ph = height
        self._xs = xstart
        self._ys = ystart
        self.bgr = bgr
        self.invert = invert
        self._madctl_xor = self._MADCTL_XOR
        if flip_x:
            self._madctl_xor ^= _MADCTL_MX
        if flip_y:
            self._madctl_xor ^= _MADCTL_MY

        # Reused chunk buffer for fills (1024 pixels = 2 KB) so big fills
        # don't allocate. _buf_color remembers what pattern is in it.
        self._buf = bytearray(2048)
        self._buf_color = None

        self.rotation = 0
        self.width = width
        self.height = height
        self._xoff = xstart
        self._yoff = ystart

        self.init()
        self.set_rotation(rotation)
        self.fill(BLACK)

    # ---- low-level helpers ----

    def _cmd(self, cmd, data=None, delay=0):
        """Send one command byte, optionally followed by data bytes."""
        self.cs(0)
        self.dc(0)
        self.spi.write(bytes([cmd]))
        if data:
            self.dc(1)
            self.spi.write(data)
        self.cs(1)
        if delay:
            time.sleep_ms(delay)

    def reset(self):
        """Hardware reset via the RST pin (no-op if rst=None)."""
        if self.rst is not None:
            self.rst(1)
            time.sleep_ms(50)
            self.rst(0)
            time.sleep_ms(50)
            self.rst(1)
            time.sleep_ms(150)

    def init(self):
        """Reset and initialize the panel. Called automatically on creation."""
        self.reset()
        self._cmd(_SWRESET, None, 150)
        self._cmd(_SLPOUT, None, 120)
        for cmd, data, delay in self._INIT:
            self._cmd(cmd, data, delay)
        self._cmd(_COLMOD, b"\x55", 10)  # 16-bit RGB565 pixels
        self._cmd(_INVON if self.invert else _INVOFF, None, 10)
        self._cmd(_NORON, None, 10)
        self._cmd(_DISPON, None, 120)

    def set_rotation(self, r):
        """Set rotation 0..3. 0 = portrait (as wired), 1 = 90 deg CW, ..."""
        r &= 3
        madctl = (
            0x00,
            _MADCTL_MV | _MADCTL_MX,
            _MADCTL_MX | _MADCTL_MY,
            _MADCTL_MV | _MADCTL_MY,
        )[r]
        madctl ^= self._madctl_xor
        if self.bgr:
            madctl |= _MADCTL_BGR
        if r & 1:  # landscape: swap width/height and the RAM offsets
            self.width, self.height = self._ph, self._pw
            self._xoff, self._yoff = self._ys, self._xs
        else:
            self.width, self.height = self._pw, self._ph
            self._xoff, self._yoff = self._xs, self._ys
        self.rotation = r
        self._cmd(_MADCTL, bytes([madctl]))

    def _window(self, x0, y0, x1, y1):
        """Set the drawing window and leave the bus open in RAMWR mode.
        The caller must write the pixel data and then set cs(1)."""
        self._cmd(_CASET, struct.pack(">HH", x0 + self._xoff, x1 + self._xoff))
        self._cmd(_RASET, struct.pack(">HH", y0 + self._yoff, y1 + self._yoff))
        self.cs(0)
        self.dc(0)
        self.spi.write(bytes([_RAMWR]))
        self.dc(1)

    def _fill_buf(self, color):
        """Fill the reusable chunk buffer with one RGB565 color."""
        if self._buf_color == color:
            return
        buf = self._buf
        buf[0] = color >> 8
        buf[1] = color & 0xFF
        n = 2
        end = len(buf)
        while n < end:  # doubling copy: 2 -> 4 -> 8 ... bytes
            buf[n:n << 1] = buf[0:n]
            n <<= 1
        self._buf_color = color

    # ---- drawing primitives ----

    def fill_rect(self, x, y, w, h, color):
        """Fill a rectangle. Clipped to the screen."""
        if x < 0:
            w += x
            x = 0
        if y < 0:
            h += y
            y = 0
        if x + w > self.width:
            w = self.width - x
        if y + h > self.height:
            h = self.height - y
        if w <= 0 or h <= 0:
            return
        self._fill_buf(color)
        self._window(x, y, x + w - 1, y + h - 1)
        chunk = len(self._buf) // 2  # pixels per chunk
        mv = memoryview(self._buf)
        n = w * h
        while n > 0:
            c = chunk if n > chunk else n
            self.spi.write(mv[: c * 2])
            n -= c
        self.cs(1)

    def fill(self, color):
        """Fill the whole screen."""
        self.fill_rect(0, 0, self.width, self.height, color)

    def pixel(self, x, y, color):
        """Set a single pixel."""
        if 0 <= x < self.width and 0 <= y < self.height:
            self._window(x, y, x, y)
            self.spi.write(bytes([color >> 8, color & 0xFF]))
            self.cs(1)

    def hline(self, x, y, w, color):
        self.fill_rect(x, y, w, 1, color)

    def vline(self, x, y, h, color):
        self.fill_rect(x, y, 1, h, color)

    def rect(self, x, y, w, h, color):
        """Rectangle outline."""
        self.hline(x, y, w, color)
        self.hline(x, y + h - 1, w, color)
        self.vline(x, y, h, color)
        self.vline(x + w - 1, y, h, color)

    def line(self, x0, y0, x1, y1, color):
        """Line between two points (Bresenham)."""
        if x0 == x1:
            self.vline(x0, min(y0, y1), abs(y1 - y0) + 1, color)
            return
        if y0 == y1:
            self.hline(min(x0, x1), y0, abs(x1 - x0) + 1, color)
            return
        dx = abs(x1 - x0)
        sx = 1 if x0 < x1 else -1
        dy = -abs(y1 - y0)
        sy = 1 if y0 < y1 else -1
        err = dx + dy
        while True:
            self.pixel(x0, y0, color)
            if x0 == x1 and y0 == y1:
                return
            e2 = 2 * err
            if e2 >= dy:
                err += dy
                x0 += sx
            if e2 <= dx:
                err += dx
                y0 += sy

    def circle(self, cx, cy, r, color):
        """Circle outline (midpoint algorithm)."""
        x, y, err = r, 0, 1 - r
        while x >= y:
            for px, py in ((cx + x, cy + y), (cx - x, cy + y),
                           (cx + x, cy - y), (cx - x, cy - y),
                           (cx + y, cy + x), (cx - y, cy + x),
                           (cx + y, cy - x), (cx - y, cy - x)):
                self.pixel(px, py, color)
            y += 1
            if err < 0:
                err += 2 * y + 1
            else:
                x -= 1
                err += 2 * (y - x) + 1

    def fill_circle(self, cx, cy, r, color):
        """Filled circle, drawn as one horizontal span per row."""
        x, y, err = r, 0, 1 - r
        while x >= y:
            self.hline(cx - x, cy + y, 2 * x + 1, color)
            self.hline(cx - x, cy - y, 2 * x + 1, color)
            self.hline(cx - y, cy + x, 2 * y + 1, color)
            self.hline(cx - y, cy - x, 2 * y + 1, color)
            y += 1
            if err < 0:
                err += 2 * y + 1
            else:
                x -= 1
                err += 2 * (y - x) + 1

    def fill_triangle(self, x0, y0, x1, y1, x2, y2, color):
        """Filled triangle, drawn as one horizontal span per row."""
        # sort the three points by y
        if y0 > y1:
            x0, y0, x1, y1 = x1, y1, x0, y0
        if y1 > y2:
            x1, y1, x2, y2 = x2, y2, x1, y1
        if y0 > y1:
            x0, y0, x1, y1 = x1, y1, x0, y0
        if y0 == y2:  # degenerate: all on one row
            xs = min(x0, x1, x2)
            self.hline(xs, y0, max(x0, x1, x2) - xs + 1, color)
            return
        for y in range(y0, y2 + 1):
            # long edge (0 -> 2) intersection
            xa = x0 + (x2 - x0) * (y - y0) // (y2 - y0)
            # short edges (0 -> 1, then 1 -> 2)
            if y < y1:
                xb = x0 + (x1 - x0) * (y - y0) // (y1 - y0) if y1 != y0 else x1
            else:
                xb = x1 + (x2 - x1) * (y - y1) // (y2 - y1) if y2 != y1 else x1
            if xa > xb:
                xa, xb = xb, xa
            self.hline(xa, y, xb - xa + 1, color)

    def blit(self, buf, x, y, w, h):
        """Push a w x h block of big-endian RGB565 pixels (bytes/bytearray)
        to position (x, y). Clipped to the screen."""
        x0 = x if x > 0 else 0
        y0 = y if y > 0 else 0
        x1 = min(x + w, self.width)
        y1 = min(y + h, self.height)
        if x0 >= x1 or y0 >= y1:
            return
        self._window(x0, y0, x1 - 1, y1 - 1)
        mv = memoryview(buf)
        if x0 == x and x1 == x + w:
            # every row fully visible: one big write
            self.spi.write(mv[(y0 - y) * w * 2:(y1 - y) * w * 2])
        else:
            rw = (x1 - x0) * 2
            for row in range(y0 - y, y1 - y):
                s = (row * w + (x0 - x)) * 2
                self.spi.write(mv[s:s + rw])
        self.cs(1)

    def text(self, s, x, y, color, bg=BLACK, scale=1):
        """Draw text with MicroPython's built-in 8x8 font.
        Each character is 8 x 8 pixels times `scale`. The background is
        painted too (bg), because the panel can't be read back over SPI."""
        if not s or scale < 1:
            return
        w = 8 * len(s)
        # Render into a tiny 1-bit framebuffer first (w x 8, 1 byte per column octet)
        mono = bytearray(w)  # MONO_HLSB: w/8 bytes per row * 8 rows
        fb = framebuf.FrameBuffer(mono, w, 8, framebuf.MONO_HLSB)
        fb.text(s, 0, 0, 1)
        # Expand to RGB565 with scaling
        ow = w * scale
        buf = bytearray(ow * 8 * scale * 2)
        chi, clo = color >> 8, color & 0xFF
        bhi, blo = bg >> 8, bg & 0xFF
        rowbytes = ow * 2
        idx = 0
        for row in range(8):
            base = row * (w >> 3)
            linestart = idx
            for col in range(w):
                if mono[base + (col >> 3)] & (0x80 >> (col & 7)):
                    hi, lo = chi, clo
                else:
                    hi, lo = bhi, blo
                for _ in range(scale):
                    buf[idx] = hi
                    buf[idx + 1] = lo
                    idx += 2
            for _ in range(scale - 1):  # repeat the scaled row vertically
                buf[idx:idx + rowbytes] = buf[linestart:linestart + rowbytes]
                idx += rowbytes
        self.blit(buf, x, y, ow, 8 * scale)


class ST7735(ST77xx):
    """ST7735S - 0.96 inch (80x160) and 1.8 inch (128x160) modules.
    Init values are the widely used ST7735S 'R' settings (frame rate, power,
    gamma) shared by Adafruit-ST7735 and Arduino_GFX."""

    _INIT = (
        (0xB1, b"\x01\x2c\x2d", 0),              # FRMCTR1 frame rate, normal mode
        (0xB2, b"\x01\x2c\x2d", 0),              # FRMCTR2 frame rate, idle mode
        (0xB3, b"\x01\x2c\x2d\x01\x2c\x2d", 0),  # FRMCTR3 frame rate, partial mode
        (0xB4, b"\x07", 0),                      # INVCTR no dot inversion
        (0xC0, b"\xa2\x02\x84", 0),              # PWCTR1
        (0xC1, b"\xc5", 0),                      # PWCTR2
        (0xC2, b"\x0a\x00", 0),                  # PWCTR3
        (0xC3, b"\x8a\x2a", 0),                  # PWCTR4
        (0xC4, b"\x8a\xee", 0),                  # PWCTR5
        (0xC5, b"\x0e", 0),                      # VMCTR1 VCOM
        (0xE0, b"\x02\x1c\x07\x12\x37\x32\x29\x2d"
               b"\x29\x25\x2b\x39\x00\x01\x03\x10", 0),  # GMCTRP1 gamma +
        (0xE1, b"\x03\x1d\x07\x06\x2e\x2c\x29\x2d"
               b"\x2e\x2e\x37\x3f\x00\x00\x02\x10", 0),  # GMCTRN1 gamma -
    )


class ST7789(ST77xx):
    """ST7789 - 2.0 / 2.4 / 2.8 inch (240x320) modules.
    Works with its power-on defaults; no extra init needed."""

    _INIT = ()


class ST7796(ST77xx):
    """ST7796 - 3.5 inch (320x480) module.
    Uses the common ST7796 vendor settings (also found in Arduino_GFX and
    LovyanGFX), wrapped in the command-set unlock/lock the chip requires."""

    # The ST7796 scans mirrored in X: without MX the picture (text) appears
    # as a mirror image. This matches Arduino_GFX's rotation-0 value of 0x48.
    _MADCTL_XOR = _MADCTL_MX

    _INIT = (
        (0xF0, b"\xc3", 0),                      # CSCON unlock part 1
        (0xF0, b"\x96", 0),                      # CSCON unlock part 2
        (0xB4, b"\x01", 0),                      # 1-dot inversion
        (0xB6, b"\x80\x02\x3b", 0),              # display function control
        (0xE8, b"\x40\x8a\x00\x00\x29\x19\xa5\x33", 0),  # display output ctrl
        (0xC1, b"\x06", 0),                      # power control 2
        (0xC2, b"\xa7", 0),                      # power control 3
        (0xC5, b"\x18", 0),                      # VCOM
        (0xE0, b"\xf0\x09\x0b\x06\x04\x15\x2f"
               b"\x54\x42\x3c\x17\x14\x18\x1b", 0),      # gamma +
        (0xE1, b"\xe0\x09\x0b\x06\x04\x03\x2b"
               b"\x43\x42\x3b\x16\x14\x17\x1b", 0),      # gamma -
        (0xF0, b"\x3c", 0),                      # CSCON lock part 1
        (0xF0, b"\x69", 0),                      # CSCON lock part 2
    )
