# Lesson 11: Clock Display

## Course Objectives

Learn to create a clock display interface and master analog clock drawing and digital time display.

## Key Concepts

### 1. Analog Clock Drawing

#### Clock Outer Circle
Use circle to draw clock outer circle:

```cpp
int centerX = 160;  // Screen width center
int centerY = 240;  // Screen height center
int radius = 100;   // Clock radius
gfx->drawCircle(centerX, centerY, radius, WHITE);
```

#### Clock Marks
Use trigonometric functions to calculate mark positions:

```cpp
for (int i = 0; i < 12; i++) {
  float angle = i * PI / 6 - PI / 2;  // 12 marks, each 30 degrees
  int x1 = centerX + (radius - 5) * cos(angle);
  int y1 = centerY + (radius - 5) * sin(angle);
  int x2 = centerX + (radius - 20) * cos(angle);
  int y2 = centerY + (radius - 20) * sin(angle);
  gfx->drawLine(x1, y1, x2, y2, WHITE);
}
```

### 2. Hour and Minute Hands

#### Hour Hand (Pointing to 3 o'clock)
Horizontal to the right:

```cpp
gfx->drawLine(centerX, centerY, centerX + 40, centerY, RED);
```

#### Minute Hand (Pointing to 12 o'clock)
Vertical upward:

```cpp
gfx->drawLine(centerX, centerY, centerX, centerY - 60, GREEN);
```

### 3. Clock Center Point

Use filled circle to draw center point:

```cpp
gfx->fillCircle(centerX, centerY, 5, WHITE);
```

### 4. Digital Time Display

Display digital time below the clock:

```cpp
drawCenteredText("12:00", 380, WHITE, 3);
```

### 5. Math Function Usage

Need to include `<math.h>` header file:

```cpp
#include <math.h>
```

Use `cos()` and `sin()` functions to calculate angles.

## Code Explanation

### Clock Mark Calculation

```cpp
// Clock marks (12 marks)
for (int i = 0; i < 12; i++) {
  float angle = i * PI / 6 - PI / 2;  // Convert to radians, -PI/2 makes 12 o'clock at top
  int x1 = centerX + (radius - 5) * cos(angle);   // Outer mark endpoint
  int y1 = centerY + (radius - 5) * sin(angle);
  int x2 = centerX + (radius - 20) * cos(angle);  // Inner mark endpoint
  int y2 = centerY + (radius - 20) * sin(angle);
  gfx->drawLine(x1, y1, x2, y2, WHITE);
}
```

### Hand Drawing

```cpp
// Hour hand (pointing to 3 o'clock, horizontal to right)
gfx->drawLine(centerX, centerY, centerX + 40, centerY, RED);

// Minute hand (pointing to 12 o'clock, vertical upward)
gfx->drawLine(centerX, centerY, centerX, centerY - 60, GREEN);
```

## Expected Result

Display clock interface, including:
- White circular outer circle
- 12 clock marks
- Red hour hand (pointing to 3 o'clock)
- Green minute hand (pointing to 12 o'clock)
- White center point
- Digital time display (12:00)

## Extended Exercises

1. **Implement Real-Time Clock**:
   ```cpp
   void updateClock() {
     // Get current time
     // Calculate hour and minute hand angles
     // Update display
   }
   ```

2. **Add Second Hand**:
   - Draw second hand
   - Update every second

3. **Add Date Display**:
   - Display date below clock
   - Format date string

## Frequently Asked Questions

**Q: How to calculate hand angles?**
- Hour hand angle: `hour * 30 + minute * 0.5` (30 degrees per hour)
- Minute hand angle: `minute * 6` (6 degrees per minute)
- Second hand angle: `second * 6` (6 degrees per second)

**Q: Why use `-PI/2`?**
- Makes 12 o'clock position at top (negative Y direction)
- Conforms to traditional clock layout

**Q: How to implement hand rotation?**
- Use `cos()` and `sin()` to calculate hand endpoint coordinates
- Calculate angle based on time

## Next Step

After completing this course, you can:
- Create real-time clock application
- Add alarm function
- Implement multi-timezone display

## Tutorial Completion

Congratulations on completing all tutorials for the 3.5-inch TFT-LCD display! You have now mastered:
- ✅ Display initialization and basic operations
- ✅ Text display and style settings
- ✅ Color usage and graphics drawing
- ✅ Screen rotation and layout design
- ✅ UI interface design and component creation
- ✅ Practical application case development

Keep exploring and create your own amazing projects! 🚀
