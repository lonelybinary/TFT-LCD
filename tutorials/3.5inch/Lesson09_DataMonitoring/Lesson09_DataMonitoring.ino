/*
 * Lesson 09: Data Monitoring Interface
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn to create a data monitoring interface
 *
 * Key concepts:
 * - Card-style layout
 * - Data visualization (progress bar)
 * - Multiple cards layout
 * - Status indicator
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

// ==================== Helper Functions ====================

// Draw label (text with background)
void drawLabel(const char* text, int x, int y, uint16_t bgColor, uint16_t textColor, int textSize = 2) {
  int textWidth = strlen(text) * 6 * textSize;
  int textHeight = 8 * textSize;
  
  // Draw background
  gfx->fillRect(x, y, textWidth + 8, textHeight + 4, bgColor);
  
  // Draw text
  gfx->setTextColor(textColor);
  gfx->setTextSize(textSize);
  gfx->setCursor(x + 4, y + 4);
  gfx->println(text);
}

// Draw progress bar
void drawProgressBar(int x, int y, int width, int height, int percent, uint16_t bgColor, uint16_t fillColor) {
  // Draw background frame
  gfx->drawRect(x, y, width, height, bgColor);
  
  // Compute fill width
  int fillWidth = (width * percent) / 100;
  if (fillWidth > 0) {
    gfx->fillRect(x + 2, y + 2, fillWidth - 4, height - 4, fillColor);
  }
}

// Draw centered text
void drawCenteredText(const char* text, int y, uint16_t color, int size) {
  gfx->setTextSize(size);
  gfx->setTextColor(color);
  int textWidth = strlen(text) * size * 6;
  int x = (gfx->width() - textWidth) / 2;
  gfx->setCursor(x, y);
  gfx->println(text);
}

// Draw separator line
void drawSeparator(int y, uint16_t color) {
  gfx->drawFastHLine(20, y, gfx->width() - 40, color);
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 09: Data Monitoring Interface");
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
  
  // Data monitoring interface
  Serial.println("Displaying Data Monitoring Interface");
  gfx->fillScreen(BLACK);
  
  // Title
  drawCenteredText("MONITOR", 20, WHITE, 2);
  drawSeparator(60, GREEN);
  
  // Data card 1 (left)
  gfx->drawRect(30, 100, 120, 100, CYAN);
  gfx->setTextColor(CYAN);
  gfx->setTextSize(2);
  gfx->setCursor(40, 110);
  gfx->println("CPU");
  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  gfx->setCursor(40, 140);
  gfx->println("45%");
  drawProgressBar(40, 170, 100, 15, 45, CYAN, GREEN);
  
  // Data card 2 (right)
  gfx->drawRect(170, 100, 120, 100, YELLOW);
  gfx->setTextColor(YELLOW);
  gfx->setTextSize(2);
  gfx->setCursor(180, 110);
  gfx->println("MEM");
  gfx->setTextColor(WHITE);
  gfx->setTextSize(3);
  gfx->setCursor(180, 140);
  gfx->println("62%");
  drawProgressBar(180, 170, 100, 15, 62, YELLOW, GREEN);
  
  // Status indicator (centered)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(30, 230);
  gfx->print("Status: ");
  drawLabel("OK", 150, 225, GREEN, BLACK, 2);
  
  Serial.println("Data Monitoring Interface display complete!");
}

void loop() {
  delay(1000);
}
