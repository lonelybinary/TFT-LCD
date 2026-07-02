# Lesson 10: Notification Interface

## Course Objectives

Build a notification card with an icon, message text, and a close button — and position
everything **relative to the card**, not the screen.

## Key Concepts

### 1. Relative positioning

The card's geometry is defined once:

```python
card_x, card_y, card_w, card_h = 30, 80, 260, 200
```

Every element inside — icon, text, close button — is computed from those four numbers
(`icon_x = card_x + 40`, `btn_x = card_x + card_w - 30`, ...). Change `card_y` to 300
and the whole notification moves as one piece. Absolute coordinates everywhere is the
most common beginner layout mistake; this lesson is the cure.

### 2. Icons from shapes

An "alert" icon is a filled circle plus an exclamation mark:

```python
tft.fill_circle(icon_x, icon_y, 25, BLUE)
tft.text("!", icon_x - 8, icon_y - 12, WHITE, bg=BLUE, scale=3)
```

Note `bg=BLUE` so the character cell blends into the circle instead of punching a black
box in it (Lesson 4's rule, again).

### 3. Dismissing = painting over

Closing the notification is one `fill_rect` in the background color over the card area.
On a display there is no "remove" — there is only "draw something else on top".

## Run it

```bash
mpremote run lesson10_notification.py
```

## Extended Exercises

1. Write `def notify(title, body):` that draws this card with any text — you now have a
   reusable toast system.
2. Add a second icon style: green circle + check mark for "success".
3. Slide the card in from the top: draw it at y = -200, -150, ... 80, erasing the strip
   it left behind each step.

## FAQ

**The icon's "!" sits in a black box.** You dropped the `bg=BLUE`. Text paints its full
character cell (there's no transparency — the display can't be read back over SPI).

**Can I make rounded corners?** With `fill_circle` in each corner plus rectangles for
the sides you can fake it — try it, it's a good shape-composition exercise.

---

Next: [Lesson 11: Clock Display](../Lesson11_Clock/README.md) ·
Previous: [Lesson 09: Data Monitoring](../Lesson09_DataMonitoring/README.md)
