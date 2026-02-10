/*
 * SPI LCD Test Program - Arduino IDE Version
 * Using Arduino GFX Official Library
 * Driver IC: ST7789
 * Display Size: 2.4 inch
 * Resolution: 240x320 
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
// ST7789 initialization parameters: 240x320
// Note: GFX Library 1.6.4 API - Arduino_ESP32SPI constructor requires MISO parameter (use GFX_NOT_DEFINED if not used)
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED /* MISO (not used) */, 1 /* VSPI */, true /* use_psram */);
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 0 /* rotation */, true /* IPS */, 240 /* width */, 320 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col offset 2 */, 0 /* row offset 2 */);

// ==================== Display LonelyBinary and Color Bars ====================
void displayLonelyBinary() {
  gfx->fillScreen(BLACK);
  
  // Top section: Center display "LonelyBinary" (adapt to screen size, ensure it doesn't exceed)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);  // 240px width, size=3 would be close to border, changed to size=2 for safety
  int textWidth = strlen("LonelyBinary") * 2 * 6;  // Estimate text width: 12*2*6=144px
  int textX = (gfx->width() - textWidth) / 2;
  int textY = 74;  // Top section
  gfx->setCursor(textX, textY);
  gfx->println("LonelyBinary");
  
  // Bottom section: 8 horizontal color bars
  uint16_t colors[] = {
    RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE, BLACK
  };
  int barStartY = 114;
  int barHeight = (gfx->height() - barStartY - 40) / 8;  // Each color bar height (widened), leave space for bottom info
  int barWidth = gfx->width();  // Color bar width (full screen width)
  
  for (int i = 0; i < 8; i++) {
    gfx->fillRect(0, barStartY + i * barHeight, barWidth, barHeight, colors[i]);
  }
  
  // Bottom: Display screen information (resolution, driver, inch size)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(1);
  int infoY = 274;
  gfx->setCursor(10, infoY);
  gfx->print("240x320");
  gfx->setCursor(10, infoY + 12);
  gfx->print("ST7789");
  gfx->setCursor(10, infoY + 24);
  gfx->print("2.4inch");
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("SPI LCD Test Program");
  Serial.println("Driver IC: ST7789");
  Serial.println("Display Size: 2.4 inch");
  Serial.println("Resolution: 240x320");
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
  
  // ST7789 initialization
  Serial.println("Initializing ST7789 display (240x320)...");
  
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
