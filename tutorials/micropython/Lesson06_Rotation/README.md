# Lesson 06: Rotation

## Course Objectives

Turn the screen sideways and understand what rotation does to the coordinate system.

## Key Concepts

### 1. `set_rotation()`

```python
tft.set_rotation(1)   # 0 = portrait, 1 = 90°, 2 = 180°, 3 = 270°
```

The rotation happens inside the display controller — drawing is just as fast in any
orientation.

### 2. Width and height swap

In portrait (0 and 2) this display is 320 × 480; in landscape (1 and 3) it's 480 × 320.
`tft.width` and `tft.height` always reflect the **current** orientation — so code that
uses them (like the centering formula from Lesson 3) keeps working in every rotation:

```python
x = (tft.width - text_w) // 2   # centered in ANY rotation
```

That's the real lesson here: never hard-code 320 or 480; ask the driver.

### 3. `(0, 0)` follows the rotation

The origin is always the top-left corner *of the current orientation* — watch the yellow
origin dot jump to a different physical corner at each step of Part 1.

## Run it

```bash
mpremote run lesson06_rotation.py
```

## Extended Exercises

1. Build a landscape status screen (rotation 1): title top-left, a progress bar along
   the bottom edge, using `tft.width`/`tft.height` for all positions.
2. Draw an arrow that always points at the same physical corner of the glass no matter
   the rotation (you'll need to think about what rotation does to your coordinates).

## FAQ

**My panel shows rotation 0 mirrored or flipped.** Panel batches vary in scan direction.
Fix it at the constructor with `flip_x=True` / `flip_y=True` — the four rotations then
follow along consistently.

**After the script, my next lesson looked sideways.** Rotation persists until changed —
this lesson restores `set_rotation(0)` at the end, and each lesson creates a fresh
driver anyway.

---

Next: [Lesson 07: System Info Display](../Lesson07_SystemInfo/README.md) ·
Previous: [Lesson 05: Graphics](../Lesson05_Graphics/README.md)
