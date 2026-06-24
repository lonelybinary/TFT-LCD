# Lesson 02: Colors

## Course Objectives

Learn to use color on the 3.5-inch TFT-LCD display — filling the whole screen with a color
and choosing the color of your text.

## Key Concepts

### 1. The built-in colors

The Arduino GFX library gives you these ready-made color names. You can use them anywhere a
color is expected:

```cpp
BLACK
WHITE
RED
GREEN
BLUE
YELLOW
MAGENTA
CYAN
```

Example:
```cpp
gfx->fillScreen(RED);      // Paint the whole screen red
gfx->setTextColor(WHITE);  // Make text white
```

### 2. Filling the screen

`fillScreen()` paints the entire display one color. It's also the easiest way to "clear" the
screen before drawing something new:

```cpp
gfx->fillScreen(BLACK);  // Clear to black
gfx->fillScreen(RED);    // Paint everything red
```

### 3. Setting the text color

`setTextColor()` sets the color of the text you print next:

```cpp
gfx->setTextColor(RED);
gfx->setTextColor(WHITE);
```

## Code Explanation

### Cycling through colors

This loops through several colors, holding each one on screen for 2 seconds:

```cpp
gfx->fillScreen(RED);
delay(2000);
gfx->fillScreen(GREEN);
delay(2000);
// ... and so on
```

### Showing the color names

Here each color name is printed in its matching color:

```cpp
gfx->setTextColor(RED);
gfx->setCursor(50, 20);
gfx->println("RED");
```

## Expected Result

1. **Color cycle**: the screen fills with red, green, blue, yellow, magenta, cyan, white,
   and black in turn (each for 2 seconds).
2. **Color list**: the color names appear on a black background, each drawn in its own color.

## Extended Exercises

1. **Change the order** the colors appear in:
   ```cpp
   gfx->fillScreen(BLUE);
   delay(2000);
   gfx->fillScreen(YELLOW);
   delay(2000);
   ```

2. **Print text in a different color**:
   ```cpp
   gfx->setTextColor(CYAN);
   gfx->setCursor(50, 50);
   gfx->println("CYAN TEXT");
   ```

3. **Combine a fill and text** — fill the screen, then write on top:
   ```cpp
   gfx->fillScreen(RED);
   gfx->setTextColor(WHITE);
   gfx->setCursor(100, 200);
   gfx->setTextSize(3);
   gfx->println("RED");
   ```

## Going Deeper: How colors are stored

You don't have to memorize this, but it's good to know why the screen is called "16-bit".

Each color is stored as a 16-bit number in a format called **RGB565** — 5 bits for red,
6 for green, 5 for blue. The built-in names like `RED` are just convenient shortcuts for
these numbers. You can save a color in a variable to reuse it:

```cpp
uint16_t myColor = RED;     // Store a color
gfx->setTextColor(myColor); // Use it later
```

And you can mix your own color with `color565(r, g, b)` (we use this in later lessons):

```cpp
uint16_t orange = gfx->color565(255, 128, 0);  // r, g, b each 0–255
```

### A note on the IPS setting

This panel is IPS, so the sketch creates the display with the IPS option set to `true`:

```cpp
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);
```

You don't need to change this. It just tells the driver the correct startup sequence so
colors come out right. If red ever shows up as blue (colors look inverted), this setting is
the first thing to check.

## Frequently Asked Questions

**Q: Why do the colors look wrong?**
- Make sure the IPS option is set to `true` for this 3.5-inch panel.
- Confirm you're using the `Arduino_ST7796` driver class.

**Q: Can I save a color in a variable?**
- Yes. Colors are `uint16_t` values, so: `uint16_t myColor = RED;`

## Next Step

- [Lesson 03: Text Size](../Lesson03_TextSize/README.md) — learn to make text bigger and smaller.
