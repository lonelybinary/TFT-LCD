# Lesson 06: Rotation

## Course Objectives

Learn how to rotate the display orientation and understand the impact of different rotation angles on display effects.

## Key Concepts

### 1. Set Rotation Angle

Use the `setRotation(angle)` function to set screen rotation angle:

```cpp
gfx->setRotation(0);  // 0 degrees (default, portrait)
gfx->setRotation(1);  // 90 degrees (clockwise)
gfx->setRotation(2);  // 180 degrees
gfx->setRotation(3);  // 270 degrees (counterclockwise 90 degrees)
```

**Rotation Angle Description**:
- **0 degrees (rotation = 0)**: Default direction, portrait mode
  - Width: 320 pixels, Height: 480 pixels
  - Origin at top-left corner
  
- **90 degrees (rotation = 1)**: Clockwise rotation 90 degrees
  - Width: 480 pixels, Height: 320 pixels
  - Origin at top-right corner (from user's perspective)
  
- **180 degrees (rotation = 2)**: Rotation 180 degrees
  - Width: 320 pixels, Height: 480 pixels
  - Origin at bottom-right corner
  
- **270 degrees (rotation = 3)**: Counterclockwise 90 degrees (or clockwise 270 degrees)
  - Width: 480 pixels, Height: 320 pixels
  - Origin at bottom-left corner

### 2. Rotation Impact on Screen Dimensions

After rotation, `width()` and `height()` values change:

```cpp
gfx->setRotation(0);
int w0 = gfx->width();   // 320
int h0 = gfx->height();  // 480

gfx->setRotation(1);
int w1 = gfx->width();   // 480
int h1 = gfx->height();  // 320
```

**Important**: When rotating 90 or 270 degrees, width and height are swapped.

### 3. Rotation Impact on Coordinate System

After rotation, the coordinate system also changes:

```cpp
// Rotation 0: (0,0) at top-left corner
gfx->setRotation(0);
gfx->setCursor(0, 0);  // Top-left corner

// Rotation 1: (0,0) at top-right corner (from user's perspective)
gfx->setRotation(1);
gfx->setCursor(0, 0);  // Top-right corner

// Rotation 2: (0,0) at bottom-right corner
gfx->setRotation(2);
gfx->setCursor(0, 0);  // Bottom-right corner

// Rotation 3: (0,0) at bottom-left corner
gfx->setRotation(3);
gfx->setCursor(0, 0);  // Bottom-left corner
```

### 4. When to Use Rotation

**Use Cases**:
- Need landscape display (rotation = 1 or 3)
- Device installation direction changes
- Adapt to different display requirements

**Notes**:
- Need to recalculate positions after rotation
- Text and graphics positions will change
- Recommend setting rotation immediately after initialization

## Code Explanation

### Basic Rotation Setting

```cpp
// Set rotation angle
gfx->setRotation(1);  // 90 degrees

// Clear screen
gfx->fillScreen(BLACK);

// Display content (coordinate system has changed)
gfx->setCursor(50, 50);
gfx->println("Rotated");
```

### Dynamic Rotation Demo

```cpp
for (int rotation = 0; rotation < 4; rotation++) {
  gfx->setRotation(rotation);
  gfx->fillScreen(BLACK);
  
  // Display rotation information
  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  gfx->setCursor(50, 50);
  gfx->print("Rot: ");
  gfx->println(rotation);
  
  delay(3000);
}
```

## Expected Result

1. **All Rotation Angles**: Display four rotation angles 0, 1, 2, 3 sequentially
2. **Coordinate Axis Display**: Display X and Y axes, mark origin
3. **Same Content Different Angles**: Display same text at different rotation angles
4. **Graphics Rotation**: Display graphics effects at different rotation angles
5. **Angle Description**: Display rotation angle reference table

## Extended Exercises

1. **Adaptive Layout**:
   ```cpp
   // Automatically adjust layout based on rotation angle
   void drawAdaptiveLayout() {
     int w = gfx->width();
     int h = gfx->height();
     // Adjust layout based on w and h...
   }
   ```

2. **Portrait/Landscape Switching**:
   ```cpp
   // Implement automatic portrait/landscape switching
   bool isLandscape = (gfx->width() > gfx->height());
   if (isLandscape) {
     // Landscape layout
   } else {
     // Portrait layout
   }
   ```

3. **Rotation Animation**:
   ```cpp
   // Implement smooth rotation animation effect
   for (int r = 0; r < 4; r++) {
     gfx->setRotation(r);
     // Display content...
     delay(500);
   }
   ```

## Frequently Asked Questions

**Q: Content position incorrect after rotation?**
- Coordinate system changes after rotation, need to recalculate positions
- Use `width()` and `height()` to get current screen dimensions

**Q: How to keep content centered?**
- Use `width()` and `height()` to dynamically calculate center position
- Don't use fixed coordinate values

**Q: Does rotation affect performance?**
- Rotation itself doesn't affect performance
- But may need to redraw all content after rotation

## Next Step

After completing this lesson, you can continue with:
- [Lesson 07: System Info Display](../Lesson07_SystemInfo/README.md) - Learn to create system information display interface
