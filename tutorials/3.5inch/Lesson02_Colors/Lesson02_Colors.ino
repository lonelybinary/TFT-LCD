/*
 * Lesson 02: Colors
 * 3.5 inch TFT-LCD Display Tutorial
 * 
 * 课程目标：学习如何使用颜色
 * 
 * 知识点：
 * - 预定义颜色
 * - 填充屏幕颜色
 * - 设置文本颜色
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
  
  Serial.println("Lesson 02: Colors");
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
  
  // Part 1: 使用预定义颜色填充屏幕
  Serial.println("Displaying predefined colors...");
  
  // 红色
  gfx->fillScreen(RED);
  delay(2000);
  
  // 绿色
  gfx->fillScreen(GREEN);
  delay(2000);
  
  // 蓝色
  gfx->fillScreen(BLUE);
  delay(2000);
  
  // 黄色
  gfx->fillScreen(YELLOW);
  delay(2000);
  
  // 洋红色
  gfx->fillScreen(MAGENTA);
  delay(2000);
  
  // 青色
  gfx->fillScreen(CYAN);
  delay(2000);
  
  // 白色
  gfx->fillScreen(WHITE);
  delay(2000);
  
  // 黑色
  gfx->fillScreen(BLACK);
  delay(2000);
  
  // Part 2: 显示颜色名称列表
  Serial.println("Displaying color names...");
  gfx->fillScreen(BLACK);
  
  gfx->setTextSize(2);
  
  gfx->setTextColor(RED);
  gfx->setCursor(50, 20);
  gfx->println("RED");
  
  gfx->setTextColor(GREEN);
  gfx->setCursor(50, 60);
  gfx->println("GREEN");
  
  gfx->setTextColor(BLUE);
  gfx->setCursor(50, 100);
  gfx->println("BLUE");
  
  gfx->setTextColor(YELLOW);
  gfx->setCursor(50, 140);
  gfx->println("YELLOW");
  
  gfx->setTextColor(MAGENTA);
  gfx->setCursor(50, 180);
  gfx->println("MAGENTA");
  
  gfx->setTextColor(CYAN);
  gfx->setCursor(50, 220);
  gfx->println("CYAN");
  
  gfx->setTextColor(WHITE);
  gfx->setCursor(50, 260);
  gfx->println("WHITE");
  
  Serial.println("Color demonstration complete!");
}

void loop() {
  delay(1000);
}
