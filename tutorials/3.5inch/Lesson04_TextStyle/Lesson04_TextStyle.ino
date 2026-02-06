/*
 * Lesson 04: Text Style
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习文本样式设置，包括前景色和背景色
 * 
 * 知识点：
 * - 文本前景色
 * - 文本背景色
 * - 颜色组合效果
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
  
  Serial.println("Lesson 04: Text Style");
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
  
  // Part 1: 只设置前景色（文本颜色）
  Serial.println("Displaying text with foreground color only...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 30);
  gfx->println("White text");
  
  gfx->setTextColor(RED);
  gfx->setCursor(50, 70);
  gfx->println("Red text");
  
  gfx->setTextColor(GREEN);
  gfx->setCursor(50, 110);
  gfx->println("Green text");
  
  gfx->setTextColor(BLUE);
  gfx->setCursor(50, 150);
  gfx->println("Blue text");
  
  gfx->setTextColor(YELLOW);
  gfx->setCursor(50, 190);
  gfx->println("Yellow text");
  
  delay(3000);
  
  // Part 2: 设置前景色和背景色
  Serial.println("Displaying text with foreground and background colors...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // 白色文字，红色背景
  gfx->setTextColor(WHITE, RED);
  gfx->setCursor(50, 30);
  gfx->println("White on Red");
  
  // 黑色文字，黄色背景
  gfx->setTextColor(BLACK, YELLOW);
  gfx->setCursor(50, 80);
  gfx->println("Black on Yellow");
  
  // 白色文字，蓝色背景
  gfx->setTextColor(WHITE, BLUE);
  gfx->setCursor(50, 130);
  gfx->println("White on Blue");
  
  // 红色文字，白色背景
  gfx->setTextColor(RED, WHITE);
  gfx->setCursor(50, 180);
  gfx->println("Red on White");
  
  delay(3000);
  
  // Part 3: 不同颜色组合
  Serial.println("Displaying different color combinations...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // 高对比度组合
  gfx->setTextColor(WHITE, BLACK);
  gfx->setCursor(50, 30);
  gfx->println("High Contrast");
  
  gfx->setTextColor(BLACK, WHITE);
  gfx->setCursor(50, 80);
  gfx->println("Inverted");
  
  // 彩色组合
  gfx->setTextColor(CYAN, MAGENTA);
  gfx->setCursor(50, 130);
  gfx->println("Cyan/Magenta");
  
  gfx->setTextColor(YELLOW, BLUE);
  gfx->setCursor(50, 180);
  gfx->println("Yellow/Blue");
  
  delay(3000);
  
  // Part 4: 文本区域背景
  Serial.println("Displaying text with background areas...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // 方法1：使用setTextColor设置背景
  gfx->setTextColor(WHITE, RED);
  gfx->setCursor(50, 30);
  gfx->println("Method 1");
  
  // 方法2：先绘制背景矩形，再显示文本
  gfx->fillRect(20, 100, 150, 30, GREEN);
  gfx->setTextColor(BLACK);
  gfx->setCursor(50, 110);
  gfx->println("Method 2");
  
  // 方法3：使用不同背景色显示多行
  gfx->fillRect(20, 160, 200, 30, BLUE);
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 170);
  gfx->println("Method 3");
  
  delay(3000);
  
  // Part 5: 创建标签效果
  Serial.println("Creating label effects...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // 标签1：成功标签（绿色背景）
  gfx->fillRect(50, 50, 120, 35, GREEN);
  gfx->setTextColor(BLACK);
  gfx->setCursor(60, 60);
  gfx->println("SUCCESS");
  
  // 标签2：警告标签（黄色背景）
  gfx->fillRect(50, 100, 120, 35, YELLOW);
  gfx->setTextColor(BLACK);
  gfx->setCursor(60, 110);
  gfx->println("WARNING");
  
  // 标签3：错误标签（红色背景）
  gfx->fillRect(50, 150, 120, 35, RED);
  gfx->setTextColor(WHITE);
  gfx->setCursor(60, 160);
  gfx->println("ERROR");
  
  // 标签4：信息标签（蓝色背景）
  gfx->fillRect(50, 200, 120, 35, BLUE);
  gfx->setTextColor(WHITE);
  gfx->setCursor(60, 210);
  gfx->println("INFO");
  
  delay(3000);
  
  // Part 6: 文本高亮效果
  Serial.println("Creating text highlight effects...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  // 高亮文本行
  gfx->fillRect(0, 100, 320, 40, CYAN);
  gfx->setTextColor(BLACK);
  gfx->setCursor(50, 110);
  gfx->println("Highlighted Line");
  
  // 正常文本
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 50);
  gfx->println("Normal Text");
  
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 160);
  gfx->println("Normal Text");
  
  Serial.println("Text style demonstration complete!");
}

void loop() {
  delay(1000);
}
