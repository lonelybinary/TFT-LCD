# Lesson 02: Colors

## Course Objectives

Use color everywhere: fill the whole screen, color your text, and mix your own custom
colors.

## Key Concepts

### 1. The built-in colors

Eight ready-made colors are importable straight from the driver:

```python
from st77xx import BLACK, WHITE, RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN
```

### 2. Filling the screen

```python
tft.fill(RED)    # every pixel becomes red
```

The lesson cycles through all eight colors, two seconds each. This is also a great panel
test — you'll spot a wrong `bgr=` setting immediately (red and blue swap).

### 3. Colored text

The color parameter of `text()` works with any color value:

```python
tft.text("RED", 50, 20, RED, scale=2)
```

### 4. Custom colors with `color565()`

The display stores a pixel in 16 bits: 5 bits red, 6 bits green, 5 bits blue — that's
why it's called **RGB565**. `color565()` packs a familiar 0–255 RGB triple into that
format:

```python
orange = st77xx.color565(255, 140, 0)
gray   = st77xx.color565(128, 128, 128)
```

Because green gets an extra bit, subtle color differences survive best in green — a bit
of display trivia you can now explain at parties.

## Run it

```bash
mpremote run lesson02_colors.py
```

or press **F5** in Thonny.

## Extended Exercises

1. Make a purple (`color565(128, 0, 128)`) and a teal, and show their names in them.
2. Write a loop that fades the screen from black to bright red in 8 steps
   (hint: `color565(i * 32, 0, 0)` — but watch out, 255 is the max).
3. Fill the screen with your favorite color and put your name in the middle.

## FAQ

**Red and blue look swapped.** That's the `bgr=` constructor argument — flip it.

**The whole picture looks like a photo negative.** That's the `invert=` argument.

**The screen flashes noticeably between fills.** Normal — a full 320×480 fill pushes
300 KB over SPI. It's fast (~a tenth of a second) but visible when the color changes
completely.

---

Next: [Lesson 03: Text Size](../Lesson03_TextSize/README.md) ·
Previous: [Lesson 01: Hello World](../Lesson01_HelloWorld/README.md)
