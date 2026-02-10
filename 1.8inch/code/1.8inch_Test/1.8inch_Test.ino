/*
 * SPI LCD Test Program - Arduino IDE Version
 * Using Arduino GFX Official Library
 * Driver IC: ST7735S
 * Display Size: 1.8 inch
 * Resolution: 128x160
 * 
 * Library Dependencies:
 * - Arduino GFX Library (moononournation/GFX Library for Arduino)
 *   In Arduino IDE: Tools -> Manage Libraries -> Search "GFX Library for Arduino"
 */

#include <Arduino_GFX_Library.h>

// ==================== SPI LCD Pin Definitions ====================
// 8-pin SPI LCD display pin definitions:
// 1.LEDA/BLK, 2.GND, 3.RESET, 4.DC/RS/A0, 5.SDA/MOSI, 6.SCL/SCLK, 7.VDD, 8.CS
// 4-wire SPI: CS, DC/RS, SCLK, MOSI

#define TFT_CS    10   // CS (Chip Select, pin 8)
#define TFT_RST   42   // RESET (Reset, pin 3)
#define TFT_DC    2    // DC/RS/A0 (Data/Command select, pin 4) - **Must connect!**
#define TFT_MOSI  11   // SDA/MOSI (SPI data output, pin 5) - VSPI hardware SPI pin
#define TFT_SCLK  12   // SCL/SCLK (SPI clock, pin 6) - VSPI hardware SPI pin
#define TFT_BACKLIGHT 41  // LEDA/BLK (Backlight control, pin 1)

// Pin connection description:
// - VDD (pin 7) → 3.3V (Power supply)
// - GND (pin 2) → GND (Ground)
// - DC/RS/A0 (pin 4) → GPIO 2 (**Must connect!**)
// - SDA/MOSI (pin 5) → GPIO 11 (SPI data output)
// - SCL/SCLK (pin 6) → GPIO 12 (SPI clock)
// - CS (pin 8) → GPIO 10 (Chip select)
// - RESET (pin 3) → GPIO 42 (Reset)
// - LEDA/BLK (pin 1) → GPIO 41 (Backlight control)

// ==================== LCD Object ====================
// Using hardware SPI (VSPI: MOSI=GPIO11, SCLK=GPIO12)
// ST7735S: 128x160
// Note: GFX Library 1.6.4 API - Arduino_ESP32SPI constructor requires MISO parameter (use GFX_NOT_DEFINED if not used)
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED /* MISO (not used) */, 1 /* VSPI */, true /* use_psram */);
Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, true /* IPS */, 128 /* width */, 160 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col offset 2 */, 0 /* row offset 2 */);

// ==================== BGR Color Conversion ====================
// RGB565 to BGR565: Swap R and B channels
// RGB565 format: RRRRR GGGGGG BBBBB (16-bit)
// BGR565 format: BBBBB GGGGGG RRRRR (16-bit)
uint16_t RGBtoBGR(uint16_t rgb) {
  // Extract RGB565 channels
  uint8_t r = (rgb >> 11) & 0x1F;  // Upper 5 bits are R
  uint8_t g = (rgb >> 5) & 0x3F;    // Middle 6 bits are G
  uint8_t b = rgb & 0x1F;            // Lower 5 bits are B
  // Recombine as BGR565: BBBBB GGGGGG RRRRR
  return (b << 11) | (g << 5) | r;
}

// ==================== Display LonelyBinary and Color Bars ====================
void displayLonelyBinary() {
  gfx->fillScreen(BLACK);
  
  // Top section: Center display "LonelyBinary" (adapt to screen size, ensure it doesn't exceed)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(1);  // 128px width, size=2 would exceed, changed to size=1
  int textWidth = strlen("LonelyBinary") * 1 * 6;  // Estimate text width: 12*1*6=72px
  int textX = (gfx->width() - textWidth) / 2;
  int textY = 24;  // Top section
  gfx->setCursor(textX, textY);
  gfx->println("LonelyBinary");
  
  // Bottom section: 8 horizontal color bars
  // Note: 1.8 inch ST7735S display may need BGR mode for correct color display
  // Use BGR conversion function to convert RGB colors to BGR colors
  uint16_t rgbColors[] = {
    RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE, BLACK
  };
  uint16_t bgrColors[8];
  for (int i = 0; i < 8; i++) {
    bgrColors[i] = RGBtoBGR(rgbColors[i]);  // Convert to BGR mode
  }
  
  int barStartY = 50;
  int barHeight = 10;  // Each color bar height (widened)
  int barWidth = gfx->width();  // Color bar width (full screen width)
  
  for (int i = 0; i < 8; i++) {
    gfx->fillRect(0, barStartY + i * barHeight, barWidth, barHeight, bgrColors[i]);
  }
  
  // Bottom: Display screen information (resolution, driver, inch size)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(1);
  int infoY = 135;
  gfx->setCursor(2, infoY);
  gfx->print("128x160");
  gfx->setCursor(2, infoY + 8);
  gfx->print("ST7735S");
  gfx->setCursor(2, infoY + 16);
  gfx->print("1.8inch");
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("SPI LCD Test Program");
  Serial.println("Driver IC: ST7735S");
  Serial.println("Display Size: 1.8 inch");
  Serial.println("Resolution: 128x160");
  Serial.println("Using Arduino GFX Official Library");
  Serial.println("========================================");
  
  // Initialize backlight (On/Off only)
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
  
  // Initialize LCD
  Serial.println("Initializing LCD...");
  
  // Reset display first
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(10);
  digitalWrite(TFT_RST, HIGH);
  delay(120);
  
  // ST7735S initialization (128x160)
  Serial.println("Initializing ST7735S display (128x160)...");
  
  if (!gfx->begin()) {
    Serial.println("LCD initialization failed!");
    while (1);
  }
  
  // Set rotation direction (optional)
  gfx->setRotation(0);  // 0=normal, 1=90°, 2=180°, 3=270°
  
  Serial.println("LCD initialization complete");
  
  // Display LonelyBinary and color bars (static display)
  displayLonelyBinary();
  
  Serial.println("Display ready - showing static LonelyBinary and color bars");
}

// ==================== Main Loop ====================
void loop() {
  // Static display - nothing to do in loop
  delay(1000);
}
