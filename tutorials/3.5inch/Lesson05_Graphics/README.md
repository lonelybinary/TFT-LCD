# Lesson 05: Graphics

## Course Objectives

Learn how to draw basic graphics, including lines, rectangles, circles, etc., and how to create simple UI elements.

## Key Concepts

### 1. Draw Lines

Use the `drawLine()` function to draw straight lines:

```cpp
gfx->drawLine(x1, y1, x2, y2, color);
```

**Parameter Description**:
- `x1, y1`: Start point coordinates
- `x2, y2`: End point coordinates
- `color`: Line color

**Example**:
```cpp
// Horizontal line
gfx->drawLine(20, 20, 300, 20, WHITE);

// Vertical line
gfx->drawLine(20, 20, 20, 460, RED);

// Diagonal line
gfx->drawLine(20, 20, 300, 460, GREEN);
```

### 2. Draw Rectangles

#### Hollow Rectangle (Outline)

```cpp
gfx->drawRect(x, y, width, height, color);
```

**Parameter Description**:
- `x, y`: Top-left corner coordinates
- `width`: Rectangle width
- `height`: Rectangle height
- `color`: Border color

#### Filled Rectangle

```cpp
gfx->fillRect(x, y, width, height, color);
```

**Example**:
```cpp
// Hollow rectangle
gfx->drawRect(20, 20, 80, 60, RED);

// Filled rectangle
gfx->fillRect(20, 20, 80, 60, RED);
```

### 3. Draw Circles

#### Hollow Circle (Outline)

```cpp
gfx->drawCircle(x, y, radius, color);
```

**Parameter Description**:
- `x, y`: Circle center coordinates
- `radius`: Radius
- `color`: Border color

#### Filled Circle

```cpp
gfx->fillCircle(x, y, radius, color);
```

**Example**:
```cpp
// Hollow circle
gfx->drawCircle(160, 200, 50, BLUE);

// Filled circle
gfx->fillCircle(160, 200, 50, BLUE);
```

### 4. Draw Triangle

```cpp
gfx->fillTriangle(x1, y1, x2, y2, x3, y3, color);
```

**Parameter Description**:
- `x1, y1, x2, y2, x3, y3`: Coordinates of three vertices
- `color`: Fill color

**Example**:
```cpp
// Play button (triangle)
gfx->fillTriangle(50, 100, 50, 200, 150, 150, GREEN);
```

## Code Explanation

### Basic Graphics Drawing

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

### Create UI Elements

```cpp
// Progress bar
gfx->drawRect(20, 200, 280, 40, WHITE);  // Background frame
gfx->fillRect(20, 200, 140, 40, GREEN); // Fill (50%)

// Button
gfx->fillRect(100, 300, 120, 60, BLUE);
gfx->drawRect(100, 300, 120, 60, WHITE);
```

## Expected Result

1. **Line Drawing**: Horizontal, vertical, diagonal lines
2. **Rectangle Drawing**: Hollow and filled rectangles
3. **Circle Drawing**: Hollow and filled circles
4. **Combined Graphics**: Create simple icons (play, stop, circular buttons)
5. **Grid Drawing**: Draw coordinate grid
6. **Progress Bar**: Create progress bar UI element
7. **Dynamic Drawing**: Moving circles and growing rectangles

## Extended Exercises

1. **Create Button Function**:
   ```cpp
   void drawButton(const char* text, int x, int y, int w, int h) {
     gfx->fillRect(x, y, w, h, BLUE);
     gfx->drawRect(x, y, w, h, WHITE);
     // Center display text...
   }
   ```

2. **Draw Chart**:
   ```cpp
   // Draw simple bar chart
   int values[] = {50, 80, 60, 90, 70};
   for (int i = 0; i < 5; i++) {
     int barHeight = values[i];
     gfx->fillRect(50 + i * 40, 400 - barHeight, 30, barHeight, GREEN);
   }
   ```

3. **Create Icon Library**:
   ```cpp
   void drawPlayIcon(int x, int y, int size) {
     gfx->fillTriangle(x, y, x, y + size, x + size, y + size/2, GREEN);
   }
   ```

## Frequently Asked Questions

**Q: How to draw rounded rectangle?**
- Arduino GFX library doesn't directly support rounded rectangles
- Can use multiple small rectangles or circles to simulate rounded corners

**Q: How to draw ellipse?**
- Arduino GFX library doesn't directly support ellipses
- Can use multiple small circles or lines to approximate

**Q: Graphics drawing is slow?**
- Using hardware SPI can speed up drawing
- Reduce unnecessary screen clearing operations
- Only update parts that need to change

## Next Step

After completing this lesson, you can continue with:
- [Lesson 06: Rotation](../Lesson06_Rotation/README.md) - Learn screen rotation
