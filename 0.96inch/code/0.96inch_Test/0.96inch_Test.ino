/*
 * SPI LCD Test Program - Arduino IDE Version
 * Using Arduino GFX Official Library
 * Driver IC: ST7735S
 * Display Model: N096-1608TBBIG11-H13 (Newvision)
 * Resolution: 160x80 
 * 
 * Library Dependencies:
 * - Arduino GFX Library (moononournation/GFX Library for Arduino)
 *   In Arduino IDE: Tools -> Manage Libraries -> Search "GFX Library for Arduino"
 */

#include <Arduino_GFX_Library.h>

// ==================== SPI LCD Pin Definitions ====================
// 8-pin SPI LCD display pin definitions:
// 1.LEDA/BLK, 2.GND, 3.RESET, 4.DC/RS/A0, 5.SDA/MOSI, 6.SCL/SCLK, 7.VDD, 8.CS
// 4-wire SPI: CS, DC/RS, SCLK, MOSI

#define TFT_CS    10   // CS (Chip Select, pin 8)
#define TFT_RST   42   // RESET (Reset, pin 3)
#define TFT_DC    2    // DC/RS/A0 (Data/Command select, pin 4) - **Must connect!**
#define TFT_MOSI  11   // SDA/MOSI (SPI data output, pin 5) - VSPI hardware SPI pin
#define TFT_SCLK  12   // SCL/SCLK (SPI clock, pin 6) - VSPI hardware SPI pin
#define TFT_BACKLIGHT 41  // LEDA/BLK (Backlight control, pin 1)

// Pin connection description:
// - VDD (pin 7) → 3.3V (Power supply)
// - GND (pin 2) → GND (Ground)
// - DC/RS/A0 (pin 4) → GPIO 2 (**Must connect!**)
// - SDA/MOSI (pin 5) → GPIO 11 (SPI data output)
// - SCL/SCLK (pin 6) → GPIO 12 (SPI clock)
// - CS (pin 8) → GPIO 10 (Chip select)
// - RESET (pin 3) → GPIO 42 (Reset)
// - LEDA/BLK (pin 1) → GPIO 41 (Backlight control)

// ==================== LCD Object ====================
// Using hardware SPI (VSPI: MOSI=GPIO11, SCLK=GPIO12)
// ST7735S initialization parameters: 160x80
// Offset description:
// - col offset: Column offset (left-right movement), typically 24-28
// - row offset: Row offset (up-down movement), typically 0-3
// - offset 1 is used for rotation 0/2, offset 2 is used for rotation 1/3
// Note: GFX Library 1.6.4 API - Arduino_ESP32SPI constructor requires MISO parameter (use GFX_NOT_DEFINED if not used)
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED /* MISO (not used) */, 1 /* VSPI */, true /* use_psram */);
Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, false /* IPS */, 80 /* width */, 160 /* height */, 24 /* col offset 1 */, 0 /* row offset 1 */, 24 /* col offset 2 */, 0 /* row offset 2 */);

// ==================== Display LonelyBinary and Color Bars ====================
void displayLonelyBinary() {
  gfx->fillScreen(BLACK);
  
  // Top section: Center display "LonelyBinary" (adapt to screen size, ensure it doesn't exceed)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(1);  // 80px width, size=1 is appropriate: 12*1*6=72px
  int textWidth = strlen("LonelyBinary") * 1 * 6;  // Estimate text width: 72px
  int textX = (gfx->width() - textWidth) / 2;
  int textY = 14;  // Top section
  gfx->setCursor(textX, textY);
  gfx->println("LonelyBinary");
  
  // Bottom section: 8 horizontal color bars
  uint16_t colors[] = {
    RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE, BLACK
  };
  int barStartY = 29;
  int barHeight = 8;  // Each color bar height (widened)
  int barWidth = gfx->width();  // Color bar width (full screen width)
  
  for (int i = 0; i < 8; i++) {
    gfx->fillRect(0, barStartY + i * barHeight, barWidth, barHeight, colors[i]);
  }
  
  // Bottom: Display screen information (resolution, driver, inch size)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(1);
  int infoY = 94;
  gfx->setCursor(2, infoY);
  gfx->print("80x160");
  gfx->setCursor(2, infoY + 8);
  gfx->print("ST7735S");
  gfx->setCursor(2, infoY + 16);
  gfx->print("0.96inch");
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("SPI LCD Test Program");
  Serial.println("Driver IC: ST7735S");
  Serial.println("Display Model: N096-1608TBBIG11-H13");
  Serial.println("Resolution: 160x80");
  Serial.println("Using Arduino GFX Official Library");
  Serial.println("========================================");
  
  // Initialize backlight (PWM reversed control)
  // Note: 0.96 inch display uses reversed PWM control (0 = ON, 255 = OFF)
  ledcSetup(0, 5000, 8);  // Channel 0, 5kHz frequency, 8-bit resolution (0-255)
  ledcAttachPin(TFT_BACKLIGHT, 0);  // Attach backlight pin to PWM channel 0
  ledcWrite(0, 0);  // Set to maximum brightness (0 = 100% brightness, reversed)
  
  // Initialize LCD
  Serial.println("Initializing LCD...");
  
  // Reset display first
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(10);
  digitalWrite(TFT_RST, HIGH);
  delay(120);
  
  // ST7735S initialization
  Serial.println("Initializing ST7735S display (160x80)...");
  
  if (!gfx->begin()) {
    Serial.println("LCD initialization failed!");
    while (1);
  }
  
  // Set rotation direction (optional)
  gfx->setRotation(0);  // 0=normal, 1=90°, 2=180°, 3=270°
  
  Serial.println("LCD initialization complete");
  
  // Display LonelyBinary and color bars (static display)
  displayLonelyBinary();
  
  Serial.println("Display ready - showing static LonelyBinary and color bars");
}

// ==================== Main Loop ====================
void loop() {
  // Static display - nothing to do in loop
  delay(1000);
}
