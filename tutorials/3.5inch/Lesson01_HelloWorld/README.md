# Lesson 01: Hello World

## Course Objectives

Show your very first text on the 3.5-inch TFT-LCD screen. This is the "hello world" of
displays — once it works, you know your wiring and software are correct, and you're ready
for everything else.

## Key Concepts

### 1. Initializing the display

Before you can draw anything, the display needs to be set up. The sketch does three things:
turn on the backlight, reset the display chip, then start the graphics library.

```cpp
// Turn on the backlight (on/off only — no dimming)
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);  // HIGH = ON on the 3.5-inch panel

// Reset the display
pinMode(TFT_RST, OUTPUT);
digitalWrite(TFT_RST, LOW);
delay(10);
digitalWrite(TFT_RST, HIGH);
delay(120);

// Start the graphics library
if (!gfx->begin()) {
    Serial.println("LCD initialization failed!");
    while (1);
}
```

**About the backlight:**
- It's simple on/off — there's no brightness control.
- On the 3.5-inch panel, `HIGH` turns the backlight on. (The 0.96-inch module is the
  opposite: `LOW` turns it on.)
- You don't need to know the exact GPIO number — the sketch picks it automatically based on
  your board. It's referred to in code as `TFT_BACKLIGHT` (GPIO 41 on ESP32-S3, GPIO 32 on
  classic ESP32).

### 2. Setting the text color

`setTextColor()` chooses the color the next text will be drawn in:

```cpp
gfx->setTextColor(WHITE);  // White text
```

These color names are built in and ready to use:

- `BLACK`
- `WHITE`
- `RED`
- `GREEN`
- `BLUE`
- `YELLOW`
- `MAGENTA`
- `CYAN`

### 3. Setting the cursor position

The **cursor** is where the next text will start. `setCursor(x, y)` moves it:

```cpp
gfx->setCursor(50, 200);  // Start text at x=50, y=200
```

**How coordinates work:**
- The origin `(0, 0)` is the **top-left** corner.
- **x** increases to the right (0 to 319).
- **y** increases downward (0 to 479).
- The 3.5-inch display is 320 × 480 pixels.

### 4. Setting the text size

`setTextSize()` scales the text. The display is large, so a bigger size like 3 looks great:

```cpp
gfx->setTextSize(3);
```

### 5. Printing text

`println()` prints text and moves to the next line. `print()` prints without a newline:

```cpp
gfx->println("Hello World");  // Print, then move to next line
gfx->print("Hello");          // Print, stay on same line
```

## Code Explanation

The heart of this lesson is just four lines: pick a color, pick a spot, pick a size, print.

```cpp
// White text
gfx->setTextColor(WHITE);

// Start at (50, 200)
gfx->setCursor(50, 200);

// Make it large
gfx->setTextSize(3);

// Print it
gfx->println("Hello World");
```

## Expected Result

After uploading, the screen shows:
- A black background
- Large white text reading **Hello World** around the middle of the screen

## Extended Exercises

1. **Move the text** — try different coordinates:
   ```cpp
   gfx->setCursor(100, 100);
   ```

2. **Change the color**:
   ```cpp
   gfx->setTextColor(RED);
   gfx->setTextColor(GREEN);
   ```

3. **Change the size**:
   ```cpp
   gfx->setTextSize(1);  // Small
   gfx->setTextSize(2);  // Medium
   gfx->setTextSize(4);  // Large
   ```

4. **Print multiple lines**:
   ```cpp
   gfx->setCursor(50, 100);
   gfx->println("Line 1");
   gfx->setCursor(50, 150);
   gfx->println("Line 2");
   ```

5. **Turn the backlight off** to save power when the screen isn't needed:
   ```cpp
   digitalWrite(TFT_BACKLIGHT, LOW);   // OFF
   digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
   ```

## Frequently Asked Questions

**Q: The screen is blank.**
- Make sure the sketch turns the backlight on (`digitalWrite(TFT_BACKLIGHT, HIGH)`).
- Double-check your wiring, especially the **DC** and **RST** pins.
- Open the Serial Monitor and look for an error message.

**Q: The text is in the wrong place.**
- Keep coordinates on screen: x from 0 to 319, y from 0 to 479.
- Remember the origin `(0, 0)` is the top-left corner.

**Q: The text color is wrong.**
- Make sure you used one of the color names listed above.
- Set the color *before* you print the text.

**Q: The backlight won't turn on.**
- Confirm the sketch runs `digitalWrite(TFT_BACKLIGHT, HIGH)` (on the 0.96-inch module,
  use `LOW` instead).
- Check that the backlight pin is wired (GPIO 41 on ESP32-S3, GPIO 32 on classic ESP32).

## Next Step

Nicely done — you've got text on the screen! Next:
- [Lesson 02: Colors](../Lesson02_Colors/README.md) — learn to use color.
