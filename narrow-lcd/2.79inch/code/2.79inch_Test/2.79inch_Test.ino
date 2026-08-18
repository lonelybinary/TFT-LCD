/*
 * SPI TFT-LCD Demo Sketch (Arduino IDE) - Narrow TFT LCD Collection
 *
 * Thank you for purchasing this Narrow TFT LCD Collection!
 *
 * Every screen in this collection uses the same 15-pin FPC connector, so any of
 * them plugs into the same breakout board - you can swap displays without
 * rewiring anything. The only thing that changes in software is which example
 * folder you open.
 *
 * Display:    2.79 inch, 142x428 pixels (428x142 in landscape)
 * Driver IC:  NV3007
 *
 * What this demo shows, once, then it stops on the thank-you page:
 *   1) RED / GREEN / BLUE full screen, 2 seconds each, colour name in the centre
 *      -> confirms the panel, the wiring and the colour order are all correct
 *   2) A backlight brightness sweep, 100% -> 10% -> 100%, on a white screen
 *      -> confirms the backlight pin and shows off PWM dimming
 *   3) A screen info page (driver, resolution, pins, SPI clock)
 *   4) A thank-you page, which stays on screen until you press reset
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
  #define LIME    RGB565_LIME
#endif
#ifndef LIME
  #define LIME    RGB565_LIME
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
  #define TFT_SPI_NUM   HSPI    // S3: SPI3 host (=1). Usable buses are FSPI(=0) and HSPI(=1).
  #define MCU_NAME      "ESP32-S3"
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
  #define MCU_NAME      "ESP32"
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
//   LEDA/BLK (pin 1)   GPIO 41       GPIO 32         Backlight (LOW = ON here!)


// ==================== Create the display object ====================
// Two steps. First, "bus" describes HOW we talk to the screen: hardware SPI
// using the DC, CS, SCLK and MOSI pins defined above (MISO is unused here).
// Then "gfx" is the actual NV3007 screen driver we call to draw.
//
// ROTATION 1 (landscape). Every screen in this collection is a narrow strip:
// this one is 142x428 as wired, which is only 142 pixels across - too narrow for
// most text. Rotation 1 turns it on its side and gives us 428x142. The wider
// screens elsewhere in this repo use rotation 0; this collection is different.
//
// THE FOUR OFFSET NUMBERS say where the visible glass sits inside the
// controller's larger internal memory. They are measured per panel. Note that
// only TWO of them are active at any one rotation - at rotation 1 the X offset
// comes from "row offset 1" and the Y offset from "col offset 2". Editing
// "col offset 1" here will appear to do nothing at all. See this size's README.
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED /* MISO (not used) */, TFT_SPI_NUM /* HSPI on S3, VSPI on classic ESP32 */, true /* is_shared_interface */);
// This size needs its own initialisation table. It is the same NV3007 chip as the
// 1.68 inch, but with different voltage/gamma values, so the 2.79 inch table is
// passed explicitly - without it the driver would use the 1.68 inch settings and
// the picture would come out wrong.
Arduino_NV3007 *gfx = new Arduino_NV3007(bus, TFT_RST, 1 /* rotation */, false /* IPS */, 142 /* width */, 428 /* height */,
    12 /* col offset 1 */, 0 /* row offset 1 */, 14 /* col offset 2 */, 0 /* row offset 2 */,
    nv3007_279_init_operations, sizeof(nv3007_279_init_operations));


// ==================== Backlight (PWM dimming) ====================
// The backlight is just an LED driven from one GPIO. Instead of switching it
// fully on or off, we drive it with PWM (a square wave whose ON fraction sets
// the apparent brightness). 5 kHz is far above what the eye can see, so there
// is no visible flicker.
#define BL_PWM_FREQ 5000   // PWM frequency in Hz
#define BL_PWM_BITS 8      // 8-bit resolution -> duty values 0..255

// IMPORTANT: on the narrow modules the backlight is ACTIVE LOW - pulling the pin
// LOW turns it ON. So a "bright" setting is a LOW duty cycle, which is why
// setBrightness() inverts the number below. Several of the wider screens in this
// repo are wired the other way round; don't copy this line across without checking.
#define BL_ACTIVE_LOW true

void backlightBegin() {
  // ESP32 core 3.x replaced ledcSetup()/ledcAttachPin() with a single ledcAttach().
  // Both spellings are here so the sketch compiles on either core version.
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcAttach(TFT_BACKLIGHT, BL_PWM_FREQ, BL_PWM_BITS);
#else
  ledcSetup(0, BL_PWM_FREQ, BL_PWM_BITS);
  ledcAttachPin(TFT_BACKLIGHT, 0);
#endif
}

// percent: 0 = off, 100 = full brightness
void setBrightness(uint8_t percent) {
  if (percent > 100) percent = 100;
  uint32_t duty = (uint32_t)percent * 255 / 100;
  if (BL_ACTIVE_LOW) duty = 255 - duty;   // LOW lights the panel, so invert
#if ESP_ARDUINO_VERSION_MAJOR >= 3
  ledcWrite(TFT_BACKLIGHT, duty);
#else
  ledcWrite(0, duty);
#endif
}


// ==================== Initialization ====================
void setup() {
  // ORDER MATTERS HERE. The screen is brought up FIRST and the serial messages
  // come afterwards, so the picture appears as soon as possible after power-up.
  // (An earlier version called Serial.begin() and then waited a second for the
  // USB port to be ready before touching the display - that wait was visible as
  // two to three seconds of dark screen on every boot.)
  Serial.begin(115200);

  // Backlight off while the panel initialises, so you don't see a flash of
  // whatever random data happens to be in the display's memory.
  backlightBegin();
  setBrightness(0);

  // 20 MHz is the SPI clock this panel was tested at.
  if (!gfx->begin(20000000)) {
    // The display failed to start. Keep the backlight off (there is nothing to
    // look at) and say so on the serial monitor once it is available.
    delay(1000);
    Serial.println("LCD initialization failed! Check the wiring, especially DC and RST.");
    while (1) { delay(1000); }
  }

  gfx->setRotation(1);          // landscape - long edge across
  gfx->fillScreen(BLACK);
  setBrightness(100);           // black screen ready - safe to light it up now

  // The display is already live, so this short wait costs nothing on screen.
  // It just gives a USB-CDC serial port time to attach before we print, so the
  // banner below isn't lost on boards where the USB port is the serial port.
  delay(200);
  Serial.println("========================================");
  Serial.println("Narrow TFT LCD Collection - Demo");
  Serial.println("Thank you for your purchase!");
  Serial.println("Driver IC: NV3007");
  Serial.println("Display Size: 2.79 inch");
  Serial.println("Resolution: 142x428 (428x142 landscape)");
  Serial.println("----------------------------------------");
  Serial.println("Same 15-pin FPC on every size - swap displays, no rewiring.");
  Serial.println("Try our E-Paper, round and touch displays too!");
  Serial.println("========================================");
  Serial.println("LCD initialization complete");
}


// ==================== Main Loop ====================
// The demo runs through its four scenes once and then parks on the thank-you
// page. Press the reset button on your board to watch it again.
void loop() {
  showColor(RED,  "RED");    delay(2000);
  showColor(LIME, "GREEN");  delay(2000);   // LIME is a pure bright green; the
  showColor(BLUE, "BLUE");   delay(2000);   // GREEN macro is a darker shade

  brightnessDemo();

  showInfo();      delay(4000);

  showThankYou();
  while (true) {
    delay(1000);
  }
}


// ---------------------------------------------------------------------------
// Scene 1: a solid colour filling the screen, with its name in the centre.
// If red shows as blue (or similar), the colour order or the IPS setting for
// this panel is wrong - see this size's README.
// ---------------------------------------------------------------------------
void showColor(uint16_t color, const char *name) {
  Serial.printf("scene: %s\n", name);
  int w = gfx->width(), h = gfx->height();

  // Pick the biggest text size that still leaves a margin on this panel.
  // Each character is 6x8 pixels at size 1, so size N is 6*N wide, 8*N tall.
  uint8_t ts = 4;
  while (ts > 1 && ((int)strlen(name) * 6 * ts > w - 16 || 8 * ts > h - 16)) ts--;

  gfx->fillScreen(color);
  gfx->setTextSize(ts);

  // getTextBounds() measures the string so we can centre it exactly.
  int16_t x1, y1;
  uint16_t tw, th;
  gfx->getTextBounds(name, 0, 0, &x1, &y1, &tw, &th);
  int cx = (w - (int)tw) / 2;
  int cy = (h - (int)th) / 2;

  // A dark plate behind the label - white text on a bright green or yellow
  // background would be almost unreadable without it.
  gfx->fillRoundRect(cx - 8, cy - 6, tw + 16, th + 12, 4, BLACK);
  gfx->setTextColor(WHITE);
  gfx->setCursor(cx, cy);
  gfx->print(name);
}


// ---------------------------------------------------------------------------
// Scene 2: the backlight brightness sweep.
// A white screen is deliberate - it is the state that drives the backlight
// hardest, so the dimming is easy to see.
// ---------------------------------------------------------------------------
void brightnessDemo() {
  Serial.println("scene: PWM brightness");
  int w = gfx->width(), h = gfx->height();

  gfx->fillScreen(WHITE);
  gfx->setTextColor(BLACK);

  // Biggest size where "100%" still fits with a margin.
  uint8_t ts = 4;
  while (ts > 1 && (4 * 6 * ts > w - 16 || 8 * ts > h - 16)) ts--;
  gfx->setTextSize(ts);

  // "%3d%%" is always 4 characters wide, so one fixed rectangle erases every
  // value and the number doesn't jitter as it counts down.
  const int textW = 4 * 6 * ts, textH = 8 * ts;
  const int tx = (w - textW) / 2;
  const int ty = (h - textH) / 2;

  for (int step = 0; step < 2; step++) {
    // step 0 counts 100 down to 10, step 1 counts back up to 100
    for (int i = 0; i <= 18; i++) {
      int pct = (step == 0) ? 100 - i * 5 : 10 + i * 5;
      setBrightness(pct);

      gfx->fillRect(tx, ty, textW, textH, WHITE);   // erase the old number
      gfx->setCursor(tx, ty);
      gfx->printf("%3d%%", pct);
      delay(60);
    }
    delay(300);
  }
  setBrightness(100);
}


// ---------------------------------------------------------------------------
// Scene 3: the details of this screen and how it is wired.
//
// The text size is worked out from the panel height rather than fixed at 1.
// Size 1 characters are 8 pixels tall, which fills the shortest screen in the
// collection nicely but looks tiny on the taller ones - so if seven lines at
// size 2 will fit, we use size 2. Every line is kept to 17 characters or fewer
// so it still fits across the narrowest panel at that size.
// ---------------------------------------------------------------------------
void showInfo() {
  Serial.println("scene: info");
  int h = gfx->height();

  const int LINES = 7;
  uint8_t ts = (LINES * (8 * 2 + 2) <= h) ? 2 : 1;   // 126 px needed at size 2
  const int lineH = 8 * ts + 2;

  gfx->fillScreen(BLACK);
  gfx->setTextSize(ts);

  int y = 2;
  gfx->setTextColor(YELLOW);
  gfx->setCursor(4, y); gfx->print("Lonely Binary"); y += lineH;

  gfx->setTextColor(WHITE);
  gfx->setCursor(4, y); gfx->print("2.79in NV3007"); y += lineH;
  gfx->setCursor(4, y); gfx->printf("%dx%d RGB565", gfx->width(), gfx->height()); y += lineH;
  gfx->setCursor(4, y); gfx->print("SPI 20MHz IPS off"); y += lineH;
  gfx->setCursor(4, y); gfx->printf("CS%d DC%d RST%d", TFT_CS, TFT_DC, TFT_RST); y += lineH;
  gfx->setCursor(4, y); gfx->printf("SCK%d MOSI%d BL%d", TFT_SCLK, TFT_MOSI, TFT_BACKLIGHT); y += lineH;
  gfx->setCursor(4, y); gfx->printf("%s %lus", MCU_NAME, millis() / 1000);
}


// ---------------------------------------------------------------------------
// Scene 4: thank you, and what else is in the range.
//
// As with the info page the body text grows to suit the panel. Here it depends
// on the WIDTH as well as the height: a wider screen fits more words per line,
// so it needs fewer lines, so a bigger font still fits. wrapLines() below
// measures that for us, and we simply use the largest size that still fits.
//
// The message is deliberately SHORT. Longer copy forces this down to size 1 on
// the 1.14 inch (the smallest screen here), which is hard to read - so anything
// extra to say goes in the serial banner instead of on the panel. If you add a
// sentence here, check it still fits at size 2 on the 1.14 inch: 19 characters
// per line, 6 lines maximum.
// ---------------------------------------------------------------------------
void showThankYou() {
  Serial.println("scene: thank you");
  int w = gfx->width(), h = gfx->height();

  const char *body1 = "Thank you for your purchase!";
  const char *body2 = "Same 15-pin FPC on every size - swap displays, no rewiring.";

  // Heading is always size 2; the body starts just below it.
  const int bodyTop = 22;

  // Try size 2 first, fall back to size 1 if the message would run off the end.
  uint8_t ts = 2;
  while (ts > 1) {
    int lineH = 8 * ts + 2;
    int lines = wrapLines(body1, w - 8, ts) + wrapLines(body2, w - 8, ts);
    if (bodyTop + lines * lineH <= h) break;
    ts--;
  }

  gfx->fillScreen(BLACK);

  // Heading, centred.
  gfx->setTextColor(YELLOW);
  gfx->setTextSize(2);
  int16_t x1, y1;
  uint16_t tw, th;
  const char *title = "Thank You!";
  gfx->getTextBounds(title, 0, 0, &x1, &y1, &tw, &th);
  gfx->setCursor((w - (int)tw) / 2, 2);
  gfx->print(title);

  // Two blocks of body text, the second starting at the y the first returns.
  gfx->setTextColor(WHITE);
  int16_t y = drawWrapped(body1, 4, bodyTop, w - 8, ts);

  gfx->setTextColor(CYAN);
  drawWrapped(body2, 4, y, w - 8, ts);
}


// ---------------------------------------------------------------------------
// How many lines would drawWrapped() need for this text at this size? Used to
// pick the biggest font that still fits, without drawing anything.
// ---------------------------------------------------------------------------
int wrapLines(const char *text, int16_t w, uint8_t size) {
  int maxChars = w / (6 * size);
  if (maxChars < 1) return 0;
  int lines = 0, len = 0;
  const char *p = text;
  while (*p) {
    const char *word = p;
    while (*p && *p != ' ') p++;
    int wlen = p - word;
    if (wlen > maxChars) wlen = maxChars;
    if (len && len + 1 + wlen > maxChars) { lines++; len = 0; }
    if (len) len++;
    len += wlen;
    while (*p == ' ') p++;
  }
  if (len) lines++;
  return lines;
}


// ---------------------------------------------------------------------------
// Word-wrap helper.
// This collection spans panels from 240 to 428 pixels wide, so the line breaks
// have to be worked out from gfx->width() at run time rather than written in by
// hand - text that fits the 2.79 inch would be cut off on the 1.14 inch.
// Returns the y coordinate just below the last line it drew.
// ---------------------------------------------------------------------------
int16_t drawWrapped(const char *text, int16_t x, int16_t y, int16_t w, uint8_t size) {
  gfx->setTextSize(size);
  const int charW = 6 * size;      // built-in font: 6 pixels per character
  const int lineH = 8 * size + 2;  // 8 pixels tall, plus 2 for breathing room
  int maxChars = w / charW;
  if (maxChars < 1) return y;
  if (maxChars > 90) maxChars = 90;   // keeps "line" inside its buffer

  char line[96];
  int len = 0;
  const char *p = text;

  while (*p) {
    // Take the next word (everything up to the next space).
    const char *word = p;
    while (*p && *p != ' ') p++;
    int wlen = p - word;
    if (wlen > maxChars) wlen = maxChars;   // a single word longer than one
                                            // line: cut it rather than loop
    if (len && len + 1 + wlen > maxChars) { // it doesn't fit - draw what we have
      line[len] = '\0';
      gfx->setCursor(x, y);
      gfx->print(line);
      y += lineH;
      len = 0;
    }
    if (len) line[len++] = ' ';
    memcpy(line + len, word, wlen);
    len += wlen;
    while (*p == ' ') p++;
  }
  if (len) {                                // draw the final partial line
    line[len] = '\0';
    gfx->setCursor(x, y);
    gfx->print(line);
    y += lineH;
  }
  return y;
}
