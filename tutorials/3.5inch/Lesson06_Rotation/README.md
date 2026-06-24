# Lesson 06: Rotation

## Course Objectives

Learn to rotate the display so you can use it in landscape as well as portrait, and
understand how rotating changes the coordinate system.

## Key Concepts

### 1. Setting the rotation

`setRotation(angle)` turns the display. There are four settings, 0 to 3:

```cpp
gfx->setRotation(0);  // 0° — portrait (default)
gfx->setRotation(1);  // 90° clockwise — landscape
gfx->setRotation(2);  // 180° — upside-down portrait
gfx->setRotation(3);  // 270° — landscape the other way
```

What each one gives you:

- **0 (portrait)**: 320 wide × 480 tall. Origin at the top-left.
- **1 (landscape)**: 480 wide × 320 tall.
- **2 (portrait, flipped)**: 320 wide × 480 tall.
- **3 (landscape, flipped)**: 480 wide × 320 tall.

Notice that rotations 1 and 3 are **landscape**, so the screen becomes wider than it is tall.

### 2. Rotation swaps width and height

After a 90° or 270° rotation, `width()` and `height()` swap. Always read them after setting
the rotation:

```cpp
gfx->setRotation(0);
int w0 = gfx->width();   // 320
int h0 = gfx->height();  // 480

gfx->setRotation(1);
int w1 = gfx->width();   // 480
int h1 = gfx->height();  // 320
```

### 3. Rotation changes where (0,0) is

The origin `(0, 0)` is always the top-left of the screen *as you're now looking at it*. So
the same `setCursor(0, 0)` lands in a different physical corner after you rotate:

```cpp
gfx->setRotation(0);
gfx->setCursor(0, 0);  // top-left in portrait

gfx->setRotation(1);
gfx->setCursor(0, 0);  // top-left of the rotated (landscape) view
```

The practical takeaway: **after you rotate, recalculate your positions.**

### 4. When to use rotation

**Good reasons:**
- You want a landscape layout (use 1 or 3).
- Your device is mounted sideways or upside-down.

**Keep in mind:**
- Text and shapes will land in new spots, so plan positions after rotating.
- It's easiest to call `setRotation()` once, right after initializing, and stick with it.

## Code Explanation

### Setting a rotation and drawing

```cpp
gfx->setRotation(1);   // landscape
gfx->fillScreen(BLACK);

gfx->setCursor(50, 50);
gfx->println("Rotated");
```

### Cycling through all four

```cpp
for (int rotation = 0; rotation < 4; rotation++) {
  gfx->setRotation(rotation);
  gfx->fillScreen(BLACK);

  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  gfx->setCursor(50, 50);
  gfx->print("Rot: ");
  gfx->println(rotation);

  delay(3000);
}
```

## Expected Result

1. **All four rotations**: 0, 1, 2, 3 shown in turn.
2. **Axes**: the x and y axes drawn with the origin marked.
3. **Same text, different angles**: the same text at each rotation.
4. **Shapes**: shapes shown at each rotation.
5. **Reference**: a small table of rotation angles.

## Extended Exercises

1. **Layout that adapts to rotation**:
   ```cpp
   void drawAdaptiveLayout() {
     int w = gfx->width();
     int h = gfx->height();
     // ...lay things out based on w and h...
   }
   ```

2. **Detect portrait vs. landscape**:
   ```cpp
   bool isLandscape = (gfx->width() > gfx->height());
   if (isLandscape) {
     // landscape layout
   } else {
     // portrait layout
   }
   ```

3. **Step through rotations as an animation**:
   ```cpp
   for (int r = 0; r < 4; r++) {
     gfx->setRotation(r);
     // ...draw...
     delay(500);
   }
   ```

## Frequently Asked Questions

**Q: My content is in the wrong place after rotating.**
- The coordinate system changes when you rotate, so recalculate positions.
- Read `width()` and `height()` *after* calling `setRotation()`.

**Q: How do I keep something centered no matter the rotation?**
- Use `width()` and `height()` to compute the center every time, instead of hard-coded
  numbers.

**Q: Does rotating slow things down?**
- Rotating itself is cheap. What costs time is redrawing everything afterward.

## Next Step

You've covered all the building blocks! The next lessons combine them into real interfaces.
- [Lesson 07: System Info Display](../Lesson07_SystemInfo/README.md) — build your first full screen.
