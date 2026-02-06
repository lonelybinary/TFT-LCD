# Lesson 02: Colors

## Course Objectives

Learn how to use colors on a 3.5-inch TFT-LCD display, including predefined colors and setting text colors.

## Key Concepts

### 1. Predefined Colors

Arduino GFX library provides the following predefined color constants:

```cpp
BLACK    // Black
WHITE    // White
RED      // Red
GREEN    // Green
BLUE     // Blue
YELLOW   // Yellow
MAGENTA  // Magenta
CYAN     // Cyan
```

Usage example:
```cpp
gfx->fillScreen(RED);        // Fill screen with red
gfx->setTextColor(WHITE);    // Set text color to white
```

### 2. Fill Screen Color

Use the `fillScreen()` function to fill the entire screen with a specified color:

```cpp
gfx->fillScreen(BLACK);  // Fill screen with black (clear screen)
gfx->fillScreen(RED);    // Fill screen with red
```

### 3. Set Text Color

Use the `setTextColor()` function to set text color:

```cpp
gfx->setTextColor(RED);    // Set text color to red
gfx->setTextColor(WHITE);  // Set text color to white
```

## Code Explanation

### Predefined Color Demo

```cpp
// Fill screen with different colors sequentially
gfx->fillScreen(RED);
delay(2000);
gfx->fillScreen(GREEN);
delay(2000);
// ... other colors
```

### Display Color Names

```cpp
// Display color names in their corresponding colors
gfx->setTextColor(RED);
gfx->setCursor(50, 20);
gfx->println("RED");
```

## Expected Result

1. **Predefined Color Demo**: Display shows red, green, blue, yellow, magenta, cyan, white, black sequentially (each color stays for 2 seconds)
2. **Color Name List**: Display various color names in their corresponding colors on black background

## Extended Exercises

1. **Change Color Order**: Try displaying colors in different order
   ```cpp
   // Try different color order
   gfx->fillScreen(BLUE);
   delay(2000);
   gfx->fillScreen(YELLOW);
   delay(2000);
   ```

2. **Change Text Color**: Try displaying text in different colors
   ```cpp
   gfx->setTextColor(CYAN);
   gfx->setCursor(50, 50);
   gfx->println("CYAN TEXT");
   ```

3. **Combine Usage**: Display text after filling with color
   ```cpp
   gfx->fillScreen(RED);
   gfx->setTextColor(WHITE);
   gfx->setCursor(100, 200);
   gfx->setTextSize(3);
   gfx->println("RED");
   ```

## Important Notes

### IPS Parameter Setting

According to the display specification, the 3.5-inch display is an **IPS TFT-LCD** (IPS display), so the IPS parameter should be set to `true`:

```cpp
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);
```

#### IPS Parameter Differences

**IPS Parameter Function**:
- Controls display initialization command sequence
- Affects color display correctness
- Adapts to different display modes

**`true` (IPS, Normally white)**:
- Suitable for **IPS displays** or **Normally white mode** displays (display white when no signal)
- Usually better viewing angle and more accurate colors
- 3.5-inch display is IPS, should use `true`
- If set to `false`, may cause color inversion or display abnormalities

**How to Determine Which Value to Use**:
1. **Check Specification**: If it says "IPS" or "Normally white", use `true`; if it says "Normally black", use `false`
2. **Test Method**: If colors are incorrect, try switching `true`/`false` to test
3. **Observe Effect**: With correct setting, colors should display normally (red is red, not blue)

**Common Display IPS Settings**:
- 0.96-inch (ST7735S, Normally black): `false`
- 2.0-inch (ST7789, IPS): `true`
- 2.4-inch (ST7789, IPS): `true`
- 2.8-inch (ST7789, IPS): `true`
- 3.5-inch (ST7796, IPS): `true` ✅

## Frequently Asked Questions

**Q: Why do colors look incorrect?**
- Check if IPS parameter is correctly set to `true` (for 3.5-inch display)
- Confirm using `Arduino_ST7796` class

**Q: Can I store color values?**
- Yes, use `uint16_t` type to store color values
- Example: `uint16_t myColor = RED;`

## Next Step

After completing this lesson, you can continue with:
- [Lesson 03: Text Size](../Lesson03_TextSize/README.md) - Learn text size control
