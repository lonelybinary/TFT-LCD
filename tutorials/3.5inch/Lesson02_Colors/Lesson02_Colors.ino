/*
 * Lesson 02: Colors
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn how to use colors
 *
 * Key concepts:
 * - Predefined colors
 * - Fill screen with color
 * - Set text color
 * 
 * Library Dependencies:
 * - Arduino GFX Library (moononournation/GFX Library for Arduino@1.6.4)
 */

#include <Arduino_GFX_Library.h>

// ==================== SPI LCD Pin Definitions ====================
#define TFT_CS    10
#define TFT_RST   42
#define TFT_DC    2
#define TFT_MOSI  11
#define TFT_SCLK  12
#define TFT_BACKLIGHT 41

// ==================== LCD Object ====================
// Note: For other screen sizes, see the test program for each size
// e.g. 0.96 inch: 0.96inch/code/0.96inch_Test/0.96inch_Test.ino
// See ADAPTATION_GUIDE.md in each screen folder for adaptation details
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, 1, true);
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 02: Colors");
  Serial.println("Initializing LCD...");
  
  // Initialize backlight (On/Off only)
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);  // ON
  
  // Reset display
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
  
  gfx->setRotation(0);
  
  Serial.println("LCD initialized successfully!");
  
  // ==================== Lesson Content ====================
  
  // Part 1: Fill screen with predefined colors
  Serial.println("Displaying predefined colors...");
  
  // Red
  gfx->fillScreen(RED);
  delay(2000);
  
  // Green
  gfx->fillScreen(GREEN);
  delay(2000);
  
  // Blue
  gfx->fillScreen(BLUE);
  delay(2000);
  
  // Yellow
  gfx->fillScreen(YELLOW);
  delay(2000);
  
  // Magenta
  gfx->fillScreen(MAGENTA);
  delay(2000);
  
  // Cyan
  gfx->fillScreen(CYAN);
  delay(2000);
  
  // White
  gfx->fillScreen(WHITE);
  delay(2000);
  
  // Black
  gfx->fillScreen(BLACK);
  delay(2000);
  
  // Part 2: Display color names list
  Serial.println("Displaying color names...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  gfx->setTextColor(RED);
  gfx->setCursor(50, 20);
  gfx->println("RED");
  
  gfx->setTextColor(GREEN);
  gfx->setCursor(50, 60);
  gfx->println("GREEN");
  
  gfx->setTextColor(BLUE);
  gfx->setCursor(50, 100);
  gfx->println("BLUE");
  
  gfx->setTextColor(YELLOW);
  gfx->setCursor(50, 140);
  gfx->println("YELLOW");
  
  gfx->setTextColor(MAGENTA);
  gfx->setCursor(50, 180);
  gfx->println("MAGENTA");
  
  gfx->setTextColor(CYAN);
  gfx->setCursor(50, 220);
  gfx->println("CYAN");
  
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 260);
  gfx->println("WHITE");
  
  Serial.println("Color demonstration complete!");
}

void loop() {
  delay(1000);
}
