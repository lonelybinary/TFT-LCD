/*
 * Lesson 01: Hello World
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn how to display text on screen
 *
 * Key concepts:
 * - Display initialization
 * - Backlight On/Off control
 * - Set text color
 * - Set cursor position
 * - Display text
 * 
 * Library Dependencies:
 * - Arduino GFX Library (moononournation/GFX Library for Arduino@1.6.4)
 */

#include <Arduino_GFX_Library.h>

// ==================== SPI LCD Pin Definitions ====================
#define TFT_CS    10   // CS (Chip Select, pin 8)
#define TFT_RST   42   // RESET (Reset, pin 3)
#define TFT_DC    2    // DC/RS/A0 (Data/Command select, pin 4) - **Must connect!**
#define TFT_MOSI  11   // SDA/MOSI (SPI data output, pin 5) - VSPI hardware SPI pin
#define TFT_SCLK  12   // SCL/SCLK (SPI clock, pin 6) - VSPI hardware SPI pin
#define TFT_BACKLIGHT 41  // LEDA/BLK (Backlight control, pin 1)

// ==================== LCD Object ====================
// Using hardware SPI (VSPI: MOSI=GPIO11, SCLK=GPIO12)
// ST7796 initialization parameters: 320x480
// Note: For other screen sizes, see the adaptation guide for each size:
// - 0.96 inch: 0.96inch/ADAPTATION_GUIDE.md
// - 1.8 inch: 1.8inch/ADAPTATION_GUIDE.md
// - 2.0 inch: 2.0inch/ADAPTATION_GUIDE.md
// - 2.4 inch: 2.4inch/ADAPTATION_GUIDE.md
// - 2.8 inch: 2.8inch/ADAPTATION_GUIDE.md
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED /* MISO (not used) */, 1 /* VSPI */, true /* use_psram */);
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0 /* rotation */, true /* IPS */, 320 /* width */, 480 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col offset 2 */, 0 /* row offset 2 */);

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 01: Hello World");
  Serial.println("Initializing LCD...");
  
  // Initialize backlight (On/Off only)
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
  
  // Reset display first
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(10);
  digitalWrite(TFT_RST, HIGH);
  delay(120);
  
  // Initialize LCD
  if (!gfx->begin()) {
    Serial.println("LCD initialization failed!");
    while (1);
  }
  
  // Set rotation direction
  gfx->setRotation(0);  // 0=normal, 1=90°, 2=180°, 3=270°
  
  // Clear screen with black background
  gfx->fillScreen(BLACK);
  
  Serial.println("LCD initialized successfully!");
  
  // ==================== Lesson Content ====================
  // Step 1: Set text color to white
  gfx->setTextColor(WHITE);
  
  // Step 2: Set cursor position (x, y)
  // Note: (0, 0) is top-left corner
  gfx->setCursor(50, 200);
  
  // Step 3: Display "Hello World"
  gfx->setTextSize(3);  // Larger text for 3.5 inch screen
  gfx->println("Hello World");
  
  Serial.println("Hello World displayed on screen!");
}

// ==================== Main Loop ====================
void loop() {
  // Nothing to do in loop for this lesson
  delay(1000);
}
