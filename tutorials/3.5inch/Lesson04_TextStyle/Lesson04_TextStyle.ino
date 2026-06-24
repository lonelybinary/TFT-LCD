/*
 * Lesson 04: Text Style
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn text style (foreground and background color)
 *
 * Key concepts:
 * - Text foreground color
 * - Text background color
 * - Color combination effects
 * 
 * Library needed (install once via Tools -> Manage Libraries):
 * - "GFX Library for Arduino" by moononournation. Any recent version works.
 *
 * Before uploading, pick your board in Arduino IDE under Tools -> Board:
 * "ESP32S3 Dev Module" for an ESP32-S3, or "ESP32 Dev Module" for a classic ESP32.
 */

#include <Arduino_GFX_Library.h>

// ==================== Color Name Compatibility ====================
// GFX Library 1.6.5+ renamed the short color macros (BLACK, RED, ...) to RGB565_*.
// These aliases keep the sketch compiling on both old (<=1.6.4) and new (>=1.6.5)
// versions. The #ifndef guard makes it a no-op on versions that still define BLACK.
#ifndef BLACK
  #define BLACK   RGB565_BLACK
  #define WHITE   RGB565_WHITE
  #define RED     RGB565_RED
  #define GREEN   RGB565_GREEN
  #define BLUE    RGB565_BLUE
  #define YELLOW  RGB565_YELLOW
  #define MAGENTA RGB565_MAGENTA
  #define CYAN    RGB565_CYAN
#endif


// ==================== SPI LCD Pin Definitions ====================
// This kit ships wired for ESP32-S3, but the display module's ribbon cable works
// with any board. Pins are selected automatically based on the board you choose
// in Arduino IDE (Tools -> Board), so the same sketch compiles on both.
#if defined(CONFIG_IDF_TARGET_ESP32S3)
  // ESP32-S3 (select "ESP32S3 Dev Module") - default wiring for this kit
  #define TFT_CS    10   // CS  (Chip Select)
  #define TFT_RST   42   // RESET
  #define TFT_DC    2    // DC/RS/A0 (Data/Command) - **Must connect!**
  #define TFT_MOSI  11   // SDA/MOSI (SPI data)
  #define TFT_SCLK  12   // SCL/SCLK (SPI clock)
  #define TFT_BACKLIGHT 41  // LEDA/BLK (Backlight)
  #define TFT_USE_PSRAM true
#else
  // Classic ESP32 (e.g. Lonely Binary PinPulse, select "ESP32 Dev Module")
  // NOTE: GPIO 41/42 do not exist on classic ESP32, and GPIO 6-11 are reserved for
  // the on-chip SPI flash, so the S3 pins above cannot be used. These are the
  // standard VSPI pins for classic ESP32.
  #define TFT_CS    15   // CS  (Chip Select)
  #define TFT_RST   4    // RESET
  #define TFT_DC    2    // DC/RS/A0 (Data/Command) - **Must connect!**
  #define TFT_MOSI  23   // SDA/MOSI (SPI data, VSPI default)
  #define TFT_SCLK  18   // SCL/SCLK (SPI clock, VSPI default)
  #define TFT_BACKLIGHT 32  // LEDA/BLK (Backlight)
  #define TFT_USE_PSRAM false
#endif

// ==================== Create the display object ====================
// "bus" sets up HOW we talk to the screen (hardware SPI on the pins above).
// "gfx" is the ST7796 screen driver (320x480) we call to draw text and shapes.
// Using a different screen size? See ADAPTATION_GUIDE.md in that size's folder.
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, 1, TFT_USE_PSRAM /* use_psram (auto: PSRAM on S3, off on classic ESP32) */);
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 04: Text Style");
  Serial.println("Initializing LCD...");
  
  // Turn the backlight on (on/off only, no brightness control).
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);  // HIGH = backlight ON
  
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
  
  // Part 1: Foreground color only (text color)
  Serial.println("Displaying text with foreground color only...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 30);
  gfx->println("White text");
  
  gfx->setTextColor(RED);
  gfx->setCursor(50, 70);
  gfx->println("Red text");
  
  gfx->setTextColor(GREEN);
  gfx->setCursor(50, 110);
  gfx->println("Green text");
  
  gfx->setTextColor(BLUE);
  gfx->setCursor(50, 150);
  gfx->println("Blue text");
  
  gfx->setTextColor(YELLOW);
  gfx->setCursor(50, 190);
  gfx->println("Yellow text");
  
  delay(3000);
  
  // Part 2: Foreground and background color
  Serial.println("Displaying text with foreground and background colors...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // White text, red background
  gfx->setTextColor(WHITE, RED);
  gfx->setCursor(50, 30);
  gfx->println("White on Red");
  
  // Black text, yellow background
  gfx->setTextColor(BLACK, YELLOW);
  gfx->setCursor(50, 80);
  gfx->println("Black on Yellow");
  
  // White text, blue background
  gfx->setTextColor(WHITE, BLUE);
  gfx->setCursor(50, 130);
  gfx->println("White on Blue");
  
  // Red text, white background
  gfx->setTextColor(RED, WHITE);
  gfx->setCursor(50, 180);
  gfx->println("Red on White");
  
  delay(3000);
  
  // Part 3: Different color combinations
  Serial.println("Displaying different color combinations...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // High contrast
  gfx->setTextColor(WHITE, BLACK);
  gfx->setCursor(50, 30);
  gfx->println("High Contrast");
  
  gfx->setTextColor(BLACK, WHITE);
  gfx->setCursor(50, 80);
  gfx->println("Inverted");
  
  // Color combinations
  gfx->setTextColor(CYAN, MAGENTA);
  gfx->setCursor(50, 130);
  gfx->println("Cyan/Magenta");
  
  gfx->setTextColor(YELLOW, BLUE);
  gfx->setCursor(50, 180);
  gfx->println("Yellow/Blue");
  
  delay(3000);
  
  // Part 4: Text area background
  Serial.println("Displaying text with background areas...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // Method 1: setTextColor for background
  gfx->setTextColor(WHITE, RED);
  gfx->setCursor(50, 30);
  gfx->println("Method 1");
  
  // Method 2: Draw background rect first, then text
  gfx->fillRect(20, 100, 150, 30, GREEN);
  gfx->setTextColor(BLACK);
  gfx->setCursor(50, 110);
  gfx->println("Method 2");
  
  // Method 3: Multiple lines with different background
  gfx->fillRect(20, 160, 200, 30, BLUE);
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 170);
  gfx->println("Method 3");
  
  delay(3000);
  
  // Part 5: Label effects
  Serial.println("Creating label effects...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // Label 1: Success (green background)
  gfx->fillRect(50, 50, 120, 35, GREEN);
  gfx->setTextColor(BLACK);
  gfx->setCursor(60, 60);
  gfx->println("SUCCESS");
  
  // Label 2: Warning (yellow background)
  gfx->fillRect(50, 100, 120, 35, YELLOW);
  gfx->setTextColor(BLACK);
  gfx->setCursor(60, 110);
  gfx->println("WARNING");
  
  // Label 3: Error (red background)
  gfx->fillRect(50, 150, 120, 35, RED);
  gfx->setTextColor(WHITE);
  gfx->setCursor(60, 160);
  gfx->println("ERROR");
  
  // Label 4: Info (blue background)
  gfx->fillRect(50, 200, 120, 35, BLUE);
  gfx->setTextColor(WHITE);
  gfx->setCursor(60, 210);
  gfx->println("INFO");
  
  delay(3000);
  
  // Part 6: Text highlight effect
  Serial.println("Creating text highlight effects...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // Highlighted line
  gfx->fillRect(0, 100, 320, 40, CYAN);
  gfx->setTextColor(BLACK);
  gfx->setCursor(50, 110);
  gfx->println("Highlighted Line");
  
  // Normal text
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 50);
  gfx->println("Normal Text");
  
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 160);
  gfx->println("Normal Text");
  
  Serial.println("Text style demonstration complete!");
}

void loop() {
  delay(1000);
}
