# Lesson 11: Clock Display

## Course Objectives

Build the final project: an **analog clock face**. You'll draw the circle, the tick marks,
and the hands — using a little trigonometry to place things around a circle.

## Key Concepts

### 1. Drawing the clock face

#### The outer circle
Pick a center point and a radius, then draw a circle:

```cpp
int centerX = 160;  // middle of the 320-wide screen
int centerY = 240;  // middle of the 480-tall screen
int radius = 100;   // clock size
gfx->drawCircle(centerX, centerY, radius, WHITE);
```

#### The 12 tick marks
There are 12 marks evenly spaced around the circle. We use `sin()` and `cos()` to find each
mark's position. Don't worry if the math feels new — the pattern below is all you need:

```cpp
for (int i = 0; i < 12; i++) {
  float angle = i * PI / 6 - PI / 2;   // 12 steps around the circle
  int x1 = centerX + (radius - 5) * cos(angle);   // outer end of the tick
  int y1 = centerY + (radius - 5) * sin(angle);
  int x2 = centerX + (radius - 20) * cos(angle);  // inner end of the tick
  int y2 = centerY + (radius - 20) * sin(angle);
  gfx->drawLine(x1, y1, x2, y2, WHITE);
}
```

### 2. The hands

This example draws fixed hands (pointing to a set time) so you can see how they work.

#### Hour hand — pointing to 3 o'clock (straight right)

```cpp
gfx->drawLine(centerX, centerY, centerX + 40, centerY, RED);
```

#### Minute hand — pointing to 12 o'clock (straight up)

```cpp
gfx->drawLine(centerX, centerY, centerX, centerY - 60, GREEN);
```

### 3. The center dot

A small filled circle covers where the hands meet:

```cpp
gfx->fillCircle(centerX, centerY, 5, WHITE);
```

### 4. A digital time too

You can show a digital readout under the clock:

```cpp
drawCenteredText("12:00", 380, WHITE, 3);
```

### 5. The math header

`sin()` and `cos()` come from the math library, so include it at the top of the sketch:

```cpp
#include <math.h>
```

## Code Explanation

### Placing the tick marks

```cpp
for (int i = 0; i < 12; i++) {
  float angle = i * PI / 6 - PI / 2;  // -PI/2 puts mark 0 at the top (12 o'clock)
  int x1 = centerX + (radius - 5) * cos(angle);   // outer point
  int y1 = centerY + (radius - 5) * sin(angle);
  int x2 = centerX + (radius - 20) * cos(angle);  // inner point
  int y2 = centerY + (radius - 20) * sin(angle);
  gfx->drawLine(x1, y1, x2, y2, WHITE);
}
```

### Drawing the hands

```cpp
// Hour hand (to 3 o'clock — horizontal, right)
gfx->drawLine(centerX, centerY, centerX + 40, centerY, RED);

// Minute hand (to 12 o'clock — vertical, up)
gfx->drawLine(centerX, centerY, centerX, centerY - 60, GREEN);
```

## Expected Result

A clock screen showing:
- A white circle
- 12 tick marks
- A red hour hand (pointing to 3)
- A green minute hand (pointing to 12)
- A white center dot
- A digital time (12:00) below

## Extended Exercises

1. **Make it tick** — compute the hand angles from the real time and redraw:
   ```cpp
   void updateClock() {
     // get the current time
     // work out the hour and minute angles
     // redraw the hands
   }
   ```

2. **Add a second hand** that updates every second.

3. **Add the date** below the clock.

## Frequently Asked Questions

**Q: How do I work out the hand angles from a time?**
- Hour hand: `hour * 30 + minute * 0.5` (30° per hour, drifting as the minutes pass)
- Minute hand: `minute * 6` (6° per minute)
- Second hand: `second * 6` (6° per second)

**Q: Why subtract `PI/2`?**
- It rotates everything so position 0 sits at the top (12 o'clock) instead of at 3 o'clock,
  matching a real clock.

**Q: How do I make a hand point to an angle?**
- Use the same `cos()`/`sin()` pattern as the tick marks to find the hand's end point, then
  draw a line from the center to that point.

## Next Step

There's no next lesson — this was the last one!

## Tutorial Complete

Congratulations — you've finished all 11 lessons for the 3.5-inch TFT-LCD display! You can now:
- ✅ Initialize the display and do the basics
- ✅ Show text and style it
- ✅ Use colors and draw shapes
- ✅ Rotate the screen and plan layouts
- ✅ Build real interfaces: info screens, menus, dashboards, notifications, and a clock
- ✅ Wrap common drawing code into reusable helper functions

Keep going — connect a sensor, add a button, or adapt these lessons to a different display
size. Have fun building your own projects! 🚀
