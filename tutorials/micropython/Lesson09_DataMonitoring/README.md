# Lesson 09: Data Monitoring Interface

## Course Objectives

Build a dashboard out of repeating "cards", and update live values **in place** without
flicker.

## Key Concepts

### 1. Cards are just another helper

A card is an outline, a title, a big number, and a progress bar — so it becomes a
function:

```python
def draw_card(x, y, title, percent, accent_color):
    tft.rect(x, y, 130, 100, accent_color)
    tft.text(title, x + 10, y + 10, accent_color, scale=2)
    tft.text("%3d%%" % percent, x + 10, y + 40, WHITE, scale=3)
    draw_progress_bar(x + 10, y + 70, 110, 15, percent, accent_color, GREEN)
```

Two calls give you two cards side by side. A 2×2 grid is four calls.

### 2. Updating values in place

The bonus loop redraws **only what changes**: the percentage text and the bar fill.
Three details make this flicker-free:

- `"%3d%%"` pads the number to a fixed width, so "7%" fully overwrites "100%".
- The text is drawn with `bg=BLACK`, so the character cells erase themselves.
- `draw_progress_bar` paints both the filled part **and** the empty remainder — a bar
  going *down* erases its old fill without clearing anything.

This is the difference between a dashboard that gently updates and one that blinks
every second.

### 3. Fixed-width formatting

`"%3d%%" % 45` → `" 45%"`. MicroPython supports `%`-formatting and f-strings; for
overwrite-in-place UIs, fixed width is the feature that matters.

## Run it

```bash
mpremote run lesson09_datamonitoring.py
```

## Extended Exercises

1. Add a third card for free heap: `import gc; percent = 100 - gc.mem_free() * 100 // (gc.mem_free() + gc.mem_alloc())`.
2. Make a card's accent turn red when its value exceeds 90.
3. Replace the fake readings with a real sensor you own.

## FAQ

**My updating number leaves junk behind.** Either the width wasn't fixed (`"%3d%%"`) or
`bg=` wasn't set. Both are required for clean overwrites.

**Can I chart the history?** Yes — keep the last N values in a list and draw a `line()`
per pair inside a cleared plot rectangle. A good project after Lesson 11.

---

Next: [Lesson 10: Notification](../Lesson10_Notification/README.md) ·
Previous: [Lesson 08: Menu Interface](../Lesson08_Menu/README.md)
