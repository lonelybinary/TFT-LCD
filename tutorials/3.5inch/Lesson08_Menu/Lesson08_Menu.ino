/*
 * Lesson 08: Menu Interface
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * Course objectives: Learn to create a menu interface
 *
 * Key concepts:
 * - Menu UI design
 * - Highlight current option
 * - Title bar design
 * - Menu item layout
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
  
  Serial.println("Lesson 08: Menu Interface");
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
  
  // Menu interface
  Serial.println("Displaying Menu Interface");
  gfx->fillScreen(BLACK);
  
  // Title bar
  gfx->fillRect(0, 0, 320, 50, BLUE);
  drawCenteredText("MENU", 10, WHITE, 2);
  
  // Menu items
  int menuY = 70;
  const char* menuItems[] = {"Settings", "Data", "About", "Exit"};
  uint16_t menuColors[] = {WHITE, CYAN, YELLOW, RED};
  
  gfx->setTextSize(2);
  for (int i = 0; i < 4; i++) {
    // Highlight current item (first one)
    if (i == 0) {
      gfx->fillRect(20, menuY - 5, 280, 50, CYAN);
      gfx->setTextColor(BLACK);
    } else {
      gfx->setTextColor(menuColors[i]);
    }
    
    gfx->setCursor(40, menuY);
    gfx->print("> ");
    gfx->println(menuItems[i]);
    
    menuY += 60;
  }
  
  Serial.println("Menu Interface display complete!");
}

void loop() {
  delay(1000);
}
