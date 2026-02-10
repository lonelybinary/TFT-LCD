# 0.96-inch Display Adaptation Guide

This guide provides detailed instructions on how to adapt 3.5-inch tutorial code to the 0.96-inch display.

## Display Specifications

| Parameter | Value | Description |
|-----------|-------|-------------|
| **Display Size** | 0.96 inch | Smallest size display |
| **Driver IC** | ST7735S | Use `Arduino_ST7735` class |
| **Resolution** | 80 x 160 | Width 80 pixels, Height 160 pixels |
| **IPS Parameter** | `false` | Normally black mode |
| **Column Offset 1** | 24 | For rotation 0/2 |
| **Column Offset 2** | 24 | For rotation 1/3 |
| **Row Offset** | 0, 0 | Usually 0 |
| **Backlight Control** | On/Off (Active Low) | `digitalWrite(BLK, LOW)`=ON, `HIGH`=OFF |
| **Color Mode** | RGB565 | 16-bit color depth |

## Key Differences

### 1. Resolution Difference
- **3.5-inch**: 320 x 480 pixels
- **0.96-inch**: 80 x 160 pixels
- **Ratio**: Width approximately 1/4, Height approximately 1/3

### 2. Backlight Control Difference (Important!)
- **3.5-inch**: On/Off (Active High), `digitalWrite(TFT_BACKLIGHT, HIGH)`=ON
- **0.96-inch**: On/Off (Active Low), `digitalWrite(TFT_BACKLIGHT, LOW)`=ON

### 3. Offset Difference
- **3.5-inch**: Offset `0, 0, 0, 0`
- **0.96-inch**: Offset `24, 0, 24, 0` (requires 24-pixel column offset)

## Code Modification Steps

### Step 1: Modify LCD Object Initialization

**3.5-inch (Tutorial Default)**:
```cpp
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);
```

**0.96-inch Adaptation**:
```cpp
Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0, false /* IPS */, 80, 160, 24, 0, 24, 0);
```

**Modification Notes**:
1. Driver class: `Arduino_ST7796` → `Arduino_ST7735`
2. IPS parameter: `true` → `false` (Normally black mode)
3. Resolution: `320, 480` → `80, 160`
4. Offset: `0, 0, 0, 0` → `24, 0, 24, 0`

### Step 2: Modify Backlight Control (Important!)

**3.5-inch (On/Off, Active High)**:
```cpp
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
```

**0.96-inch (On/Off, Active Low)**:
```cpp
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, LOW);   // ON (0.96 inch is Active Low)
```

**Important Notes**:
- 0.96-inch backlight is **Active Low**: LOW=ON, HIGH=OFF
- Other sizes are Active High: HIGH=ON, LOW=OFF
- 背光仅支持 On/Off，无亮度调节

### Step 3: Adjust Coordinates and Dimensions

#### Coordinate Conversion Formula

```
New X coordinate = Original X coordinate × (New width / Original width)
New Y coordinate = Original Y coordinate × (New height / Original height)
```

**0.96-inch Conversion Ratio**:
- X coordinate ratio: 80 / 320 = 0.25 (scale down to 1/4)
- Y coordinate ratio: 160 / 480 = 0.333 (scale down to 1/3)

#### Coordinate Conversion Examples

| 3.5-inch Coordinates | 0.96-inch Coordinates | Calculation Process |
|----------------------|------------------------|---------------------|
| (50, 200) | (12, 66) | 50×0.25=12.5≈12, 200×0.333=66.6≈66 |
| (100, 300) | (25, 100) | 100×0.25=25, 300×0.333=100 |
| (160, 240) | (40, 80) | 160×0.25=40, 240×0.333=80 |
| (320, 480) | (80, 160) | 320×0.25=80, 480×0.333=160 |

#### Dimension Conversion Examples

| 3.5-inch Dimensions | 0.96-inch Dimensions | Calculation Process |
|---------------------|----------------------|---------------------|
| Width 100 | Width 25 | 100×0.25=25 |
| Height 50 | Height 17 | 50×0.333=16.65≈17 |
| Radius 50 | Radius 17 | 50×0.333=16.65≈17 |

### Step 4: Adjust Text Size

**Text Size Recommendations**:

| 3.5-inch Text Size | 0.96-inch Recommended Size | Notes |
|---------------------|----------------------------|-------|
| size 3 | size 1 | Large title → Small title |
| size 2 | size 1 | Medium text → Small text |
| size 1 | size 1 | Small text remains unchanged |

**Text Width Estimation**:
- Text width ≈ Character count × size × 6
- Example: "Hello World" (12 characters)
  - size 3: 12 × 3 × 6 = 216 pixels (exceeds 0.96-inch width 80)
  - size 1: 12 × 1 × 6 = 72 pixels (fits 0.96-inch width 80)

## Complete Code Comparison Examples

### Example 1: Hello World (Lesson 01)

**3.5-inch Code**:
```cpp
// LCD object initialization
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true, 320, 480, 0, 0, 0, 0);

// Backlight control (On/Off)
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);  // ON

// Display text
gfx->setTextColor(WHITE);
gfx->setCursor(50, 200);
gfx->setTextSize(3);
gfx->println("Hello World");
```

**0.96-inch Adapted Code**:
```cpp
// LCD object initialization
Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0, false, 80, 160, 24, 0, 24, 0);

// Backlight control (On/Off, Active Low)
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, LOW);   // ON

// Display text (coordinates and font size both scaled down)
gfx->setTextColor(WHITE);
gfx->setCursor(12, 66);  // 50×0.25=12.5≈12, 200×0.333=66.6≈66
gfx->setTextSize(1);     // size 3 → size 1
gfx->println("Hello World");
```

### Example 2: Draw Rectangle (Lesson 05)

**3.5-inch Code**:
```cpp
// Draw rectangle: top-left corner (50, 100), width 200, height 150
gfx->drawRect(50, 100, 200, 150, RED);
```

**0.96-inch Adapted Code**:
```cpp
// Draw rectangle: top-left corner (12, 33), width 50, height 50
// 50×0.25=12.5≈12, 100×0.333=33.3≈33
// 200×0.25=50, 150×0.333=50
gfx->drawRect(12, 33, 50, 50, RED);
```

### Example 3: Draw Circle (Lesson 05)

**3.5-inch Code**:
```cpp
// Draw circle: center (160, 240), radius 50
gfx->drawCircle(160, 240, 50, BLUE);
```

**0.96-inch Adapted Code**:
```cpp
// Draw circle: center (40, 80), radius 17
// 160×0.25=40, 240×0.333=80
// 50×0.333=16.65≈17
gfx->drawCircle(40, 80, 17, BLUE);
```

## Special Notes

### 1. Offset Explanation
- 0.96-inch display usually requires 24-pixel column offset for correct display
- Offset parameters: `24, 0, 24, 0`
  - First 24: Column offset for rotation 0/2
  - Second 24: Column offset for rotation 1/3
  - 0, 0: Row offset (usually 0)

### 2. Display Size Limitations
- Width is only 80 pixels, very small
- Recommendations:
  - Text size not exceeding size 2
  - Avoid displaying too much content
  - Simplify UI design

### 3. Center Display Calculation
```cpp
// 3.5-inch center text
int textWidth = strlen("Text") * 3 * 6;  // Estimate width
int x = (320 - textWidth) / 2;
int y = (480 - 24) / 2;  // 24 is text height for size 3

// 0.96-inch center text
int textWidth = strlen("Text") * 1 * 6;  // Estimate width
int x = (80 - textWidth) / 2;
int y = (160 - 8) / 2;  // 8 is text height for size 1
```

## Frequently Asked Questions

### Q1: Display doesn't light up?
**A**: Check backlight control code:
- Confirm using `digitalWrite(TFT_BACKLIGHT, LOW)` (0.96-inch is Active Low)
- If still not lighting up, try `digitalWrite(TFT_BACKLIGHT, HIGH)`
- Check if GPIO 41 connection is correct

### Q2: Display position offset?
**A**: Adjust offset parameters:
- If content is shifted left, increase column offset (e.g., 24→26)
- If content is shifted right, decrease column offset (e.g., 24→22)
- If content is shifted up, increase row offset (e.g., 0→2)
- If content is shifted down, decrease row offset (e.g., 0→-2)

### Q3: Text not fully displayed?
**A**: 
- Reduce text size (size 3 → size 1)
- Shorten text content
- Check if text width exceeds 80 pixels

### Q4: How to accurately convert coordinates?
**A**: Use formula calculation:
```cpp
// Define conversion functions
int convertX(int x35) {
  return (int)(x35 * 80.0 / 320.0);
}

int convertY(int y35) {
  return (int)(y35 * 160.0 / 480.0);
}

// Usage
int x = convertX(50);  // 3.5-inch's 50 → 0.96-inch's 12
int y = convertY(200); // 3.5-inch's 200 → 0.96-inch's 66
```

### Q5: How to determine if offset is correct?
**A**: 
- Reference test program: `0.96inch/code/0.96inch_Test/0.96inch_Test.ino`
- If display position is incorrect, fine-tune offset parameters
- Column offset is usually between 20-28

## Practical Adaptation Cases

### Case 1: Adapt Lesson 01 (Hello World)

**Original Code (3.5-inch)**:
```cpp
gfx->setCursor(50, 200);
gfx->setTextSize(3);
gfx->println("Hello World");
```

**Adapted (0.96-inch)**:
```cpp
gfx->setCursor(12, 66);  // Coordinate conversion
gfx->setTextSize(1);     // Text size adjustment
gfx->println("Hello");   // Shorten text to fit small screen
```

### Case 2: Adapt Lesson 05 (Graphics)

**Original Code (3.5-inch)**:
```cpp
// Draw progress bar
gfx->drawRect(20, 200, 280, 40, WHITE);
gfx->fillRect(20, 200, 140, 40, GREEN);  // 50%
```

**Adapted (0.96-inch)**:
```cpp
// Draw progress bar (scaled down proportionally)
gfx->drawRect(5, 66, 70, 13, WHITE);     // 20×0.25=5, 200×0.333=66, 280×0.25=70, 40×0.333=13
gfx->fillRect(5, 66, 35, 13, GREEN);     // 50% = 70×0.5=35
```

## Reference Resources

- **Test Program**: `0.96inch/code/0.96inch_Test/0.96inch_Test.ino`
- **Display README**: `0.96inch/README.md`
- **3.5-inch Tutorial**: `tutorials/3.5inch/`

## Quick Checklist

After adaptation, check the following items:

- [ ] LCD object initialization modified (`Arduino_ST7735`, resolution `80, 160`, offset `24, 0, 24, 0`)
- [ ] IPS parameter set to `false`
- [ ] Backlight control uses On/Off (0.96-inch: `digitalWrite(TFT_BACKLIGHT, LOW)` = ON)
- [ ] All coordinates converted proportionally (X×0.25, Y×0.333)
- [ ] Text size adjusted (recommended size 1-2)
- [ ] Graphics dimensions scaled down proportionally
- [ ] Display shows correctly, no offset
- [ ] Backlight is ON

---

**Tip**: If you encounter problems, first refer to the test program code, then fine-tune parameters according to actual situation.
