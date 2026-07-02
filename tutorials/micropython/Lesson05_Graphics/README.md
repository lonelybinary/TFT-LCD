# Lesson 05: Graphics

## Course Objectives

Draw every basic shape, combine them into icons and UI parts, and learn the one trick
that makes animation smooth on a pure-Python driver.

## Key Concepts

### 1. The shape functions

| Shape | Outline | Filled |
| ----- | ------- | ------ |
| Line | `line(x0, y0, x1, y1, c)` | — |
| Rectangle | `rect(x, y, w, h, c)` | `fill_rect(x, y, w, h, c)` |
| Circle | `circle(cx, cy, r, c)` | `fill_circle(cx, cy, r, c)` |
| Triangle | — | `fill_triangle(x0,y0, x1,y1, x2,y2, c)` |
| H/V line | `hline(x, y, w, c)` / `vline(x, y, h, c)` | — |

Rectangles take a corner plus width/height; circles take their **center** plus radius.

### 2. Building UI parts

A progress bar is just two shapes:

```python
tft.rect(20, 200, 280, 40, WHITE)        # the frame
tft.fill_rect(20, 200, 140, 40, GREEN)   # the fill: 50% of 280 px
```

A play/stop/record icon row is a triangle, a square, and a circle. Most interfaces are
shapes plus text — nothing more.

### 3. Animation: erase-and-redraw, don't clear

Filling the whole 320×480 screen pushes 153,600 pixels down the SPI wire. Doing that
every frame limits you to a flickery few frames per second. Instead, erase only the old
shape and draw the new one:

```python
tft.fill_circle(old_x, 240, 30, BLACK)   # erase where it was
tft.fill_circle(x, 240, 30, YELLOW)      # draw where it is now
```

Now each frame touches ~2% of the pixels, and the motion is smooth. This "only redraw
what changed" idea is the single most useful display-programming habit — every dashboard
in the later lessons relies on it.

### 4. Speed expectations

Filled shapes (`fill_rect`, `fill_circle`, `fill_triangle`) are fast — they stream whole
rows at once. Outlines and diagonal lines go pixel-by-pixel in Python, so they're slower.
A big `circle()` outline visibly sweeps; that's normal.

## Run it

```bash
mpremote run lesson05_graphics.py
```

## Extended Exercises

1. Draw a house: a square, a triangle roof, a rectangle door, two square windows.
2. Animate the progress bar from 0% to 100% (only draw the newly-filled strip each step).
3. Bounce the yellow ball left-right continuously (`while True:` — press Ctrl-C in the
   REPL to stop it).

## FAQ

**The moving circle leaves a faint trail on some steps.** Your erase color must exactly
match the background. If you drew over the grid, you erased the grid too — real games
redraw the background patch, not just black.

**Why is there no `triangle()` outline?** Draw three `line()` calls. (That's exactly
what a triangle outline is.)

---

Next: [Lesson 06: Rotation](../Lesson06_Rotation/README.md) ·
Previous: [Lesson 04: Text Style](../Lesson04_TextStyle/README.md)
