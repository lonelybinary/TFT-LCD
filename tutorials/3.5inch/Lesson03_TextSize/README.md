# Lesson 03: Text Size

## Course Objectives

Learn how to control text size and understand the impact of different sizes on display effects.

## Key Concepts

### 1. Set Text Size

Use the `setTextSize(size)` function to set text size:

```cpp
gfx->setTextSize(1);  // Minimum size (default)
gfx->setTextSize(2);  // 2x size
gfx->setTextSize(3);  // 3x size
// ... up to 8
```

**Text Size Range**: 1-8
- Size 1: Smallest, suitable for displaying large amounts of text
- Size 2-3: Medium, suitable for titles and important information
- Size 4-8: Very large, suitable for emphasis and displaying large numbers

### 2. Size Impact on Dimensions

Text size affects:
- **Character Width**: Approximately `size × 6` pixels
- **Character Height**: Approximately `size × 8` pixels
- **Line Spacing**: Needs adjustment based on size

**Example**:
```cpp
gfx->setTextSize(1);  // Characters approximately 6×8 pixels
gfx->setTextSize(2);  // Characters approximately 12×16 pixels
gfx->setTextSize(3);  // Characters approximately 18×24 pixels
```

### 3. Multi-line Text Size

When displaying multi-line text, adjust Y coordinates based on size:

```cpp
int y = 20;
for (int size = 1; size <= 5; size++) {
  gfx->setTextSize(size);
  gfx->setCursor(20, y);
  gfx->println("Text");
  y += size * 8 + 5;  // Adjust next line position based on size
}
```

### 4. Mixed Size Text

You can use different text sizes on the same screen:

```cpp
// Large title
gfx->setTextSize(3);
gfx->setCursor(80, 30);
gfx->println("TITLE");

// Small body text
gfx->setTextSize(1);
gfx->setCursor(20, 150);
gfx->println("Body text");
```

## Code Explanation

### Basic Size Setting

```cpp
gfx->setTextSize(1);
gfx->setCursor(20, 20);
gfx->println("Size 1");
```

### Size Comparison Display

```cpp
for (int size = 1; size <= 5; size++) {
  gfx->setTextSize(size);
  gfx->setCursor(20, y);
  gfx->print("Size ");
  gfx->println(size);
  y += size * 8 + 5;  // Adjust Y position
}
```

### Center Display (Considering Size)

```cpp
int size = 3;
gfx->setTextSize(size);
int textWidth = strlen("TEXT") * size * 6;  // Estimate width
int x = (gfx->width() - textWidth) / 2;
int y = (gfx->height() - size * 8) / 2;
gfx->setCursor(x, y);
gfx->println("TEXT");
```

## Expected Result

1. **Different Size Display**: Display text of Size 1, 2, 3, 4 sequentially
2. **Size Comparison**: Compare different text sizes on the same screen
3. **Number Display**: Display numbers in different sizes
4. **Mixed Sizes**: Use different sizes for title, subtitle, and body text
5. **Dynamic Changes**: Text size dynamically changes from 1 to 5

## Extended Exercises

1. **Create Title Style Function**:
   ```cpp
   void drawTitle(const char* text, int y, uint16_t color) {
     gfx->setTextSize(3);
     gfx->setTextColor(color);
     // Center display...
   }
   ```

2. **Number Display Function**:
   ```cpp
   void drawLargeNumber(int number, int x, int y) {
     gfx->setTextSize(4);
     gfx->setCursor(x, y);
     gfx->println(number);
   }
   ```

3. **Adaptive Size**:
   ```cpp
   // Automatically adjust size based on text length to ensure it doesn't exceed screen
   int calculateSize(const char* text, int maxWidth) {
     int len = strlen(text);
     for (int size = 8; size >= 1; size--) {
       if (len * size * 6 <= maxWidth) {
         return size;
       }
     }
     return 1;
   }
   ```

## Frequently Asked Questions

**Q: What is the maximum text size?**
- Theoretically can be set to 8, but actually limited by screen size
- 3.5-inch display (320x480) can use larger text, recommended maximum size 5-6

**Q: How to accurately calculate text width?**
- Text width = character count × size × 6 (estimate)
- Actual width may vary by character (numbers are usually narrower than letters)

**Q: Large text not fully displayed?**
- Check if text exceeds screen range
- Use `gfx->width()` and `gfx->height()` to check screen dimensions
- Consider reducing text size or shortening text content

## Next Step

After completing this lesson, you can continue with:
- [Lesson 04: Text Style](../Lesson04_TextStyle/README.md) - Learn text styles
