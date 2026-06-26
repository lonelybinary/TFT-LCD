/*
 * Lesson 05: Graphics
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn how to draw basic shapes
 *
 * Key concepts:
 * - Draw lines
 * - Draw rectangles
 * - Draw circles
 * - Filled shapes
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
  #define TFT_SPI_NUM   HSPI    // S3: SPI3 host (=1). Usable buses are FSPI(=0) and HSPI(=1).
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
  #define TFT_SPI_NUM   VSPI    // classic ESP32: SPI3 host (=3). NOT FSPI(=1) -- that is the on-chip flash bus.
#endif

// ==================== Create the display object ====================
// "bus" sets up HOW we talk to the screen (hardware SPI on the pins above).
// "gfx" is the ST7796 screen driver (320x480) we call to draw text and shapes.
// Using a different screen size? See ADAPTATION_GUIDE.md in that size's folder.
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, TFT_SPI_NUM /* HSPI on S3, VSPI on classic ESP32 */, true /* is_shared_interface */);
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 05: Graphics");
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
  
  // Part 1: Draw lines
  Serial.println("Drawing lines...");
  gfx->fillScreen(BLACK);
  
  // Horizontal line
  gfx->drawLine(20, 20, 300, 20, WHITE);
  
  // Vertical line
  gfx->drawLine(20, 20, 20, 460, RED);
  
  // Diagonal lines
  gfx->drawLine(20, 20, 300, 460, GREEN);
  gfx->drawLine(300, 20, 20, 460, BLUE);
  
  delay(2000);
  
  // Part 2: Draw rectangles (outline)
  Serial.println("Drawing rectangles (outline)...");
  gfx->fillScreen(BLACK);
  
  // Small rect
  gfx->drawRect(20, 20, 80, 60, RED);
  
  // Medium rect
  gfx->drawRect(120, 20, 100, 80, GREEN);
  
  // Large rect
  gfx->drawRect(20, 120, 150, 100, BLUE);
  
  delay(2000);
  
  // Part 3: Draw filled rectangles
  Serial.println("Drawing filled rectangles...");
  gfx->fillScreen(BLACK);
  
  // Filled rects
  gfx->fillRect(20, 20, 80, 60, RED);
  gfx->fillRect(120, 20, 100, 80, GREEN);
  gfx->fillRect(20, 120, 150, 100, BLUE);
  
  delay(2000);
  
  // Part 4: Draw circles (outline)
  Serial.println("Drawing circles (outline)...");
  gfx->fillScreen(BLACK);
  
  // Small circle
  gfx->drawCircle(80, 100, 30, RED);
  
  // Medium circle
  gfx->drawCircle(160, 100, 50, GREEN);
  
  // Large circle
  gfx->drawCircle(240, 100, 70, BLUE);
  
  delay(2000);
  
  // Part 5: Draw filled circles
  Serial.println("Drawing filled circles...");
  gfx->fillScreen(BLACK);
  
  // Filled circles
  gfx->fillCircle(80, 200, 30, RED);
  gfx->fillCircle(160, 200, 50, GREEN);
  gfx->fillCircle(240, 200, 70, BLUE);
  
  delay(2000);
  
  // Part 6: Combined shapes - simple icons
  Serial.println("Creating simple icons...");
  gfx->fillScreen(BLACK);
  
  // Icon 1: Play button (triangle)
  gfx->fillTriangle(50, 100, 50, 200, 150, 150, GREEN);
  
  // Icon 2: Stop button (square)
  gfx->fillRect(180, 100, 80, 80, RED);
  
  // Icon 3: Circle button
  gfx->fillCircle(280, 150, 40, BLUE);
  
  delay(2000);
  
  // Part 7: Draw grid
  Serial.println("Drawing grid...");
  gfx->fillScreen(BLACK);
  
  // Grid lines
  for (int x = 0; x < 320; x += 40) {
    gfx->drawLine(x, 0, x, 480, CYAN);
  }
  for (int y = 0; y < 480; y += 40) {
    gfx->drawLine(0, y, 320, y, CYAN);
  }
  
  delay(2000);
  
  // Part 8: Draw progress bar
  Serial.println("Drawing progress bar...");
  gfx->fillScreen(BLACK);
  
  // Progress bar background
  gfx->drawRect(20, 200, 280, 40, WHITE);
  
  // Progress bar fill (50%)
  gfx->fillRect(20, 200, 140, 40, GREEN);
  
  // Show percentage
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(50, 100);
  gfx->println("Progress: 50%");
  
  delay(2000);
  
  // Part 9: Animate graphics
  Serial.println("Animating graphics...");
  gfx->fillScreen(BLACK);
  
  // Moving circle
  for (int x = 40; x < 280; x += 10) {
    gfx->fillScreen(BLACK);
    gfx->fillCircle(x, 240, 30, YELLOW);
    delay(100);
  }
  
  // Growing rectangle
  for (int w = 20; w < 300; w += 10) {
    gfx->fillScreen(BLACK);
    gfx->fillRect(10, 200, w, 80, CYAN);
    delay(50);
  }
  
  Serial.println("Graphics demonstration complete!");
}

void loop() {
  delay(1000);
}
