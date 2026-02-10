# 1.8-inch Display Adaptation Guide

This guide provides detailed instructions on how to adapt 3.5-inch tutorial code to the 1.8-inch display.

## Display Specifications

| Parameter | Value | Description |
|-----------|-------|-------------|
| **Display Size** | 1.8 inch | Small size display |
| **Driver IC** | ST7735S | Use `Arduino_ST7735` class |
| **Resolution** | 128 x 160 | Width 128 pixels, Height 160 pixels |
| **IPS Parameter** | `true` | **Must be set to true for correct color display** |
| **Column Offset** | 0, 0 | Usually no offset needed |
| **Row Offset** | 0, 0 | Usually no offset needed |
| **Backlight Control** | On/Off (Active High) | `digitalWrite(BLK, HIGH)`=ON |
| **Color Mode** | RGB565/BGR565 | May require BGR conversion |

## Key Differences

### 1. Resolution Difference
- **3.5-inch**: 320 x 480 pixels
- **1.8-inch**: 128 x 160 pixels
- **Ratio**: Width approximately 2/5, Height approximately 1/3

### 2. IPS Parameter (Important!)
- **3.5-inch**: IPS parameter `true`
- **1.8-inch**: IPS parameter **must** be set to `true`, otherwise colors will display incorrectly

### 3. Color Display (Special)
- 1.8-inch ST7735S may require BGR color conversion
- If colors display incorrectly (e.g., red displays as blue), BGR conversion function is needed

## Code Modification Steps

### Step 1: Modify LCD Object Initialization

**3.5-inch (Tutorial Default)**:
```cpp
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);
```

**1.8-inch Adaptation**:
```cpp
Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0, true /* IPS */, 128, 160, 0, 0, 0, 0);
```

**Modification Notes**:
1. Driver class: `Arduino_ST7796` → `Arduino_ST7735`
2. IPS parameter: Keep `true` (**must be true**)
3. Resolution: `320, 480` → `128, 160`
4. Offset: Keep `0, 0, 0, 0`

### Step 2: Backlight Control (Same as 3.5-inch)

**1.8-inch (On/Off, Active High)**:
```cpp
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
```

**Note**: 1.8-inch backlight is the same as 3.5-inch, On/Off only.

### Step 3: BGR Color Conversion (Optional, Based on Actual Situation)

If colors display incorrectly (e.g., red displays as blue), add BGR conversion function:

```cpp
// RGB565 to BGR565: Swap R and B channels
uint16_t RGBtoBGR(uint16_t rgb) {
  uint8_t r = (rgb >> 11) & 0x1F;  // Upper 5 bits are R
  uint8_t g = (rgb >> 5) & 0x3F;    // Middle 6 bits are G
  uint8_t b = rgb & 0x1F;            // Lower 5 bits are B
  return (b << 11) | (g << 5) | r;  // Recombine as BGR565
}

// Usage example
uint16_t colors[] = {RED, GREEN, BLUE};
uint16_t bgrColors[3];
for (int i = 0; i < 3; i++) {
  bgrColors[i] = RGBtoBGR(colors[i]);  // Convert to BGR mode
}
gfx->fillRect(0, 0, 128, 20, bgrColors[0]);  // Use BGR color
```

### Step 4: Adjust Coordinates and Dimensions

#### Coordinate Conversion Formula

```
New X coordinate = Original X coordinate × (New width / Original width)
New Y coordinate = Original Y coordinate × (New height / Original height)
```

**1.8-inch Conversion Ratio**:
- X coordinate ratio: 128 / 320 = 0.4 (scale down to 2/5)
- Y coordinate ratio: 160 / 480 = 0.333 (scale down to 1/3)

#### Coordinate Conversion Examples

| 3.5-inch Coordinates | 1.8-inch Coordinates | Calculation Process |
|----------------------|----------------------|---------------------|
| (50, 200) | (20, 66) | 50×0.4=20, 200×0.333=66.6≈66 |
| (100, 300) | (40, 100) | 100×0.4=40, 300×0.333=100 |
| (160, 240) | (64, 80) | 160×0.4=64, 240×0.333=80 |
| (320, 480) | (128, 160) | 320×0.4=128, 480×0.333=160 |

#### Dimension Conversion Examples

| 3.5-inch Dimensions | 1.8-inch Dimensions | Calculation Process |
|---------------------|---------------------|---------------------|
| Width 100 | Width 40 | 100×0.4=40 |
| Height 50 | Height 17 | 50×0.333=16.65≈17 |
| Radius 50 | Radius 17 | 50×0.333=16.65≈17 |

### Step 5: Adjust Text Size

**Text Size Recommendations**:

| 3.5-inch Text Size | 1.8-inch Recommended Size | Notes |
|---------------------|---------------------------|-------|
| size 3 | size 1 | Large title → Small title |
| size 2 | size 1 | Medium text → Small text |
| size 1 | size 1 | Small text remains unchanged |

**Text Width Estimation**:
- Text width ≈ Character count × size × 6
- Example: "Hello World" (12 characters)
  - size 3: 12 × 3 × 6 = 216 pixels (exceeds 1.8-inch width 128)
  - size 2: 12 × 2 × 6 = 144 pixels (exceeds 1.8-inch width 128)
  - size 1: 12 × 1 × 6 = 72 pixels (fits 1.8-inch width 128)

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

**1.8-inch Adapted Code**:
```cpp
// LCD object initialization
Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0, true, 128, 160, 0, 0, 0, 0);

// Backlight control (same as 3.5-inch, On/Off)
pinMode(TFT_BACKLIGHT, OUTPUT);
digitalWrite(TFT_BACKLIGHT, HIGH);

// Display text (coordinates and font size both scaled down)
gfx->setTextColor(WHITE);
gfx->setCursor(20, 66);  // 50×0.4=20, 200×0.333=66.6≈66
gfx->setTextSize(1);     // size 3 → size 1
gfx->println("Hello World");
```

### Example 2: Color Display (Lesson 02)

**3.5-inch Code**:
```cpp
gfx->fillScreen(RED);
gfx->setTextColor(WHITE);
gfx->println("RED");
```

**1.8-inch Adapted Code (If colors incorrect, use BGR conversion)**:
```cpp
// If colors display incorrectly, use BGR conversion
uint16_t bgrRed = RGBtoBGR(RED);
gfx->fillScreen(bgrRed);
gfx->setTextColor(WHITE);
gfx->println("RED");
```

### Example 3: Draw Rectangle (Lesson 05)

**3.5-inch Code**:
```cpp
// Draw rectangle: top-left corner (50, 100), width 200, height 150
gfx->drawRect(50, 100, 200, 150, RED);
```

**1.8-inch Adapted Code**:
```cpp
// Draw rectangle: top-left corner (20, 33), width 80, height 50
// 50×0.4=20, 100×0.333=33.3≈33
// 200×0.4=80, 150×0.333=50
gfx->drawRect(20, 33, 80, 50, RED);
// If colors incorrect, use BGR conversion:
// uint16_t bgrRed = RGBtoBGR(RED);
// gfx->drawRect(20, 33, 80, 50, bgrRed);
```

## Special Notes

### 1. IPS Parameter Must Be True
- **Important**: 1.8-inch display's IPS parameter **must** be set to `true`
- If set to `false`, colors will display incorrectly
- This is a special requirement for 1.8-inch display

### 2. BGR Color Conversion
- Some 1.8-inch ST7735S displays may require BGR color conversion
- If colors display incorrectly (e.g., red displays as blue), try using BGR conversion
- Reference test program: `1.8inch/code/1.8inch_Test/1.8inch_Test.ino`

### 3. Display Size Limitations
- Width 128 pixels, Height 160 pixels
- Recommendations:
  - Text size not exceeding size 2
  - Simplify UI design
  - Avoid displaying too much content

### 4. Center Display Calculation
```cpp
// 3.5-inch center text
int textWidth = strlen("Text") * 3 * 6;  // Estimate width
int x = (320 - textWidth) / 2;
int y = (480 - 24) / 2;  // 24 is text height for size 3

// 1.8-inch center text
int textWidth = strlen("Text") * 1 * 6;  // Estimate width
int x = (128 - textWidth) / 2;
int y = (160 - 8) / 2;  // 8 is text height for size 1
```

## Frequently Asked Questions

### Q1: Colors display incorrectly?
**A**: 
1. **First check IPS parameter**: Must be set to `true`
2. **If IPS parameter is correct but colors still wrong**: Try using BGR color conversion
3. Reference BGR conversion function in test program

### Q2: How to determine if BGR conversion is needed?
**A**: 
- If red displays as blue, green displays as magenta, BGR conversion is needed
- Test method: Display red, if it displays as blue, conversion is needed
- Reference test program: `1.8inch/code/1.8inch_Test/1.8inch_Test.ino`

### Q3: What happens if IPS parameter is set to false?
**A**: 
- Colors will display incorrectly
- May display as inverted colors
- **Must be set to `true`**

### Q4: How to accurately convert coordinates?
**A**: Use formula calculation:
```cpp
// Define conversion functions
int convertX(int x35) {
  return (int)(x35 * 128.0 / 320.0);
}

int convertY(int y35) {
  return (int)(y35 * 160.0 / 480.0);
}

// Usage
int x = convertX(50);  // 3.5-inch's 50 → 1.8-inch's 20
int y = convertY(200); // 3.5-inch's 200 → 1.8-inch's 66
```

### Q5: Text not fully displayed?
**A**: 
- Reduce text size (size 3 → size 1)
- Shorten text content
- Check if text width exceeds 128 pixels

## Practical Adaptation Cases

### Case 1: Adapt Lesson 01 (Hello World)

**Original Code (3.5-inch)**:
```cpp
gfx->setCursor(50, 200);
gfx->setTextSize(3);
gfx->println("Hello World");
```

**Adapted (1.8-inch)**:
```cpp
gfx->setCursor(20, 66);  // Coordinate conversion
gfx->setTextSize(1);     // Text size adjustment
gfx->println("Hello World");
```

### Case 2: Adapt Lesson 02 (Colors)

**Original Code (3.5-inch)**:
```cpp
gfx->fillScreen(RED);
gfx->setTextColor(WHITE);
gfx->println("RED");
```

**Adapted (1.8-inch, if BGR conversion needed)**:
```cpp
uint16_t bgrRed = RGBtoBGR(RED);
gfx->fillScreen(bgrRed);
gfx->setTextColor(WHITE);
gfx->println("RED");
```

### Case 3: Adapt Lesson 05 (Graphics)

**Original Code (3.5-inch)**:
```cpp
// Draw progress bar
gfx->drawRect(20, 200, 280, 40, WHITE);
gfx->fillRect(20, 200, 140, 40, GREEN);  // 50%
```

**Adapted (1.8-inch)**:
```cpp
// Draw progress bar (scaled down proportionally)
gfx->drawRect(8, 66, 112, 13, WHITE);     // 20×0.4=8, 200×0.333=66, 280×0.4=112, 40×0.333=13
gfx->fillRect(8, 66, 56, 13, GREEN);      // 50% = 112×0.5=56
```

## Reference Resources

- **Test Program**: `1.8inch/code/1.8inch_Test/1.8inch_Test.ino`
- **Display README**: `1.8inch/README.md`
- **3.5-inch Tutorial**: `tutorials/3.5inch/`

## Quick Checklist

After adaptation, check the following items:

- [ ] LCD object initialization modified (`Arduino_ST7735`, resolution `128, 160`)
- [ ] **IPS parameter set to `true` (Important!)****
- [ ] Backlight control uses On/Off (`digitalWrite(TFT_BACKLIGHT, HIGH)` = ON)
- [ ] All coordinates converted proportionally (X×0.4, Y×0.333)
- [ ] Text size adjusted (recommended size 1-2)
- [ ] Graphics dimensions scaled down proportionally
- [ ] If colors incorrect, BGR conversion added
- [ ] Display shows correctly, colors correct
- [ ] Backlight is ON

---

**Tip**: The key for 1.8-inch display is that IPS parameter must be set to `true`. If colors display incorrectly, try using BGR color conversion.
