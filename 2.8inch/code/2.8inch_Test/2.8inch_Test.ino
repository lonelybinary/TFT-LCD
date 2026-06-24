/*
 * SPI TFT-LCD Test Sketch (Arduino IDE)
 *
 * What it does: lights up the screen and draws "LonelyBinary" plus a set of
 * color bars, so you can confirm your display and wiring work. Display only
 * (no touch). The backlight is simple on/off (no brightness control).
 *
 * Display:    2.8 inch, 240x320 pixels
 * Driver IC:  ST7789
 *
 * Before uploading, pick your board in Arduino IDE under Tools -> Board:
 * "ESP32S3 Dev Module" for an ESP32-S3, or "ESP32 Dev Module" for a classic ESP32.
 *
 * Library needed (install once via Tools -> Manage Libraries):
 * - "GFX Library for Arduino" by moononournation. Any recent version works.
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
// 8-pin SPI LCD display pin definitions:
// 1.LEDA/BLK, 2.GND, 3.RESET, 4.DC/RS/A0, 5.SDA/MOSI, 6.SCL/SCLK, 7.VDD, 8.CS
// 4-wire SPI: CS, DC/RS, SCLK, MOSI
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
#endif
// Wiring quick-reference (which GPIO to use depends on your board).
// The #if block above picks these for you automatically based on the board
// you select in Arduino IDE - you do NOT need to edit any code.
//
//   Display pin        ESP32-S3      Classic ESP32   What it does
//   VDD (pin 7)        3.3V          3.3V            Power (use 3.3V, NEVER 5V)
//   GND (pin 2)        GND           GND             Ground
//   CS  (pin 8)        GPIO 10       GPIO 15         Chip select
//   RESET (pin 3)      GPIO 42       GPIO 4          Reset
//   DC/RS/A0 (pin 4)   GPIO 2        GPIO 2          Data/command (must connect!)
//   SDA/MOSI (pin 5)   GPIO 11       GPIO 23         SPI data
//   SCL/SCLK (pin 6)   GPIO 12       GPIO 18         SPI clock
//   LEDA/BLK (pin 1)   GPIO 41       GPIO 32         Backlight (on/off only)

// ==================== Create the display object ====================
// Two steps. First, "bus" describes HOW we talk to the screen: hardware SPI
// using the DC, CS, SCLK and MOSI pins defined above (MISO is unused here).
// Then "gfx" is the actual ST7789 screen driver (240x320) we call to draw.
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED /* MISO (not used) */, 1 /* VSPI */, TFT_USE_PSRAM /* use_psram (auto: PSRAM on S3, off on classic ESP32) */);
Arduino_ST7789 *gfx = new Arduino_ST7789(bus, TFT_RST, 0 /* rotation */, true /* IPS */, 240 /* width */, 320 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col offset 2 */, 0 /* row offset 2 */);

// ==================== Display LonelyBinary and Color Bars ====================
void displayLonelyBinary() {
  gfx->fillScreen(BLACK);
  
  // Top section: Center display "LonelyBinary" (adapt to screen size, ensure it doesn't exceed)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);  // 240px width, size=3 would be close to border, changed to size=2 for safety
  int textWidth = strlen("LonelyBinary") * 2 * 6;  // Estimate text width: 12*2*6=144px
  int textX = (gfx->width() - textWidth) / 2;
  int textY = 74;  // Top section
  gfx->setCursor(textX, textY);
  gfx->println("LonelyBinary");
  
  // Bottom section: 8 horizontal color bars
  uint16_t colors[] = {
    RED, GREEN, BLUE, YELLOW, MAGENTA, CYAN, WHITE, BLACK
  };
  int barStartY = 114;
  int barHeight = (gfx->height() - barStartY - 40) / 8;  // Each color bar height (widened), leave space for bottom info
  int barWidth = gfx->width();  // Color bar width (full screen width)
  
  for (int i = 0; i < 8; i++) {
    gfx->fillRect(0, barStartY + i * barHeight, barWidth, barHeight, colors[i]);
  }
  
  // Bottom: Display screen information (resolution, driver, inch size)
  gfx->setTextColor(WHITE);
  gfx->setTextSize(1);
  int infoY = 274;
  gfx->setCursor(10, infoY);
  gfx->print("240x320");
  gfx->setCursor(10, infoY + 12);
  gfx->print("ST7789");
  gfx->setCursor(10, infoY + 24);
  gfx->print("2.8inch");
}

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("SPI LCD Test Program");
  Serial.println("Driver IC: ST7789");
  Serial.println("Display Size: 2.8 inch");
  Serial.println("Resolution: 240x320");
  Serial.println("Using Arduino GFX Official Library");
  Serial.println("========================================");
  
  // Turn the backlight on (on/off only, no brightness control).
  pinMode(TFT_BACKLIGHT, OUTPUT);
  digitalWrite(TFT_BACKLIGHT, HIGH);  // HIGH = backlight ON
  
  // Initialize LCD
  Serial.println("Initializing LCD...");
  
  // Reset display first
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(10);
  digitalWrite(TFT_RST, HIGH);
  delay(120);
  
  // ST7789 initialization
  Serial.println("Initializing ST7789 display (240x320)...");
  
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
