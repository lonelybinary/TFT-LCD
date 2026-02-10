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
 * Library Dependencies:
 * - Arduino GFX Library (moononournation/GFX Library for Arduino@1.6.4)
 */

#include <Arduino_GFX_Library.h>
#include <math.h>

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
