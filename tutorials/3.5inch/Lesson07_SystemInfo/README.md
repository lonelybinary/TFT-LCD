# Lesson 07: System Info Display

## Course Objectives

Learn to create a system information display interface and master UI component design and information layout.

## Key Concepts

### 1. UI Component Design

#### Label
Text with background color for status display:

```cpp
drawLabel("ONLINE", 150, 95, GREEN, BLACK, 2);
```

#### Progress Bar
Display percentage or progress:

```cpp
drawProgressBar(150, 220, 200, 20, 75, WHITE, GREEN);
```

#### Separator
Used to separate different areas:

```cpp
drawSeparator(60, CYAN);
```

### 2. Information Layout

#### Hierarchy
- **Title Area**: Top, use larger font and eye-catching colors
- **Content Area**: Middle, main information display
- **Status Area**: Bottom, status indicators

#### Color Usage
- **Primary Color**: For titles (YELLOW)
- **Secondary Color**: For separators (CYAN)
- **Status Colors**: Green (success/online), Gray (weak signal)

### 3. Status Indicators

#### Signal Strength Indicator
Use multiple rectangular bars to represent signal strength:

```cpp
for (int i = 0; i < 4; i++) {
  int barHeight = (i + 1) * 8;
  uint16_t color = (i < 3) ? GREEN : gfx->color565(128, 128, 128);
  gfx->fillRect(150 + i * 12, 280 + (20 - barHeight), 10, barHeight, color);
}
```

## Code Explanation

### Helper Functions

```cpp
// Draw label
void drawLabel(const char* text, int x, int y, uint16_t bgColor, uint16_t textColor, int textSize = 2) {
  int textWidth = strlen(text) * 6 * textSize;
  int textHeight = 8 * textSize;
  gfx->fillRect(x, y, textWidth + 8, textHeight + 4, bgColor);
  gfx->setTextColor(textColor);
  gfx->setTextSize(textSize);
  gfx->setCursor(x + 4, y + 4);
  gfx->println(text);
}

// Draw progress bar
void drawProgressBar(int x, int y, int width, int height, int percent, uint16_t bgColor, uint16_t fillColor) {
  gfx->drawRect(x, y, width, height, bgColor);
  int fillWidth = (width * percent) / 100;
  if (fillWidth > 0) {
    gfx->fillRect(x + 2, y + 2, fillWidth - 4, height - 4, fillColor);
  }
}
```

### Interface Layout

```cpp
// Title
drawCenteredText("SYSTEM INFO", 20, YELLOW, 2);

// Separator
drawSeparator(60, CYAN);

// Status label
drawLabel("ONLINE", 150, 95, GREEN, BLACK, 2);

// Progress bar
drawProgressBar(150, 220, 200, 20, 75, WHITE, GREEN);
```

## Expected Result

Display system information interface, including:
- System status (online/offline)
- Temperature display
- Battery level (progress bar)
- Signal strength (multi-level indicator)

## Extended Exercises

1. **Add More Information Items**:
   - Memory usage
   - CPU usage
   - Network status

2. **Implement Data Updates**:
   ```cpp
   void updateSystemInfo() {
     // Update temperature, battery, etc.
   }
   ```

3. **Optimize Layout**:
   - Adjust spacing
   - Add icons
   - Improve color matching

## Frequently Asked Questions

**Q: How to create custom colors?**
- Use `gfx->color565(r, g, b)` to create RGB565 colors
- r, g, b range: 0-31, 0-63, 0-31

**Q: How to adjust progress bar width?**
- Modify `width` parameter in `drawProgressBar` function
- Ensure `fillWidth` calculation is correct

## Next Step

After completing this course, you can:
- Create your own information display interface
- Combine with sensors to display real-time data
- Add data update functionality
