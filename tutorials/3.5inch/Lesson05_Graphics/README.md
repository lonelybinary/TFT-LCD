# Lesson 05: Graphics

## Course Objectives

Learn to draw shapes — lines, rectangles, circles, and triangles — and start combining them
into simple UI pieces.

## Key Concepts

### 1. Lines

`drawLine()` draws a straight line between two points:

```cpp
gfx->drawLine(x1, y1, x2, y2, color);
```

- `x1, y1`: where the line starts
- `x2, y2`: where it ends
- `color`: the line color

```cpp
gfx->drawLine(20, 20, 300, 20, WHITE);   // horizontal
gfx->drawLine(20, 20, 20, 460, RED);     // vertical
gfx->drawLine(20, 20, 300, 460, GREEN);  // diagonal
```

### 2. Rectangles

Most shapes come in two flavors: **outlined** (just the border) and **filled** (solid).

#### Outline only

```cpp
gfx->drawRect(x, y, width, height, color);
```

- `x, y`: the top-left corner
- `width`, `height`: the size
- `color`: the border color

#### Filled

```cpp
gfx->fillRect(x, y, width, height, color);
```

```cpp
gfx->drawRect(20, 20, 80, 60, RED);  // outline
gfx->fillRect(20, 20, 80, 60, RED);  // solid
```

### 3. Circles

#### Outline only

```cpp
gfx->drawCircle(x, y, radius, color);
```

- `x, y`: the **center** of the circle
- `radius`: how big it is
- `color`: the color

#### Filled

```cpp
gfx->fillCircle(x, y, radius, color);
```

```cpp
gfx->drawCircle(160, 200, 50, BLUE);  // outline
gfx->fillCircle(160, 200, 50, BLUE);  // solid
```

### 4. Triangles

`fillTriangle()` draws a solid triangle from three corner points:

```cpp
gfx->fillTriangle(x1, y1, x2, y2, x3, y3, color);
```

```cpp
// A "play" button shape
gfx->fillTriangle(50, 100, 50, 200, 150, 150, GREEN);
```

## Code Explanation

### Basic shapes

```cpp
// Line
gfx->drawLine(20, 20, 300, 20, WHITE);

// Rectangle
gfx->drawRect(20, 20, 80, 60, RED);
gfx->fillRect(20, 20, 80, 60, RED);

// Circle
gfx->drawCircle(160, 200, 50, BLUE);
gfx->fillCircle(160, 200, 50, BLUE);
```

### Combining shapes into UI

```cpp
// Progress bar: an outlined frame with a filled bar inside
gfx->drawRect(20, 200, 280, 40, WHITE);  // frame
gfx->fillRect(20, 200, 140, 40, GREEN);  // 50% fill

// Button: a filled box with an outline
gfx->fillRect(100, 300, 120, 60, BLUE);
gfx->drawRect(100, 300, 120, 60, WHITE);
```

## Expected Result

1. **Lines**: horizontal, vertical, and diagonal.
2. **Rectangles**: outlined and filled.
3. **Circles**: outlined and filled.
4. **Combined shapes**: simple icons (play, stop, round buttons).
5. **Grid**: a coordinate grid.
6. **Progress bar**: a UI progress bar.
7. **Animation**: a moving circle and a growing rectangle.

## Extended Exercises

1. **A button helper**:
   ```cpp
   void drawButton(const char* text, int x, int y, int w, int h) {
     gfx->fillRect(x, y, w, h, BLUE);
     gfx->drawRect(x, y, w, h, WHITE);
     // ...center the text...
   }
   ```

2. **A bar chart**:
   ```cpp
   int values[] = {50, 80, 60, 90, 70};
   for (int i = 0; i < 5; i++) {
     int barHeight = values[i];
     gfx->fillRect(50 + i * 40, 400 - barHeight, 30, barHeight, GREEN);
   }
   ```

3. **An icon helper**:
   ```cpp
   void drawPlayIcon(int x, int y, int size) {
     gfx->fillTriangle(x, y, x, y + size, x + size, y + size/2, GREEN);
   }
   ```

## Frequently Asked Questions

**Q: How do I draw a rounded rectangle?**
- The library doesn't have a built-in rounded rectangle here. You can fake the corners with
  small filled circles, or just use a plain rectangle.

**Q: How do I draw an ellipse?**
- There's no built-in ellipse. You can approximate one with several small circles or lines.

**Q: Drawing feels slow.**
- These modules use hardware SPI, which is already fast.
- Don't redraw the whole screen if only one part changed — just update that part.
- Clear the screen less often.

## Next Step

- [Lesson 06: Rotation](../Lesson06_Rotation/README.md) — turn the screen sideways.
