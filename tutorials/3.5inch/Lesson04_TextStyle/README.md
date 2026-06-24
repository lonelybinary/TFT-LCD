# Lesson 04: Text Style

## Course Objectives

Learn to style your text — giving it a background color and building useful effects like
labels and highlights.

## Key Concepts

### 1. Foreground and background colors

#### Just the text color

```cpp
gfx->setTextColor(WHITE);  // White text on whatever is already there
```

The text is drawn over the current screen background.

#### Text color *and* a background color

Give `setTextColor()` two colors and it paints a background behind each character:

```cpp
gfx->setTextColor(foreground, background);
gfx->setTextColor(WHITE, RED);  // White text on a red background
```

- **First color**: the text itself (foreground).
- **Second color**: the background behind the text.

### 2. Choosing readable color combinations

High contrast is easy to read; low contrast strains the eyes.

**Good (high contrast):**
- White text on black
- Black text on white
- Yellow text on blue

**Avoid (low contrast):**
- Light text on a light background
- Dark text on a dark background

### 3. Two ways to put a background behind text

#### Way 1: Let `setTextColor` do it

```cpp
gfx->setTextColor(WHITE, RED);
gfx->setCursor(50, 30);
gfx->println("Text");
```

**Pro:** simple — the background is handled for you.
**Con:** the background only covers the text itself, with no padding.

#### Way 2: Draw a rectangle first, then text on top

```cpp
gfx->fillRect(20, 100, 150, 30, GREEN);  // background box
gfx->setTextColor(BLACK);
gfx->setCursor(50, 110);
gfx->println("Text");
```

**Pro:** you control the exact size and position of the background.
**Con:** you place the text yourself. (`fillRect` is covered fully in Lesson 5 — for now,
the numbers are x, y, width, height, color.)

### 4. Building a label

A **label** is a small colored box with text inside — a common UI element. Combine a filled
rectangle with contrasting text:

```cpp
// Success label (green box)
gfx->fillRect(50, 50, 120, 35, GREEN);
gfx->setTextColor(BLACK);
gfx->setCursor(60, 60);
gfx->println("SUCCESS");

// Error label (red box)
gfx->fillRect(50, 150, 120, 35, RED);
gfx->setTextColor(WHITE);
gfx->setCursor(60, 160);
gfx->println("ERROR");
```

## Code Explanation

### Text color, with and without a background

```cpp
// Just the text color
gfx->setTextColor(WHITE);
gfx->println("White text");

// Text color + background color
gfx->setTextColor(WHITE, RED);
gfx->println("White on Red");
```

### A label

```cpp
// Draw the background box
gfx->fillRect(50, 50, 120, 35, GREEN);

// Set the text color
gfx->setTextColor(BLACK);

// Place the text (nudge the y a little so it sits nicely inside)
gfx->setCursor(60, 60);
gfx->println("SUCCESS");
```

### A highlight row

```cpp
// Highlight bar across the screen
gfx->fillRect(0, 100, 320, 40, CYAN);

// Text on top
gfx->setTextColor(BLACK);
gfx->setCursor(50, 110);
gfx->println("Highlighted");
```

## Expected Result

1. **Foreground colors**: text in several different colors.
2. **Foreground + background**: text with a background color behind it.
3. **Combinations**: various color pairings.
4. **Background methods**: both ways of putting a background behind text.
5. **Labels**: success, warning, error, and info labels.
6. **Highlight**: a highlighted text row.

## Extended Exercises

1. **A status helper** (0 = success, 1 = warning, 2 = error):
   ```cpp
   void drawStatus(const char* text, int status, int x, int y) {
     uint16_t colors[] = {GREEN, YELLOW, RED};
     gfx->fillRect(x, y, 100, 40, colors[status]);
     gfx->setTextColor(BLACK);
     gfx->setCursor(x+10, y+10);
     gfx->println(text);
   }
   ```

2. **A button helper**:
   ```cpp
   void drawButton(const char* text, int x, int y, int w, int h) {
     gfx->fillRect(x, y, w, h, BLUE);  // fill
     gfx->drawRect(x, y, w, h, WHITE); // border
     gfx->setTextColor(WHITE);
     // ...center the text...
   }
   ```

## Frequently Asked Questions

**Q: My background color isn't showing.**
- Use the two-color form: `setTextColor(foreground, background)`.
- Check the background color isn't the same as the screen color.

**Q: The background box is the wrong size.**
- The `setTextColor` background only covers the text exactly. For a bigger box, draw it
  yourself with `fillRect()` first.

**Q: My text doesn't line up with its background box.**
- When you use `fillRect()`, you position the text by hand.
- Nudge the y coordinate down a few pixels (about +5 to +10, depending on text size) so the
  text sits centered inside the box.

## Next Step

- [Lesson 05: Graphics](../Lesson05_Graphics/README.md) — draw lines, rectangles, and circles.
