# Lesson 09: Data Monitoring Interface

## Course Objectives

Learn to create a data monitoring interface and master card-style layout and data visualization.

## Key Concepts

### 1. Card-Style Layout

Use rectangular borders to create cards:

```cpp
gfx->drawRect(30, 100, 120, 100, CYAN);
```

#### Card Layout Principles
- **Left-Right Arrangement**: Two cards displayed side by side
- **Uniform Size**: Keep card sizes consistent
- **Appropriate Spacing**: Leave spacing between cards

### 2. Data Visualization

#### Progress Bar Display Percentage
Use progress bar to visually display data:

```cpp
drawProgressBar(40, 170, 100, 15, 45, CYAN, GREEN);
```

#### Large Font Display Values
Use larger font to highlight data:

```cpp
gfx->setTextSize(3);
gfx->println("45%");
```

### 3. Multi-Card Design

#### Card 1 (CPU)
- Position: Left side (x=30)
- Border color: CYAN
- Data: 45%

#### Card 2 (MEM)
- Position: Right side (x=170)
- Border color: YELLOW
- Data: 62%

### 4. Status Indication

Use label to display overall status:

```cpp
drawLabel("OK", 150, 225, GREEN, BLACK, 2);
```

## Code Explanation

### Card Drawing

```cpp
// Data card 1 (left side)
gfx->drawRect(30, 100, 120, 100, CYAN);
gfx->setTextColor(CYAN);
gfx->setTextSize(2);
gfx->setCursor(40, 110);
gfx->println("CPU");
gfx->setTextColor(WHITE);
gfx->setTextSize(3);
gfx->setCursor(40, 140);
gfx->println("45%");
drawProgressBar(40, 170, 100, 15, 45, CYAN, GREEN);
```

### Progress Bar Visualization

```cpp
void drawProgressBar(int x, int y, int width, int height, int percent, uint16_t bgColor, uint16_t fillColor) {
  gfx->drawRect(x, y, width, height, bgColor);
  int fillWidth = (width * percent) / 100;
  if (fillWidth > 0) {
    gfx->fillRect(x + 2, y + 2, fillWidth - 4, height - 4, fillColor);
  }
}
```

## Expected Result

Display data monitoring interface, including:
- Title and separator
- CPU usage card (45%)
- Memory usage card (62%)
- Status indicator (OK)

## Extended Exercises

1. **Add More Data Cards**:
   - Disk usage
   - Network traffic
   - Temperature monitoring

2. **Implement Real-Time Updates**:
   ```cpp
   void updateMonitoringData() {
     // Update CPU, memory, etc. data
   }
   ```

3. **Add Chart Display**:
   - Line chart
   - Bar chart
   - Pie chart

## Frequently Asked Questions

**Q: How to adjust card size?**
- Modify width and height parameters in `drawRect` function
- Ensure content fits card size

**Q: How to add more cards?**
- Calculate card positions (consider screen width)
- Can create multi-row layout

## Next Step

After completing this course, you can:
- Create your own monitoring interface
- Combine with sensors to display real-time data
- Implement data recording and display
