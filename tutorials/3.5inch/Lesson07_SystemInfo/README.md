# Lesson 07: System Info Display

## Course Objectives

Put everything so far together to build a real **system-info screen**. Along the way you'll
learn to make reusable helper functions and lay information out clearly.

## Key Concepts

### 1. Reusable UI pieces

Instead of repeating the same drawing code, we wrap it in small **helper functions** and
call them whenever we need that piece.

#### Label
A bit of text on a colored background, great for showing status:

```cpp
drawLabel("ONLINE", 150, 95, GREEN, BLACK, 2);
```

#### Progress bar
Shows a percentage as a filling bar:

```cpp
drawProgressBar(150, 220, 200, 20, 75, WHITE, GREEN);
```

#### Separator
A line that divides sections of the screen:

```cpp
drawSeparator(60, CYAN);
```

### 2. Laying out information

#### Visual hierarchy
- **Title** at the top — bigger font, eye-catching color.
- **Main content** in the middle.
- **Status** at the bottom.

#### Using color with purpose
- **Titles**: a standout color like `YELLOW`.
- **Separators**: a calmer color like `CYAN`.
- **Status**: green for good/online, gray for weak/inactive.

### 3. Status indicators

#### Signal-strength bars
Draw a row of bars of increasing height to show signal strength. This also shows how to make
your own color with `color565(r, g, b)`:

```cpp
for (int i = 0; i < 4; i++) {
  int barHeight = (i + 1) * 8;
  uint16_t color = (i < 3) ? GREEN : gfx->color565(128, 128, 128);  // gray for the last bar
  gfx->fillRect(150 + i * 12, 280 + (20 - barHeight), 10, barHeight, color);
}
```

## Code Explanation

### The helper functions

```cpp
// A text label on a colored background
void drawLabel(const char* text, int x, int y, uint16_t bgColor, uint16_t textColor, int textSize = 2) {
  int textWidth = strlen(text) * 6 * textSize;
  int textHeight = 8 * textSize;
  gfx->fillRect(x, y, textWidth + 8, textHeight + 4, bgColor);  // background
  gfx->setTextColor(textColor);
  gfx->setTextSize(textSize);
  gfx->setCursor(x + 4, y + 4);  // small padding inside
  gfx->println(text);
}

// A progress bar: outlined frame with a filled portion
void drawProgressBar(int x, int y, int width, int height, int percent, uint16_t bgColor, uint16_t fillColor) {
  gfx->drawRect(x, y, width, height, bgColor);
  int fillWidth = (width * percent) / 100;  // how far to fill
  if (fillWidth > 0) {
    gfx->fillRect(x + 2, y + 2, fillWidth - 4, height - 4, fillColor);
  }
}
```

### Putting the screen together

```cpp
// Title
drawCenteredText("SYSTEM INFO", 20, YELLOW, 2);

// Separator
drawSeparator(60, CYAN);

// Status label
drawLabel("ONLINE", 150, 95, GREEN, BLACK, 2);

// Progress bar at 75%
drawProgressBar(150, 220, 200, 20, 75, WHITE, GREEN);
```

## Expected Result

A system-info screen showing:
- System status (online/offline)
- A temperature reading
- A battery level (as a progress bar)
- Signal strength (the row of bars)

## Extended Exercises

1. **Add more info rows** — memory usage, CPU usage, network status.

2. **Refresh the data** instead of showing fixed numbers:
   ```cpp
   void updateSystemInfo() {
     // re-read temperature, battery, etc., then redraw
   }
   ```

3. **Polish the layout** — tweak spacing, add small icons, refine the colors.

## Frequently Asked Questions

**Q: How do I make a custom color?**
- Use `gfx->color565(r, g, b)`, where `r`, `g`, and `b` each range 0–255 (like normal RGB).
- For example, `gfx->color565(128, 128, 128)` makes gray. The library packs these into the
  16-bit RGB565 format described in Lesson 2 for you.

**Q: How do I change the progress bar's width?**
- Pass a different `width` to `drawProgressBar`.
- The fill is calculated from that width, so it scales automatically.

## Next Step

- [Lesson 08: Menu Interface](../Lesson08_Menu/README.md) — build a selectable menu.
