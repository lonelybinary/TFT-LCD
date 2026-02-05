/*
 * SPI接口 LCD 测试程序
 * 使用 Arduino GFX 官方库
 * 驱动芯片：ST7735P3
 * 规格书：T177BH-C12-12（1.77寸）
 * 分辨率：128x160
 */

#include <Arduino.h>
#include <Arduino_GFX_Library.h>

// ==================== SPI LCD 引脚定义 ====================
// 8引脚SPI LCD屏幕引脚定义：
// 1.LEDA/BLK, 2.GND, 3.RESET, 4.DC/RS/A0, 5.SDA/MOSI, 6.SCL/SCLK, 7.VDD, 8.CS
// 4线SPI: CS, DC/RS, SCLK, MOSI

#define TFT_CS    10   // CS (片选，引脚8)
#define TFT_RST   42   // RESET (复位，引脚3)
#define TFT_DC    2    // DC/RS/A0 (数据/命令选择，引脚4) - **必须连接！**
#define TFT_MOSI  11   // SDA/MOSI (SPI数据输出，引脚5)
#define TFT_SCLK  12   // SCL/SCLK (SPI时钟，引脚6)
#define TFT_BACKLIGHT 41  // LEDA/BLK (背光控制，引脚1)

// 引脚连接说明：
// - VDD (引脚7) → 3.3V (电源)
// - GND (引脚2) → GND (地线)
// - DC/RS/A0 (引脚4) → GPIO 2 (**必须连接！**)
// - SDA/MOSI (引脚5) → GPIO 11 (SPI数据输出)
// - SCL/SCLK (引脚6) → GPIO 12 (SPI时钟)
// - CS (引脚8) → GPIO 10 (片选)
// - RESET (引脚3) → GPIO 42 (复位)
// - LEDA/BLK (引脚1) → GPIO 41 (背光控制)

// ==================== LCD 对象 ====================
// 使用软件SPI（指定MOSI和SCLK引脚）
// ST7735P3：128x160
Arduino_DataBus *bus = new Arduino_SWSPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, -1);
Arduino_ST7735 *gfx = new Arduino_ST7735(bus, TFT_RST, 0 /* rotation */, false /* IPS */, 128 /* width */, 160 /* height */, 0 /* col offset 1 */, 0 /* row offset 1 */, 0 /* col offset 2 */, 0 /* row offset 2 */);

// ==================== 测试函数 ====================
void testFillScreen() {
  Serial.println("测试: 填充屏幕");
  gfx->fillScreen(BLACK);
  delay(500);
  gfx->fillScreen(RED);
  delay(500);
  gfx->fillScreen(GREEN);
  delay(500);
  gfx->fillScreen(BLUE);
  delay(500);
  gfx->fillScreen(WHITE);
  delay(500);
}

void testText() {
  Serial.println("测试: 文字显示");
  gfx->fillScreen(BLACK);
  gfx->setCursor(0, 0);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->println("SPI LCD Test");
  
  gfx->setTextColor(RED);
  gfx->setTextSize(1);
  gfx->println("RESOLUTION:128x160");
  gfx->println("DRIVER IC:ST7735P3");
  gfx->println("Library: Arduino GFX");
  gfx->println("Support rotation");
  
  delay(2000);
}

void testColors() {
  Serial.println("测试: 颜色显示");
  gfx->fillScreen(BLACK);
  
  uint16_t colors[] = {
    RED, GREEN, BLUE,
    YELLOW, MAGENTA, CYAN, WHITE
  };
  
  int w = gfx->width() / 4;
  int h = gfx->height() / 2;
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 2; j++) {
      int idx = i + j * 4;
      if (idx < 7) {
        gfx->fillRect(i * w, j * h, w, h, colors[idx]);
      }
    }
  }
  
  delay(2000);
}

void testLines() {
  Serial.println("测试: 线条绘制");
  gfx->fillScreen(BLACK);
  
  for (int i = 0; i < gfx->width(); i += 10) {
    gfx->drawLine(0, 0, i, gfx->height() - 1, RED);
    delay(10);
  }
  for (int i = 0; i < gfx->height(); i += 10) {
    gfx->drawLine(0, 0, gfx->width() - 1, i, GREEN);
    delay(10);
  }
  
  delay(1000);
}

void testCircles() {
  Serial.println("测试: 圆形绘制");
  gfx->fillScreen(BLACK);
  
  int centerX = gfx->width() / 2;
  int centerY = gfx->height() / 2;
  
  int maxR = (centerX < centerY) ? centerX : centerY;
  for (int r = 5; r < maxR; r += 5) {
    gfx->drawCircle(centerX, centerY, r, BLUE);
    delay(50);
  }
  
  delay(1000);
}

void testRectangles() {
  Serial.println("测试: 矩形绘制");
  gfx->fillScreen(BLACK);
  
  int maxSize = (gfx->width() < gfx->height()) ? gfx->width() : gfx->height();
  for (int i = 0; i < maxSize / 2; i += 5) {
    gfx->drawRect(i, i, gfx->width() - 2 * i, gfx->height() - 2 * i, YELLOW);
    delay(50);
  }
  
  delay(1000);
}

void testRotation() {
  Serial.println("测试: 屏幕旋转");
  
  for (uint8_t rotation = 0; rotation < 4; rotation++) {
    gfx->setRotation(rotation);
    gfx->fillScreen(BLACK);
    gfx->setCursor(10, 10);
    gfx->setTextColor(WHITE);
    gfx->setTextSize(2);
    gfx->print("Rotation ");
    gfx->println(rotation);
    delay(2000);
  }
  
  // 恢复默认方向
  gfx->setRotation(0);
}

void testGradient() {
  Serial.println("测试: 渐变效果");
  gfx->fillScreen(BLACK);
  
  for (int y = 0; y < gfx->height(); y++) {
    uint16_t color = gfx->color565(0, (y * 255) / gfx->height(), 255 - (y * 255) / gfx->height());
    gfx->drawFastHLine(0, y, gfx->width(), color);
  }
  
  delay(2000);
}

void displayInfo() {
  gfx->fillScreen(BLACK);
  gfx->setCursor(0, 0);
  gfx->setTextColor(WHITE);
  gfx->setTextSize(1);
  
  gfx->println("SPI LCD Test Program");
  gfx->println("================");
  gfx->print("Width: ");
  gfx->println(gfx->width());
  gfx->print("Height: ");
  gfx->println(gfx->height());
  gfx->println("");
  gfx->println("Tests:");
  gfx->println("1. Fill Screen");
  gfx->println("2. Text Display");
  gfx->println("3. Colors");
  gfx->println("4. Lines");
  gfx->println("5. Circles");
  gfx->println("6. Rectangles");
  gfx->println("7. Rotation");
  gfx->println("8. Gradient");
  
  delay(3000);
}

// ==================== 初始化 ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("========================================");
  Serial.println("SPI接口 LCD 测试程序");
  Serial.println("驱动芯片: ST7735P3");
  Serial.println("屏幕尺寸: 1.8 英寸");
  Serial.println("分辨率: 128x160");
  Serial.println("使用 Arduino GFX 官方库");
  Serial.println("========================================");
  
  // 初始化背光（PWM调光，设置为最亮）
  ledcSetup(0, 5000, 8);  // 通道0, 5kHz频率, 8位分辨率（0-255）
  ledcAttachPin(TFT_BACKLIGHT, 0);  // 将背光引脚连接到PWM通道0
  ledcWrite(0, 255);  // 设置为最亮（255 = 100%亮度）
  
  // 初始化LCD
  Serial.println("初始化LCD...");
  
  // 先复位屏幕
  pinMode(TFT_RST, OUTPUT);
  digitalWrite(TFT_RST, LOW);
  delay(10);
  digitalWrite(TFT_RST, HIGH);
  delay(120);
  
  // ST7735 初始化（128x160）
  Serial.println("初始化 ST7735 屏幕 (128x160)...");
  
  if (!gfx->begin()) {
    Serial.println("LCD初始化失败！");
    while (1);
  }
  
  // 设置旋转方向（可选）
  gfx->setRotation(0);  // 0=正常, 1=90度, 2=180度, 3=270度
  
  // 测试：先填充一个颜色看看是否有反应
  gfx->fillScreen(RED);
  delay(500);
  gfx->fillScreen(BLACK);
  
  Serial.println("LCD初始化完成");
  
  // 显示信息
  displayInfo();
  
  Serial.println("开始测试...");
}

// ==================== 主循环 ====================
void loop() {
  // 运行各种测试
  testFillScreen();
  testText();
  testColors();
  testLines();
  testCircles();
  testRectangles();
  testRotation();
  testGradient();
  
  // 最后显示信息
  displayInfo();
  
  Serial.println("测试循环完成，重新开始...");
  delay(2000);
}
