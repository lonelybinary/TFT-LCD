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
  
  Serial.println("Lesson 06: Rotation");
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
