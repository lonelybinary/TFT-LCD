# 1.14-inch Display Adaptation Guide

This guide provides detailed instructions on how to adapt 3.5-inch tutorial code to the
1.14-inch display of the Narrow TFT LCD Collection.

## Display Specifications

| Parameter | Value | Description |
|-----------|-------|-------------|
| **Display Size** | 1.14 inch | Narrow TFT LCD Collection |
| **Driver IC** | ST7789 | Use `Arduino_ST7789` class |
| **Resolution** | 135 x 240 | As wired (portrait) |
| **Working Resolution** | 240 x 135 | What the examples use (rotation 1, landscape) |
| **IPS Parameter** | `true` | Wrong value = colors look inverted |
| **Column Offset 1** | 52 | Active at rotation 0/3 |
| **Row Offset 1** | 40 | Active at rotation 1/4 — **X offset in the examples** |
| **Column Offset 2** | 53 | Active at rotation 1/2 — **Y offset in the examples** |
| **Row Offset 2** | 40 | Active at rotation 2/6 |
| **SPI Clock** | 8 MHz | Tested value |
| **Backlight Control** | On/Off (Active Low) | `digitalWrite(BLK, LOW)`=ON, `HIGH`=OFF |
| **Color Mode** | RGB565 | 16-bit color depth |

## Key Differences

### 1. Orientation Difference (Important!)
- **3.5-inch tutorials**: rotation 0, portrait, 320 x 480
- **1.14-inch**: rotation **1**, landscape, 240 x 135

This is the biggest difference and the one that trips people up. The tutorials assume a
portrait screen. This panel is a narrow strip: only 135 pixels across as wired, which is
too narrow for most of the tutorial layouts, so the examples rotate it.

**Everywhere the tutorial says "width" you now have 240, and "height" is 135.**

### 2. Resolution Difference
- **3.5-inch**: 320 x 480 pixels
- **1.14-inch**: 240 x 135 pixels (landscape)
- **Ratio**: Width approximately 0.75x, Height approximately 0.281x

### 3. Backlight Control Difference (Important!)
- **3.5-inch**: On/Off (Active High), `digitalWrite(TFT_BACKLIGHT, HIGH)`=ON
- **1.14-inch**: On/Off (Active **Low**), `digitalWrite(TFT_BACKLIGHT, LOW)`=ON

### 4. Offset Difference
- **3.5-inch**: Offset `0, 0, 0, 0`
- **1.14-inch**: Offset `52, 40, 53, 40`

Because the examples use rotation 1, the two values that actually take effect are
**row offset 1 (40)** for X and **col offset 2 (53)** for Y. Changing col offset 1
has no effect at this rotation.

## Code Modification Steps

### Step 1: Modify LCD Object Initialization

**3.5-inch (Tutorial Default)**:
```cpp
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);
```

**1.14-inch Adaptation**:
```cpp
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 1, true /* IPS */, 135, 240, 52, 40, 53, 40);
```

**Modification Notes**:
1. Driver class: `Arduino_ST7796` → `Arduino_ST7789`
2. Rotation: `0` → `1` (landscape)
3. IPS parameter: `true` → `true`
4. Resolution: `320, 480` → `135, 240`
5. Offset: `0, 0, 0, 0` → `52, 40, 53, 40`
6. SPI clock: call `gfx->begin(8000000)` instead of `gfx->begin()`

### Step 2: Modify Backlight Control (Important!)

**3.5-inch (On/Off, Active High)**:
```cpp
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
```

**1.14-inch (On/Off, Active Low)**:
```cpp
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, LOW);   // ON
```

If you copy a tutorial sketch across and the screen stays dark, this is the first line to check.

### Step 3: Adjust Coordinates and Dimensions

#### Coordinate Conversion Formula

```
new_x = old_x * 240 / 320    (about 0.75x)
new_y = old_y * 135 / 480    (about 0.281x)
```

#### Coordinate Conversion Examples

| 3.5-inch | 1.14-inch | Note |
|----------|-------------|------|
| `(10, 10)` | `(8, 3)` | top-left corner |
| `(160, 240)` | `(120, 67)` | screen centre |
| `(300, 460)` | `(225, 129)` | bottom-right area |

#### Dimension Conversion Examples

| 3.5-inch | 1.14-inch |
|----------|-------------|
| `fillRect(0, 0, 320, 100)` | `fillRect(0, 0, 240, 28)` |
| `fillCircle(160, 240, 50)` | `fillCircle(120, 67, 14)` |

Better still, use `gfx->width()` and `gfx->height()` instead of literal numbers — then the
same code works on every size in the kit.

### Step 4: Adjust Text Size

The built-in font is 6 x 8 pixels at `setTextSize(1)`.

| Text size | Pixel height | Characters across 240 px | Suitable for 1.14 inch? |
|-----------|--------------|--------------------------|---------------------------|
| 1 | 8 | 40 | yes |
| 2 | 16 | 20 | yes |
| 3 | 24 | 13 | yes |
| 4 | 32 | 10 | ok for a single heading |

With only **135 pixels of height**, you can fit about **13 lines** of size-1 text.
Plan the layout around that before porting a tutorial screen.

## Special Notes

### 1. Offset Explanation

The offsets tell the driver where the visible glass sits inside the controller's larger internal
memory. Wrong values show up as content cut off at one edge with a blank or noisy band at the
opposite edge — not as a stretched picture.

Remember: at rotation 1 only **row offset 1** and **col offset 2** are used.

### 2. Display Size Limitations

- The screen is 135 pixels tall in landscape. Long tutorial layouts will need trimming.
- Center text with `(gfx->width() - textWidth) / 2` rather than hard-coded x positions.
- The tutorials' multi-line status screens may need a smaller text size to fit.

### 3. Center Display Calculation

```cpp
int textWidth = strlen(text) * 6 * textSize;
int textX = (gfx->width() - textWidth) / 2;
int textY = (gfx->height() - 8 * textSize) / 2;
```

## Frequently Asked Questions

### Q1: Display doesn't light up?
- Check the backlight line is `LOW`, not `HIGH` — this collection is active low.
- Check **DC** and **RST** wiring.
- Confirm 3.3V power, never 5V.

### Q2: Display position offset?
- Adjust **row offset 1** (X) and **col offset 2** (Y). The other two do nothing at rotation 1.
- Move in steps of 1–2 pixels.

### Q3: Text not fully displayed?
- The screen is only 135 px tall in landscape — reduce `setTextSize()` or shorten the string.
- Check you are not drawing past `gfx->width()` (240).

### Q4: Colors look inverted?
- That is the IPS parameter. This panel needs `true`.

### Q5: How do I know the offset is correct?
- Draw a 1-pixel rectangle around the whole screen:
  `gfx->drawRect(0, 0, gfx->width(), gfx->height(), WHITE);`
- All four sides should be visible with an even margin. A missing side means the picture runs
  off that edge.

## Quick Checklist

- [ ] Driver class changed to `Arduino_ST7789`
- [ ] Rotation set to 1 (landscape)
- [ ] Resolution set to 135 x 240
- [ ] Offsets set to 52, 40, 53, 40
- [ ] IPS parameter set to `true`
- [ ] Backlight set to **LOW = ON**
- [ ] SPI clock set to 8 MHz
- [ ] Coordinates scaled for 240 x 135
- [ ] Text size checked against the 135-pixel height

## Reference Resources

- [Narrow LCD series README](../README.md) — full setup steps
- [This size's README](README.md) — specs and wiring
- [3.5-inch tutorials](../../tutorials/3.5inch/README.md) — the lessons being adapted
