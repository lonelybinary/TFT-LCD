/*
 * Lesson 06: Rotation
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn how to rotate screen orientation
 *
 * Key concepts:
 * - setRotation() function
 * - Effect of different rotation angles
 * - How rotation affects coordinates
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
  
  Serial.println("Lesson 06: Rotation");
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
  
  Serial.println("LCD initialized successfully!");
  
  // ==================== Lesson Content ====================
  
  // Part 1: Show all rotation angles
  Serial.println("Displaying all rotation angles...");
  
  for (int rotation = 0; rotation < 4; rotation++) {
    // Set rotation
    gfx->setRotation(rotation);
    
    // Clear screen
    gfx->fillScreen(BLACK);
    
    // Show rotation info
    gfx->setTextColor(WHITE);
    gfx->setTextSize(3);
    gfx->setCursor(50, 50);
    gfx->print("Rot: ");
    gfx->println(rotation);
    
    // Show current screen size
    gfx->setTextSize(2);
    gfx->setCursor(50, 120);
    gfx->print("W: ");
    gfx->print(gfx->width());
    gfx->print(" H: ");
    gfx->println(gfx->height());
    
    // Draw axes
    int centerX = gfx->width() / 2;
    int centerY = gfx->height() / 2;
    
    // X axis (red)
    gfx->drawLine(0, centerY, gfx->width(), centerY, RED);
    gfx->setTextColor(RED);
    gfx->setTextSize(2);
    gfx->setCursor(gfx->width() - 40, centerY - 30);
    gfx->print("X");
    
    // Y axis (green)
    gfx->drawLine(centerX, 0, centerX, gfx->height(), GREEN);
    gfx->setTextColor(GREEN);
    gfx->setCursor(centerX + 10, 20);
    gfx->print("Y");
    
    // Origin marker
    gfx->fillCircle(0, 0, 5, YELLOW);
    gfx->setTextColor(YELLOW);
    gfx->setTextSize(1);
    gfx->setCursor(10, 10);
    gfx->print("(0,0)");
    
    // Corner markers
    gfx->fillCircle(0, 0, 3, CYAN);
    gfx->fillCircle(gfx->width()-1, 0, 3, CYAN);
    gfx->fillCircle(0, gfx->height()-1, 3, CYAN);
    gfx->fillCircle(gfx->width()-1, gfx->height()-1, 3, CYAN);
    
    delay(3000);
  }
  
  // Part 2: Same content at different rotations
  Serial.println("Displaying same content at different rotations...");
  
  for (int rotation = 0; rotation < 4; rotation++) {
    gfx->setRotation(rotation);
    gfx->fillScreen(BLACK);
    
    // Display text
    gfx->setTextColor(WHITE);
    gfx->setTextSize(4);
    
    // Center on screen
    int textWidth = 6 * 4 * 4;  // "TEST" 4 chars, size=4
    int x = (gfx->width() - textWidth) / 2;
    int y = (gfx->height() - 32) / 2;
    
    gfx->setCursor(x, y);
    gfx->println("TEST");
    
    // Show rotation
    gfx->setTextSize(2);
    gfx->setTextColor(CYAN);
    gfx->setCursor(20, 20);
    gfx->print("Rotation: ");
    gfx->println(rotation);
    
    delay(3000);
  }
  
  // Part 3: Graphics at different rotations
  Serial.println("Showing graphics at different rotations...");
  
  for (int rotation = 0; rotation < 4; rotation++) {
    gfx->setRotation(rotation);
    gfx->fillScreen(BLACK);
    
    int centerX = gfx->width() / 2;
    int centerY = gfx->height() / 2;
    
    // Draw rectangle
    gfx->drawRect(centerX - 60, centerY - 40, 120, 80, RED);
    
    // Draw circle
    gfx->drawCircle(centerX, centerY, 50, GREEN);
    
    // Draw line (to top-right)
    gfx->drawLine(centerX, centerY, centerX + 60, centerY - 60, BLUE);
    
    // Show angle
    gfx->setTextColor(WHITE);
    gfx->setTextSize(2);
    gfx->setCursor(20, 20);
    gfx->print("Rot: ");
    gfx->println(rotation);
    
    delay(3000);
  }
  
  // Part 4: Rotation reference
  Serial.println("Rotation angle reference...");
  gfx->setRotation(0);  // Restore default
  gfx->fillScreen(BLACK);
  
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(50, 50);
  gfx->println("Rotation:");
  gfx->setCursor(50, 100);
  gfx->println("0 = 0 deg");
  gfx->setCursor(50, 150);
  gfx->println("1 = 90 deg");
  gfx->setCursor(50, 200);
  gfx->println("2 = 180 deg");
  gfx->setCursor(50, 250);
  gfx->println("3 = 270 deg");
  
  delay(5000);
  
  Serial.println("Rotation demonstration complete!");
}

void loop() {
  delay(1000);
}
