# 2.8-inch Display Adaptation Guide

This guide provides detailed instructions on how to adapt 3.5-inch tutorial code to the 2.8-inch display.

## Display Specifications

| Parameter | Value | Description |
|-----------|-------|-------------|
| **Display Size** | 2.8 inch | Medium to large size display |
| **Driver IC** | ST7789 | Use `Arduino_ST7789` class |
| **Resolution** | 240 x 320 | Width 240 pixels, Height 320 pixels |
| **IPS Parameter** | `true` | IPS display |
| **Column Offset** | 0, 0 | Usually no offset needed |
| **Row Offset** | 0, 0 | Usually no offset needed |
| **Backlight Control** | On/Off (Active High) | `digitalWrite(BLK, HIGH)`=ON |
| **Color Mode** | RGB565 | 16-bit color depth |

## Key Differences

### 1. Resolution Difference
- **3.5-inch**: 320 x 480 pixels
- **2.8-inch**: 240 x 320 pixels
- **Ratio**: Width approximately 3/4, Height approximately 2/3

**Note**: 2.8-inch has the same resolution as 2.0-inch and 2.4-inch, adaptation method is the same.

### 2. Driver IC Difference
- **3.5-inch**: ST7796 (`Arduino_ST7796` class)
- **2.8-inch**: ST7789 (`Arduino_ST7789` class)

### 3. Backlight Control
- 2.8-inch is the same as 3.5-inch, On/Off only

## Code Modification Steps

### Step 1: Modify LCD Object Initialization

**3.5-inch (Tutorial Default)**:
```cpp
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);
```

**2.8-inch Adaptation**:
```cpp
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 0, true /* IPS */, 240, 320, 0, 0, 0, 0);
```

**Modification Notes**:
1. Driver class: `Arduino_ST7796` → `Arduino_ST7789`
2. IPS parameter: Keep `true` (IPS display)
3. Resolution: `320, 480` → `240, 320`
4. Offset: Keep `0, 0, 0, 0`

### Step 2: Backlight Control (Same as 3.5-inch)

**2.8-inch (On/Off, Active High)**:
```cpp
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
```

**Note**: 2.8-inch backlight control is exactly the same as 3.5-inch.

### Step 3: Adjust Coordinates and Dimensions

#### Coordinate Conversion Formula

```
New X coordinate = Original X coordinate × (New width / Original width)
New Y coordinate = Original Y coordinate × (New height / Original height)
```

**2.8-inch Conversion Ratio**:
- X coordinate ratio: 240 / 320 = 0.75 (scale down to 3/4)
- Y coordinate ratio: 320 / 480 = 0.667 (scale down to 2/3)

#### Coordinate Conversion Examples

| 3.5-inch Coordinates | 2.8-inch Coordinates | Calculation Process |
|----------------------|---------------------|---------------------|
| (50, 200) | (38, 133) | 50×0.75=37.5≈38, 200×0.667=133.4≈133 |
| (100, 300) | (75, 200) | 100×0.75=75, 300×0.667=200 |
| (160, 240) | (120, 160) | 160×0.75=120, 240×0.667=160 |
| (320, 480) | (240, 320) | 320×0.75=240, 480×0.667=320 |

#### Dimension Conversion Examples

| 3.5-inch Dimensions | 2.8-inch Dimensions | Calculation Process |
|---------------------|---------------------|---------------------|
| Width 100 | Width 75 | 100×0.75=75 |
| Height 50 | Height 33 | 50×0.667=33.35≈33 |
| Radius 50 | Radius 33 | 50×0.667=33.35≈33 |

### Step 4: Adjust Text Size

**Text Size Recommendations**:

| 3.5-inch Text Size | 2.8-inch Recommended Size | Notes |
|---------------------|--------------------------|-------|
| size 3 | size 2-3 | Large title can keep size 3 |
| size 2 | size 2 | Medium text remains unchanged |
| size 1 | size 1 | Small text remains unchanged |

**Text Width Estimation**:
- Text width ≈ Character count × size × 6
- Example: "Hello World" (12 characters)
  - size 3: 12 × 3 × 6 = 216 pixels (fits 2.8-inch width 240)
  - size 2: 12 × 2 × 6 = 144 pixels (fits 2.8-inch width 240)
  - size 1: 12 × 1 × 6 = 72 pixels (fits 2.8-inch width 240)

## Complete Code Comparison Examples

### Example 1: Hello World (Lesson 01)

**3.5-inch Code**:
```cpp
// LCD object initialization
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true, 320, 480, 0, 0, 0, 0);

// Backlight control (On/Off)
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);

// Display text
gfx->setTextColor(WHITE);
gfx->setCursor(50, 200);
gfx->setTextSize(3);
gfx->println("Hello World");
```

**2.8-inch Adapted Code**:
```cpp
// LCD object initialization
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 0, true, 240, 320, 0, 0, 0, 0);

// Backlight control (same as 3.5-inch, On/Off)
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);

// Display text (coordinates adjusted proportionally, text size can keep size 3)
gfx->setTextColor(WHITE);
gfx->setCursor(38, 133);  // 50×0.75=37.5≈38, 200×0.667=133.4≈133
gfx->setTextSize(3);      // size 3 can be kept (optional size 2)
gfx->println("Hello World");
```

### Example 2: Draw Rectangle (Lesson 05)

**3.5-inch Code**:
```cpp
// Draw rectangle: top-left corner (50, 100), width 200, height 150
gfx->drawRect(50, 100, 200, 150, RED);
```

**2.8-inch Adapted Code**:
```cpp
// Draw rectangle: top-left corner (38, 67), width 150, height 100
// 50×0.75=37.5≈38, 100×0.667=66.7≈67
// 200×0.75=150, 150×0.667=100.05≈100
gfx->drawRect(38, 67, 150, 100, RED);
```

### Example 3: Draw Circle (Lesson 05)

**3.5-inch Code**:
```cpp
// Draw circle: center (160, 240), radius 50
gfx->drawCircle(160, 240, 50, BLUE);
```

**2.8-inch Adapted Code**:
```cpp
// Draw circle: center (120, 160), radius 33
// 160×0.75=120, 240×0.667=160.08≈160
// 50×0.667=33.35≈33
gfx->drawCircle(120, 160, 33, BLUE);
```

## Special Notes

### 1. Moderate to Large Display Size
- Width 240 pixels, Height 320 pixels
- Physical size is larger, but resolution is the same as 2.0/2.4-inch
- Recommendations:
  - Text size can use size 1-4
  - UI design can be richer
  - Suitable for displaying multiple lines of text and graphics

### 2. Center Display Calculation
```cpp
// 3.5-inch center text
int textWidth = strlen("Text") * 3 * 6;  // Estimate width
int x = (320 - textWidth) / 2;
int y = (480 - 24) / 2;  // 24 is text height for size 3

// 2.8-inch center text
int textWidth = strlen("Text") * 3 * 6;  // Estimate width
int x = (240 - textWidth) / 2;
int y = (320 - 24) / 2;  // 24 is text height for size 3
```

### 3. Multi-line Text Layout
```cpp
// 3.5-inch multi-line text
gfx->setCursor(50, 100);
gfx->println("Line 1");
gfx->setCursor(50, 150);
gfx->println("Line 2");

// 2.8-inch multi-line text (adjusted proportionally)
gfx->setCursor(38, 67);  // 50×0.75=38, 100×0.667=67
gfx->println("Line 1");
gfx->setCursor(38, 100); // 50×0.75=38, 150×0.667=100
gfx->println("Line 2");
```

## Frequently Asked Questions

### Q1: How to accurately convert coordinates?
**A**: Use formula calculation:
```cpp
// Define conversion functions
int convertX(int x35) {
  return (int)(x35 * 240.0 / 320.0);
}

int convertY(int y35) {
  return (int)(y35 * 320.0 / 480.0);
}

// Usage
int x = convertX(50);  // 3.5-inch's 50 → 2.8-inch's 38
int y = convertY(200); // 3.5-inch's 200 → 2.8-inch's 133
```

### Q2: How to choose text size?
**A**: 
- size 1: Suitable for displaying large amounts of text
- size 2: Suitable for titles and important information (recommended)
- size 3: Suitable for large titles, can be kept
- size 4: Suitable for extra large titles, but may be large

### Q3: Display position offset?
**A**: 
- 2.8-inch usually doesn't need offset
- If display position is incorrect, check if coordinate conversion is correct
- Reference test program: `2.8inch/code/2.8inch_Test/2.8inch_Test.ino`

### Q4: How to adapt UI interface?
**A**: 
- 2.8-inch display has larger physical size, but resolution is the same as 2.0/2.4-inch
- Recommendations:
  - Use card-style layout
  - Make reasonable use of space
  - Maintain appropriate spacing
  - Can use slightly larger text

## Practical Adaptation Cases

### Case 1: Adapt Lesson 01 (Hello World)

**Original Code (3.5-inch)**:
```cpp
gfx->setCursor(50, 200);
gfx->setTextSize(3);
gfx->println("Hello World");
```

**Adapted (2.8-inch)**:
```cpp
gfx->setCursor(38, 133);  // Coordinate conversion
gfx->setTextSize(3);     // Text size can keep size 3
gfx->println("Hello World");
```

### Case 2: Adapt Lesson 05 (Graphics)

**Original Code (3.5-inch)**:
```cpp
// Draw progress bar
gfx->drawRect(20, 200, 280, 40, WHITE);
gfx->fillRect(20, 200, 140, 40, GREEN);  // 50%
```

**Adapted (2.8-inch)**:
```cpp
// Draw progress bar (scaled down proportionally)
gfx->drawRect(15, 133, 210, 27, WHITE);     // 20×0.75=15, 200×0.667=133, 280×0.75=210, 40×0.667=27
gfx->fillRect(15, 133, 105, 27, GREEN);     // 50% = 210×0.5=105
```

### Case 3: Adapt Lesson 07 (System Info)

**Original Code (3.5-inch)**:
```cpp
// Title
drawCenteredText("SYSTEM INFO", 20, YELLOW, 2);

// Label
drawLabel("ONLINE", 150, 95, GREEN, BLACK, 2);
```

**Adapted (2.8-inch)**:
```cpp
// Title (Y coordinate adjusted)
drawCenteredText("SYSTEM INFO", 13, YELLOW, 2);  // 20×0.667=13.34≈13

// Label (coordinates adjusted)
drawLabel("ONLINE", 113, 63, GREEN, BLACK, 2);   // 150×0.75=112.5≈113, 95×0.667=63.365≈63
```

## Reference Resources

- **Test Program**: `2.8inch/code/2.8inch_Test/2.8inch_Test.ino`
- **Display README**: `2.8inch/README.md`
- **3.5-inch Tutorial**: `tutorials/3.5inch/`

## Quick Checklist

After adaptation, check the following items:

- [ ] LCD object initialization modified (`Arduino_ST7789`, resolution `240, 320`)
- [ ] IPS parameter set to `true`
- [ ] Backlight control uses On/Off (`digitalWrite(TFT_BACKLIGHT, HIGH)` = ON)
- [ ] All coordinates converted proportionally (X×0.75, Y×0.667)
- [ ] Text size adjusted (recommended size 1-4)
- [ ] Graphics dimensions scaled down proportionally
- [ ] Display shows correctly, no offset
- [ ] Backlight is ON

---

**Tip**: 2.8-inch display adaptation is the same as 2.0/2.4-inch, mainly modify driver class and resolution, convert coordinates proportionally. Due to larger physical size, can use slightly larger text.
