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
