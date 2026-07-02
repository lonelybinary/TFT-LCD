# Lesson 04: Text Style

## Course Objectives

Put backgrounds behind text and build the label / highlight effects every real interface
uses.

## Key Concepts

### 1. The `bg=` parameter

```python
tft.text("White on Red", 50, 30, WHITE, bg=RED, scale=2)
```

This paints the character cells' background too — Arduino's `setTextColor(fg, bg)`.

**Why the default background is black, not transparent:** the display can't be read back
over SPI (there's no MISO wire), so the driver can't know what's already on screen behind
a character. It always paints the full character cell. To make text look transparent,
pass a `bg=` that matches whatever the text sits on.

### 2. Backgrounds bigger than the text

`bg=` covers exactly the character cells. For padding — a label, a button, a banner —
draw a filled rectangle first, then the text on top with a matching `bg=`:

```python
tft.fill_rect(50, y, 130, 35, GREEN)                      # the padded background
tft.text("SUCCESS", 60, y + 10, BLACK, bg=GREEN, scale=2)  # text on top
```

### 3. Readable color combinations

High contrast reads best: white-on-black, black-on-yellow, white-on-red. Low-contrast
pairs (cyan-on-magenta) are shown in the lesson mostly as a warning — squint and see.

## Run it

```bash
mpremote run lesson04_textstyle.py
```

## Extended Exercises

1. Make a "battery low" label: white text on a red rectangle, bottom-right corner.
2. Build a two-line "toast" notification: gray rectangle, white title, smaller gray text.
3. Write a `label(text, x, y, fg, bg)` **function** so you stop repeating the
   rectangle+text pair — you'll build exactly this in Lesson 7.

## FAQ

**My text overwrote a shape behind it with black boxes.** That's the default
`bg=BLACK`. Pass the color of whatever is behind the text instead.

**Can I get bold or a different font?** The built-in 8×8 font is the only one in stock
MicroPython. For "bold", draw the text twice, one pixel apart. Custom fonts need frozen
font modules — beyond this tutorial, but search "micropython writer fonts" when you're
ready.

---

Next: [Lesson 05: Graphics](../Lesson05_Graphics/README.md) ·
Previous: [Lesson 03: Text Size](../Lesson03_TextSize/README.md)
