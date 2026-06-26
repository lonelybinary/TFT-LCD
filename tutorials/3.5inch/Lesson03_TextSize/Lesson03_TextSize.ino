/*
 * Lesson 03: Text Size
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn how to control text size
 *
 * Key concepts:
 * - setTextSize() function
 * - Effect of different sizes
 * - How size affects position
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
  
  Serial.println("Lesson 03: Text Size");
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
  
  // Part 1: Display text in different sizes
  Serial.println("Displaying different text sizes...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextColor(WHITE);
  
  // Size 1 (default)
  gfx->setTextSize(1);
  gfx->setCursor(20, 20);
  gfx->println("Size 1");
  
  // Size 2
  gfx->setTextSize(2);
  gfx->setCursor(20, 50);
  gfx->println("Size 2");
  
  // Size 3
  gfx->setTextSize(3);
  gfx->setCursor(20, 100);
  gfx->println("Size 3");
  
  // Size 4
  gfx->setTextSize(4);
  gfx->setCursor(20, 180);
  gfx->println("Size 4");
  
  delay(3000);
  
  // Part 2: Size comparison
  Serial.println("Comparing text sizes...");
  gfx->fillScreen(BLACK);
  
  int y = 20;
  for (int size = 1; size <= 5; size++) {
    gfx->setTextSize(size);
    gfx->setTextColor(WHITE);
    gfx->setCursor(20, y);
    gfx->print("Size ");
    gfx->print(size);
    
    // Same text, different size
    gfx->setTextColor(CYAN);
    gfx->print(" ABC");
    
    y += size * 8 + 5;  // Adjust Y by size
  }
  
  delay(3000);
  
  // Part 3: Numbers in different sizes
  Serial.println("Displaying numbers in different sizes...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(50, 20);
  gfx->println("Numbers:");
  
  // Small numbers
  gfx->setTextSize(2);
  gfx->setCursor(50, 60);
  gfx->println("123");
  
  // Medium numbers
  gfx->setTextSize(3);
  gfx->setCursor(50, 120);
  gfx->println("456");
  
  // Large numbers
  gfx->setTextSize(4);
  gfx->setCursor(50, 220);
  gfx->println("789");
  
  delay(3000);
  
  // Part 4: Mixed size text
  Serial.println("Displaying mixed size text...");
  gfx->fillScreen(BLACK);
  
  // Title (large)
  gfx->setTextSize(3);
  gfx->setTextColor(YELLOW);
  gfx->setCursor(80, 30);
  gfx->println("TITLE");
  
  // Subtitle (medium)
  gfx->setTextSize(2);
  gfx->setTextColor(CYAN);
  gfx->setCursor(50, 100);
  gfx->println("Subtitle");
  
  // Body (small)
  gfx->setTextSize(1);
  gfx->setTextColor(WHITE);
  gfx->setCursor(20, 150);
  gfx->println("Body text line 1");
  gfx->setCursor(20, 170);
  gfx->println("Body text line 2");
  gfx->setCursor(20, 190);
  gfx->println("Body text line 3");
  
  delay(3000);
  
  // Part 5: Animate text size
  Serial.println("Animating text size...");
  gfx->fillScreen(BLACK);
  
  for (int size = 1; size <= 5; size++) {
    gfx->fillScreen(BLACK);
    gfx->setTextSize(size);
    gfx->setTextColor(WHITE);
    
    // Center on screen
    int textWidth = 4 * size * 6;  // Estimate width
    int x = (gfx->width() - textWidth) / 2;
    int y = (gfx->height() - size * 8) / 2;
    
    gfx->setCursor(x, y);
    gfx->println("SIZE");
    
    delay(1000);
  }
  
  Serial.println("Text size demonstration complete!");
}

void loop() {
  delay(1000);
}
