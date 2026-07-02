# Lesson 08: Menu Interface

## Course Objectives

Build a menu with a title bar and a highlighted selection — and learn to keep interface
*data* separate from *drawing code*.

## Key Concepts

### 1. The menu is data

```python
MENU_ITEMS = ("Settings", "Data", "About", "Exit")
selected = 0
```

The drawing is one loop over that tuple. Adding a fifth menu item means adding one
string — no new drawing code. Interfaces built this way stay easy to change.

### 2. Highlighting the selection

The selected item gets a filled bar behind it and inverted text colors:

```python
if i == selected:
    tft.fill_rect(20, y - 5, 280, 50, CYAN)
    tft.text("> " + item, 40, y + 5, BLACK, bg=CYAN, scale=2)
```

Note the `bg=CYAN`: without it the text cell would paint black boxes over the highlight
bar (remember Lesson 4 — text always paints its background).

### 3. Moving the highlight without flicker

The bonus part animates the selection: when it moves, only **two rows** repaint (the
un-highlighted old row, the highlighted new row). No full-screen clear, no flicker —
the erase-and-redraw pattern from Lesson 5 applied to UI.

## Run it

```bash
mpremote run lesson08_menu.py
```

## Extended Exercises

1. Add two more menu items and check the spacing still fits (60 px per row).
2. Wire two buttons (GPIO + `Pin.IRQ_FALLING`) to move the highlight up and down —
   congratulations, you've built a real navigable menu.
3. Show a different "page" (just a title on black) when the animation lands on each
   item, then return to the menu.

## FAQ

**Why `y + 5` for the text but `y - 5` for the bar?** The bar is 50 px tall and the
scale-2 text is 16 px — the offsets center the text vertically inside the bar.

**Can the menu scroll?** Yes: keep a `top_index`, draw only the rows that fit, and
redraw all rows when `top_index` changes. Try it after Lesson 9.

---

Next: [Lesson 09: Data Monitoring](../Lesson09_DataMonitoring/README.md) ·
Previous: [Lesson 07: System Info Display](../Lesson07_SystemInfo/README.md)
