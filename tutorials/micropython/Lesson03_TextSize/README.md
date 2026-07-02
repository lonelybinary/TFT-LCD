# Lesson 03: Text Size

## Course Objectives

Control how big your text is, and learn the simple math for lining text up and centering
it.

## Key Concepts

### 1. The `scale=` parameter

```python
tft.text("Size 3", 20, 100, WHITE, scale=3)
```

MicroPython's built-in font is **8 × 8 pixels** per character. `scale` multiplies that:

| scale | character size | characters per line (320 px) |
| ----- | -------------- | ---------------------------- |
| 1 | 8 × 8 px | 40 |
| 2 | 16 × 16 px | 20 |
| 3 | 24 × 24 px | 13 |
| 4 | 32 × 32 px | 10 |
| 5 | 40 × 40 px | 8 |

> **Porting note:** Arduino's font is 6 px wide, so text here is a third wider at the
> same size number. That's why this lesson's side-by-side demo stops at scale 4 where the
> Arduino version reached 5 — `"Size 4 ABC"` is 10 characters × 32 px = exactly 320 px.

### 2. Text width math

Everything in this lesson comes down to one formula:

```python
text_width = len(s) * 8 * scale
```

Lining up two pieces of text on one line means starting the second where the first ends:

```python
tft.text("Size 2", 20, y, WHITE, scale=2)
tft.text(" ABC", 20 + 6 * 8 * 2, y, CYAN, scale=2)   # 6 chars into the line
```

### 3. Centering text

```python
x = (tft.width - len(s) * 8 * scale) // 2
```

`tft.width` and `tft.height` are attributes (no parentheses) — they follow the rotation,
which will matter in Lesson 6.

## Run it

```bash
mpremote run lesson03_textsize.py
```

## Extended Exercises

1. Show your name as large as will fit on one line (use the formula to work out the
   biggest scale first).
2. Make a countdown: 5, 4, 3, 2, 1 — centered, growing bigger each second.
3. Right-align a number at the screen edge (hint: `x = tft.width - text_width`).

## FAQ

**My text ran off the right edge.** The driver clips it safely — nothing crashes, the
extra pixels just aren't shown. Do the width math to make it fit.

**Very large text draws slowly.** Text is the most CPU-hungry thing the pure-Python
driver does (it builds each string pixel-by-pixel). Keep frequently-updated text short —
Lesson 9's dashboard shows the pattern.

---

Next: [Lesson 04: Text Style](../Lesson04_TextStyle/README.md) ·
Previous: [Lesson 02: Colors](../Lesson02_Colors/README.md)
