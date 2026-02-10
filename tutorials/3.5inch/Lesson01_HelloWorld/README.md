# Lesson 01: Hello World

## Course Objectives

Learn how to display text on a 3.5-inch TFT-LCD screen, the first step in using the display.

## Key Concepts

### 1. Display Initialization

Before displaying any content, you need to initialize the display:

```cpp
// Initialize backlight (On/Off only)
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);  // ON

// Reset display
pinMode(TFT_RST, OUTPUT);
digitalWrite(TFT_RST, LOW);
delay(10);
digitalWrite(TFT_RST, HIGH);
delay(120);

// Initialize LCD
if (!gfx->begin()) {
    Serial.println("LCD initialization failed!");
    while (1);
}
```

**Backlight Control Notes**:
- 3.5-inch: On/Off only, `digitalWrite(TFT_BACKLIGHT, HIGH)`=ON (0.96-inch: LOW=ON)
- Use `pinMode(TFT_BACKLIGHT, OUTPUT)` and `digitalWrite()`, no brightness level

### 2. Set Text Color

Use the `setTextColor()` function to set text color:

```cpp
gfx->setTextColor(WHITE);  // Set text color to white
```

Common predefined colors:
- `BLACK` - Black
- `WHITE` - White
- `RED` - Red
- `GREEN` - Green
- `BLUE` - Blue
- `YELLOW` - Yellow
- `MAGENTA` - Magenta
- `CYAN` - Cyan

### 3. Set Cursor Position

Use `setCursor(x, y)` to set text display position:

```cpp
gfx->setCursor(50, 200);  // x=50, y=200
```

**Coordinate System Notes**:
- Origin (0, 0) is at the top-left corner
- X-axis increases to the right (0 to 319)
- Y-axis increases downward (0 to 479)
- 3.5-inch display resolution: 320x480 pixels

### 4. Set Text Size

Use `setTextSize()` to set text size:

```cpp
gfx->setTextSize(3);  // Set text size to 3 (3.5-inch display is large, suitable for larger fonts)
```

### 5. Display Text

Use `println()` or `print()` to display text:

```cpp
gfx->println("Hello World");  // Display text with newline
gfx->print("Hello");          // Display text without newline
```

## Code Explanation

Core parts of this lesson's code:

```cpp
// Set text color to white
gfx->setTextColor(WHITE);

// Set cursor position to (50, 200)
gfx->setCursor(50, 200);

// Set text size
gfx->setTextSize(3);

// Display "Hello World"
gfx->println("Hello World");
```

## Expected Result

After uploading the code, the display should show:
- Black background
- Large white text "Hello World" displayed in the center area of the screen

## Extended Exercises

1. **Change Text Position**: Try displaying text at different positions
   ```cpp
   gfx->setCursor(100, 100);  // Try different coordinates
   ```

2. **Change Text Color**: Try using different colors
   ```cpp
   gfx->setTextColor(RED);  // Try red
   gfx->setTextColor(GREEN);  // Try green
   ```

3. **Change Text Size**: Try different text sizes
   ```cpp
   gfx->setTextSize(1);  // Small
   gfx->setTextSize(2);  // Medium
   gfx->setTextSize(4);  // Large
   ```

4. **Display Multiple Lines**: Try displaying multiple lines of text
   ```cpp
   gfx->setCursor(50, 100);
   gfx->println("Line 1");
   gfx->setCursor(50, 150);
   gfx->println("Line 2");
   ```

5. **Backlight On/Off**: Turn backlight off when not needed to save power
   ```cpp
   digitalWrite(TFT_BACKLIGHT, LOW);   // OFF
   digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
   ```

## Frequently Asked Questions

**Q: Display shows nothing?**
- Check if backlight pinMode and digitalWrite are correct
- Check if hardware connections are correct
- Check serial output for error messages

**Q: Text position is incorrect?**
- Confirm coordinate values are within screen range (x: 0-319, y: 0-479)
- Note that coordinate origin is at top-left corner

**Q: Text color is incorrect?**
- Confirm correct color constants are used
- Check if text color is set before displaying

**Q: Backlight is not on?**
- Check if `digitalWrite(TFT_BACKLIGHT, HIGH)` has been executed (0.96-inch: use LOW)
- Check if GPIO 41 connection is correct

## Next Step

After completing this lesson, you can continue with:
- [Lesson 02: Colors](../Lesson02_Colors/README.md) - Learn more about color usage
