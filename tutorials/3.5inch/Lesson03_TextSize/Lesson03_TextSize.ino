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
  
  Serial.println("Lesson 03: Text Size");
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
