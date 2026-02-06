# Lesson 04: Text Style

## Course Objectives

Learn how to set text styles, including foreground and background colors, creating various visual effects.

## Key Concepts

### 1. Set Text Color

#### Set Only Foreground Color (Text Color)

```cpp
gfx->setTextColor(WHITE);  // Set only text color
```

Text will be displayed on the current screen background.

#### Set Both Foreground and Background Colors

```cpp
gfx->setTextColor(foreground, background);
gfx->setTextColor(WHITE, RED);  // White text, red background
```

**Parameter Description**:
- First parameter: Foreground color (text color)
- Second parameter: Background color (text background)

### 2. Color Combination Principles

#### High Contrast Combinations (Recommended)
- White text + Black background
- Black text + White background
- Yellow text + Blue background

#### Low Contrast Combinations (Not Recommended)
- Light text + Light background
- Dark text + Dark background

### 3. Two Methods to Create Text Background

#### Method 1: Use setTextColor to Set Background

```cpp
gfx->setTextColor(WHITE, RED);
gfx->setCursor(50, 30);
gfx->println("Text");
```

**Advantages**: Simple, automatically handles background
**Disadvantages**: Background only covers text area

#### Method 2: Draw Background Rectangle First

```cpp
gfx->fillRect(20, 100, 150, 30, GREEN);  // Draw background
gfx->setTextColor(BLACK);
gfx->setCursor(50, 110);
gfx->println("Text");
```

**Advantages**: Can control background size and position
**Disadvantages**: Need to manually calculate position

### 4. Create Label Effect

Labels are common UI elements that can be created by combining background and text colors:

```cpp
// Success label (green background)
gfx->fillRect(50, 50, 120, 35, GREEN);
gfx->setTextColor(BLACK);
gfx->setCursor(60, 60);
gfx->println("SUCCESS");

// Error label (red background)
gfx->fillRect(50, 150, 120, 35, RED);
gfx->setTextColor(WHITE);
gfx->setCursor(60, 160);
gfx->println("ERROR");
```

## Code Explanation

### Basic Text Color Setting

```cpp
// Set only foreground color
gfx->setTextColor(WHITE);
gfx->println("White text");

// Set foreground and background colors
gfx->setTextColor(WHITE, RED);
gfx->println("White on Red");
```

### Create Label

```cpp
// Draw background rectangle
gfx->fillRect(50, 50, 120, 35, GREEN);

// Set text color
gfx->setTextColor(BLACK);

// Display text (note Y coordinate needs fine-tuning)
gfx->setCursor(60, 60);
gfx->println("SUCCESS");
```

### Text Highlight

```cpp
// Draw highlight background
gfx->fillRect(0, 100, 320, 40, CYAN);

// Display text
gfx->setTextColor(BLACK);
gfx->setCursor(50, 110);
gfx->println("Highlighted");
```

## Expected Result

1. **Foreground Color Demo**: Display text in different colors
2. **Foreground + Background**: Display text with background color
3. **Color Combinations**: Show various color combination effects
4. **Text Area Background**: Demonstrate different background creation methods
5. **Label Effects**: Create success, warning, error, info labels
6. **Highlight Effect**: Create text highlight rows

## Extended Exercises

1. **Create Status Indicator**:
   ```cpp
   void drawStatus(const char* text, int status, int x, int y) {
     // status: 0=success(green), 1=warning(yellow), 2=error(red)
     uint16_t colors[] = {GREEN, YELLOW, RED};
     gfx->fillRect(x, y, 100, 40, colors[status]);
     gfx->setTextColor(BLACK);
     gfx->setCursor(x+10, y+10);
     gfx->println(text);
   }
   ```

2. **Create Button Effect**:
   ```cpp
   void drawButton(const char* text, int x, int y, int w, int h) {
     // Draw button background
     gfx->fillRect(x, y, w, h, BLUE);
     // Draw border
     gfx->drawRect(x, y, w, h, WHITE);
     // Center display text
     gfx->setTextColor(WHITE);
     // Calculate center position...
   }
   ```

## Frequently Asked Questions

**Q: Background color not showing?**
- Confirm using two-parameter `setTextColor(foreground, background)`
- Check if background color is the same as screen background color

**Q: Text background size incorrect?**
- `setTextColor` background only covers text area
- If larger background is needed, use `fillRect()` to draw background first

**Q: Text position doesn't match background?**
- When using `fillRect()`, need to manually calculate text position
- Y coordinate usually needs fine-tuning (+5 to +10 pixels, depending on text size)

## Next Step

After completing this lesson, you can continue with:
- [Lesson 05: Graphics](../Lesson05_Graphics/README.md) - Learn graphics drawing
