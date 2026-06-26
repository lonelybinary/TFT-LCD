/*
 * Lesson 11: Clock Display
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn to create a clock display interface
 *
 * Key concepts:
 * - Analog clock drawing
 * - Clock tick marks
 * - Hour and minute hands
 * - Digital time display
 * - Centered layout
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

#include <math.h>

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

// ==================== Helper Functions ====================

// Draw centered text
void drawCenteredText(const char* text, int y, uint16_t color, int size) {
  gfx->setTextSize(size);
  gfx->setTextColor(color);
  int textWidth = strlen(text) * size * 6;
  int x = (gfx->width() - textWidth) / 2;
  gfx->setCursor(x, y);
  gfx->println(text);
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 11: Clock Display");
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
  
  // Clock interface
  Serial.println("Displaying Clock Interface");
  gfx->fillScreen(BLACK);
  
  // Clock center (screen center: 320/2=160, 480/2=240)
  int centerX = 160;  // Screen width center
  int centerY = 240;  // Screen height center
  int radius = 100;   // Clock radius, keep within screen
  
  // Outer circle
  gfx->drawCircle(centerX, centerY, radius, WHITE);
  
  // Clock ticks (12 marks)
  for (int i = 0; i < 12; i++) {
    float angle = i * PI / 6 - PI / 2;
    int x1 = centerX + (radius - 5) * cos(angle);
    int y1 = centerY + (radius - 5) * sin(angle);
    int x2 = centerX + (radius - 20) * cos(angle);
    int y2 = centerY + (radius - 20) * sin(angle);
    gfx->drawLine(x1, y1, x2, y2, WHITE);
  }
  
  // Hour hand (pointing to 3 o'clock)
  gfx->drawLine(centerX, centerY, centerX + 40, centerY, RED);
  
  // Minute hand (pointing to 12 o'clock)
  gfx->drawLine(centerX, centerY, centerX, centerY - 60, GREEN);
  
  // Center dot
  gfx->fillCircle(centerX, centerY, 5, WHITE);
  
  // Time text (below clock)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  drawCenteredText("12:00", 380, WHITE, 3);
  
  Serial.println("Clock Display complete!");
}

void loop() {
  delay(1000);
}
