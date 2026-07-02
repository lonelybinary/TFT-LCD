# Lesson 11: Clock Display

## Course Objectives

Draw an analog clock face — circles, tick marks, and hands placed with trigonometry —
plus a digital readout. The final lesson brings together everything you've learned.

## Key Concepts

### 1. Polar to screen coordinates

A clock is naturally described in "angle + distance from center" (polar coordinates).
One helper converts that to screen x, y:

```python
def hand_end(angle_deg, length):
    a = math.radians(angle_deg - 90)      # 0 deg = 12 o'clock
    return (CENTER_X + int(length * math.cos(a)),
            CENTER_Y + int(length * math.sin(a)))
```

The `- 90` shift is the only subtle part: math angles start at "3 o'clock" and we want
clock angles to start at "12".

### 2. Ticks and hands are the same math

- Tick marks: a short `line()` from radius−5 to radius−20 at every 30°.
- Hour hand: 30° per hour (plus `minute // 2` so it creeps between hours).
- Minute hand: 6° per minute.

### 3. Ticking without flicker

The bonus loop erases the old hands (same lines, black), advances the time, and draws
the new hands. The face circle and ticks are drawn once and refreshed cheaply. Full
screen clears would flash once per second — this doesn't.

### 4. Structure recap

Notice the shape of the final program — setup, then `draw_face()` / `draw_hands()` /
`draw_digital()` helpers, then a loop with state (`hour`, `minute`). That's the
skeleton of every display project you'll write from here.

## Run it

```bash
mpremote run lesson11_clock.py
```

## Extended Exercises

1. Add a second hand (6° per second, thinner/longer, yellow).
2. Use real time: `machine.RTC().datetime()` gives `(year, month, day, weekday, hour,
   minute, second, μs)` — set it once from the REPL, then display it.
3. Get true wall-clock time from WiFi: `import ntptime; ntptime.settime()` after
   connecting with `network.WLAN`.
4. Draw the 12 hour numbers around the face with `hand_end(i * 30, RADIUS + 15)`.

## FAQ

**The hands look jagged.** Diagonal lines on a low-res panel are stairsteps — normal.
For smoother hands, draw two parallel lines one pixel apart.

**Erasing a hand nicked a tick mark.** That's why the loop calls `draw_face()` after
erasing — cheap insurance that restores anything the black line clipped.

---

**You made it!** Back to the [tutorial overview](../README.md) — or connect a sensor
and build something of your own. 🎉

Previous: [Lesson 10: Notification](../Lesson10_Notification/README.md)
