/*
 * Lesson 05: Graphics
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习如何绘制基本图形
 * 
 * 知识点：
 * - 线条绘制
 * - 矩形绘制
 * - 圆形绘制
 * - 填充图形
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
// 注意：如需适配其他屏幕，请查看对应屏幕的测试程序
// 例如：0.96寸请查看 0.96inch/code/0.96inch_Test/0.96inch_Test.ino
// 详细适配指南请参考各屏幕文件夹下的ADAPTATION_GUIDE.md文件
Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCLK, TFT_MOSI, GFX_NOT_DEFINED, 1, true);
Arduino_ST7796 *gfx = new Arduino_ST7796(bus, TFT_RST, 0, true /* IPS */, 320, 480, 0, 0, 0, 0);

// ==================== Initialization ====================
void setup() {
  Serial.begin(115200);
  delay(1000);
  
  Serial.println("Lesson 05: Graphics");
  Serial.println("Initializing LCD...");
  
  // Initialize backlight (PWM)
  // 注意：0.96寸使用Active Low控制（digitalWrite(TFT_BACKLIGHT, LOW)）
  // 其他屏幕使用PWM控制，请查看对应屏幕的测试程序
  ledcSetup(0, 5000, 8);
  ledcAttachPin(TFT_BACKLIGHT, 0);
  ledcWrite(0, 255);
  
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
  
  // Part 1: 绘制线条
  Serial.println("Drawing lines...");
  gfx->fillScreen(BLACK);
  
  // 水平线
  gfx->drawLine(20, 20, 300, 20, WHITE);
  
  // 垂直线
  gfx->drawLine(20, 20, 20, 460, RED);
  
  // 对角线
  gfx->drawLine(20, 20, 300, 460, GREEN);
  gfx->drawLine(300, 20, 20, 460, BLUE);
  
  delay(2000);
  
  // Part 2: 绘制矩形（空心）
  Serial.println("Drawing rectangles (outline)...");
  gfx->fillScreen(BLACK);
  
  // 小矩形
  gfx->drawRect(20, 20, 80, 60, RED);
  
  // 中矩形
  gfx->drawRect(120, 20, 100, 80, GREEN);
  
  // 大矩形
  gfx->drawRect(20, 120, 150, 100, BLUE);
  
  delay(2000);
  
  // Part 3: 绘制填充矩形
  Serial.println("Drawing filled rectangles...");
  gfx->fillScreen(BLACK);
  
  // 填充矩形
  gfx->fillRect(20, 20, 80, 60, RED);
  gfx->fillRect(120, 20, 100, 80, GREEN);
  gfx->fillRect(20, 120, 150, 100, BLUE);
  
  delay(2000);
  
  // Part 4: 绘制圆形（空心）
  Serial.println("Drawing circles (outline)...");
  gfx->fillScreen(BLACK);
  
  // 小圆
  gfx->drawCircle(80, 100, 30, RED);
  
  // 中圆
  gfx->drawCircle(160, 100, 50, GREEN);
  
  // 大圆
  gfx->drawCircle(240, 100, 70, BLUE);
  
  delay(2000);
  
  // Part 5: 绘制填充圆形
  Serial.println("Drawing filled circles...");
  gfx->fillScreen(BLACK);
  
  // 填充圆
  gfx->fillCircle(80, 200, 30, RED);
  gfx->fillCircle(160, 200, 50, GREEN);
  gfx->fillCircle(240, 200, 70, BLUE);
  
  delay(2000);
  
  // Part 6: 组合图形 - 创建简单图标
  Serial.println("Creating simple icons...");
  gfx->fillScreen(BLACK);
  
  // 图标1：播放按钮（三角形）
  gfx->fillTriangle(50, 100, 50, 200, 150, 150, GREEN);
  
  // 图标2：停止按钮（正方形）
  gfx->fillRect(180, 100, 80, 80, RED);
  
  // 图标3：圆形按钮
  gfx->fillCircle(280, 150, 40, BLUE);
  
  delay(2000);
  
  // Part 7: 绘制网格
  Serial.println("Drawing grid...");
  gfx->fillScreen(BLACK);
  
  // 绘制网格线
  for (int x = 0; x < 320; x += 40) {
    gfx->drawLine(x, 0, x, 480, CYAN);
  }
  for (int y = 0; y < 480; y += 40) {
    gfx->drawLine(0, y, 320, y, CYAN);
  }
  
  delay(2000);
  
  // Part 8: 绘制进度条
  Serial.println("Drawing progress bar...");
  gfx->fillScreen(BLACK);
  
  // 进度条背景
  gfx->drawRect(20, 200, 280, 40, WHITE);
  
  // 进度条填充（50%）
  gfx->fillRect(20, 200, 140, 40, GREEN);
  
  // 显示百分比
  gfx->setTextColor(WHITE);
  gfx->setTextSize(2);
  gfx->setCursor(50, 100);
  gfx->println("Progress: 50%");
  
  delay(2000);
  
  // Part 9: 动态绘制
  Serial.println("Animating graphics...");
  gfx->fillScreen(BLACK);
  
  // 移动的圆
  for (int x = 40; x < 280; x += 10) {
    gfx->fillScreen(BLACK);
    gfx->fillCircle(x, 240, 30, YELLOW);
    delay(100);
  }
  
  // 增长的矩形
  for (int w = 20; w < 300; w += 10) {
    gfx->fillScreen(BLACK);
    gfx->fillRect(10, 200, w, 80, CYAN);
    delay(50);
  }
  
  Serial.println("Graphics demonstration complete!");
}

void loop() {
  delay(1000);
}
