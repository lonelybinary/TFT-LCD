# Lesson 03: Text Size

## Course Objectives

Learn to make text bigger or smaller, and understand how text size affects how much room your
words take up on screen.

## Key Concepts

### 1. Setting the text size

`setTextSize(size)` scales the built-in font. Size 1 is the default; larger numbers make
bigger text:

```cpp
gfx->setTextSize(1);  // Smallest (default)
gfx->setTextSize(2);  // 2× bigger
gfx->setTextSize(3);  // 3× bigger
// ... up to 8
```

**Sizes range from 1 to 8:**
- **Size 1**: smallest — good for lots of text at once.
- **Sizes 2–3**: medium — good for titles and key info.
- **Sizes 4–8**: very large — good for big numbers or one short word.

### 2. How size changes the dimensions

The built-in font is 6 × 8 pixels at size 1, and each step multiplies that:

- **Character width**: about `size × 6` pixels
- **Character height**: about `size × 8` pixels

```cpp
gfx->setTextSize(1);  // each character ≈ 6 × 8 pixels
gfx->setTextSize(2);  // ≈ 12 × 16 pixels
gfx->setTextSize(3);  // ≈ 18 × 24 pixels
```

Knowing this lets you leave the right amount of space between lines.

### 3. Spacing multiple lines

When you stack lines of text, move the y coordinate down by the height of each line (plus a
little gap):

```cpp
int y = 20;
for (int size = 1; size <= 5; size++) {
  gfx->setTextSize(size);
  gfx->setCursor(20, y);
  gfx->println("Text");
  y += size * 8 + 5;  // height of this line + 5px gap
}
```

### 4. Mixing sizes on one screen

You can change the size as often as you like — for example, a big title and smaller body text:

```cpp
// Large title
gfx->setTextSize(3);
gfx->setCursor(80, 30);
gfx->println("TITLE");

// Small body text
gfx->setTextSize(1);
gfx->setCursor(20, 150);
gfx->println("Body text");
```

## Code Explanation

### Setting a size

```cpp
gfx->setTextSize(1);
gfx->setCursor(20, 20);
gfx->println("Size 1");
```

### Comparing sizes in a loop

```cpp
for (int size = 1; size <= 5; size++) {
  gfx->setTextSize(size);
  gfx->setCursor(20, y);
  gfx->print("Size ");
  gfx->println(size);
  y += size * 8 + 5;  // move down for the next line
}
```

### Centering text (taking size into account)

To center text, work out its width and height from the size, then position it:

```cpp
int size = 3;
gfx->setTextSize(size);
int textWidth = strlen("TEXT") * size * 6;  // estimate width
int x = (gfx->width() - textWidth) / 2;
int y = (gfx->height() - size * 8) / 2;
gfx->setCursor(x, y);
gfx->println("TEXT");
```

## Expected Result

1. **Different sizes**: text shown at sizes 1, 2, 3, and 4 in turn.
2. **Side-by-side comparison**: several sizes on one screen.
3. **Numbers**: numbers shown at different sizes.
4. **Mixed sizes**: a title, subtitle, and body text together.
5. **Animated size**: text that grows from size 1 to 5.

## Extended Exercises

1. **Make a title helper**:
   ```cpp
   void drawTitle(const char* text, int y, uint16_t color) {
     gfx->setTextSize(3);
     gfx->setTextColor(color);
     // ...center it...
   }
   ```

2. **Make a big-number helper**:
   ```cpp
   void drawLargeNumber(int number, int x, int y) {
     gfx->setTextSize(4);
     gfx->setCursor(x, y);
     gfx->println(number);
   }
   ```

3. **Auto-fit the size** so text never runs off screen:
   ```cpp
   int calculateSize(const char* text, int maxWidth) {
     int len = strlen(text);
     for (int size = 8; size >= 1; size--) {
       if (len * size * 6 <= maxWidth) {
         return size;
       }
     }
     return 1;
   }
   ```

## Frequently Asked Questions

**Q: What's the biggest text size?**
- The maximum is 8, but it's really limited by screen space. On this 320 × 480 display,
  sizes up to 5 or 6 are comfortable for most text.

**Q: How do I know exactly how wide my text will be?**
- A good estimate is `character count × size × 6` pixels.
- The exact width can vary slightly by character, but this estimate is usually close enough.

**Q: My large text gets cut off.**
- Check that it fits on screen.
- Use `gfx->width()` and `gfx->height()` to get the current screen size.
- Shorten the text or use a smaller size.

## Next Step

- [Lesson 04: Text Style](../Lesson04_TextStyle/README.md) — add background colors and highlights.
