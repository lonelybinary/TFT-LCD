# Lesson 07: System Info Display

## Course Objectives

Build your first complete screen — and more importantly, stop copy-pasting drawing code:
wrap it in reusable Python functions.

## Key Concepts

### 1. UI helper functions

Every real interface repeats the same handful of elements. Write each one **once**:

```python
def draw_label(text, x, y, bg_color, text_color, scale=2):
    text_w = len(text) * 8 * scale
    tft.fill_rect(x, y, text_w + 8, 8 * scale + 8, bg_color)
    tft.text(text, x + 4, y + 4, text_color, bg=bg_color, scale=scale)
```

Now `draw_label("ONLINE", 170, 95, GREEN, BLACK)` reads like what it *means*, and fixing
the padding once fixes it everywhere. Lessons 8–11 all build on this pattern.

### 2. The four helpers in this lesson

| Helper | What it draws |
| ------ | ------------- |
| `draw_label(...)` | Padded colored label, sized to its text |
| `draw_progress_bar(...)` | Outline frame + percentage fill |
| `draw_centered_text(...)` | Title centered on `tft.width` |
| `draw_separator(...)` | Horizontal rule with margins |

### 3. Layout by rows

The screen is a title plus four rows (status / temperature / battery / signal), each at
a fixed y. Sketching rows on paper before coding beats nudging pixels afterwards.

> **Porting note:** x-positions here differ slightly from the Arduino lesson because
> MicroPython's font is 8 px wide vs Arduino's 6 px — `"Battery:"` simply needs more
> room. The structure is identical.

## Run it

```bash
mpremote run lesson07_systeminfo.py
```

## Extended Exercises

1. Show real values: `import esp32; esp32.mcu_temperature()` on an S3 gives the chip
   temperature (classic ESP32: `esp32.raw_temperature()` in Fahrenheit).
2. Add a "WiFi:" row with a red `OFFLINE` label.
3. Make `draw_progress_bar` turn its fill red below 20% (pass the percent in, choose the
   color inside the function).

## FAQ

**Why do the helpers use `tft` without it being a parameter?** They close over the
module-level `tft` — fine for a single-display script. If it bothers you, pass `tft` as
the first argument; that's the more scalable style.

**My label background sticks out past the text.** That's the `+8` padding. Padding is
what makes it a label rather than just colored text.

---

Next: [Lesson 08: Menu Interface](../Lesson08_Menu/README.md) ·
Previous: [Lesson 06: Rotation](../Lesson06_Rotation/README.md)
